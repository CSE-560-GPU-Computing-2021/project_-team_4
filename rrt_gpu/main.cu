#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <iostream>
#include <fstream>
#include <random>
#include <ctime>
#include <cuda_runtime.h>

#include "Utils.h"
#include "Canvas.h"
#include "Tree.h"
#include "collision_gpu.h"
#include <chrono>
#define ENABLE_TIMER 1

using namespace std;
extern "C" int build_tree(Tree *tree1, Tree *tree2){
    if(print_file){ std::ofstream myfile; myfile.open ("path_raw.txt", std::ios_base::trunc | std::ios_base::out); myfile.close();}
    std::ofstream myfile;
    myfile.open ("path_raw.txt", std::ios_base::app);
    std::default_random_engine generator;
    generator.seed(SEED);
    float time_gpu = 0.;

    std::uniform_real_distribution<> sample_dir_x(BB.first.first, BB.second.first);
    std::uniform_real_distribution<> sample_dir_y(BB.first.second, BB.second.second);
    int iterations = 0;
    Tree* tree = tree1;
    Tree* sec_tree = tree2;

    bool* collided;
    bool* col_host;
    cudaMalloc((void **)&collided, sizeof(bool));
    col_host = (bool*)malloc(sizeof(bool));
    while (iterations++<MAX_ITERATIONS){
        if(iterations%2==0){tree = tree1; sec_tree = tree2;} else{tree = tree2; sec_tree = tree1;}
        Node sampled_dir = std::make_pair(sample_dir_x(generator), sample_dir_y(generator));
        Node parent = Utils::nearest_neighbour(sampled_dir, tree->nodes);
        Node new_node = Utils::extend(parent, sampled_dir, STEP_SIZE);

        std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();


        cudaMemset(collided, false, sizeof(bool));
        is_colliding_gpu(new_node, tree->canvas->obstacles_gpu, collided, tree->canvas->obstacles.size());


        cudaMemcpy(col_host, collided, sizeof (bool), cudaMemcpyDeviceToHost);

        if(SINGLE_CHECK_TIME) {
//            std::cout << *col_host << "\n";
            std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> time_span = t2 - t1;
            time_gpu += time_span.count();
        }

        if (tree->add_node(parent, new_node, *col_host)){
            if(print_file) {
                myfile << parent.first << " " << parent.second << " " <<  new_node.first << " " << new_node.second << " " << tree->id << "\n";
            }
            if (Utils::eul_dist(new_node, tree->end)<0.2){
                myfile.close();
                return iterations;
            }
            for(auto node: sec_tree->nodes){
                if (Utils::eul_dist(new_node, node)<0.2){
                    myfile.close();
                    if(SINGLE_CHECK_TIME){std::cout << "Time GPU: " << time_gpu << " ms" << std::endl;}
                    return iterations;
                }
            }
        }
        if(PRINT_ITERATIONS){if(iterations%1000==0){std::cout<< iterations << std::endl;}}
    }
    myfile.close();
    return -1;
}

int main(int argc, char **argv) {
    Canvas canvas;
    canvas.add_obs_from_file(path_to_obs);

    Node obs_array[canvas.obstacles.size()];
    std::copy(canvas.obstacles.begin(), canvas.obstacles.end(), obs_array);
    cudaMalloc((void **)&canvas.obstacles_gpu, canvas.obstacles.size()*sizeof(Node));
    cudaMemcpy(canvas.obstacles_gpu, obs_array, canvas.obstacles.size()*sizeof(Node), cudaMemcpyHostToDevice);

    Tree tree1(&canvas, start_node, end_node, STEP_SIZE, 0);
    Tree tree2(&canvas, end_node, start_node, STEP_SIZE, 1);

    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    int iterations = build_tree(&tree1, &tree2);
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> time_span = t2 - t1;
    std::cout << "Time spent: " << time_span.count() << " ms" << std::endl;
    std::cout << iterations << std::endl;
    return 0;
}
