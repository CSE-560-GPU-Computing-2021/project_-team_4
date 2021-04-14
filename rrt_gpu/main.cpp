#include <iostream>
#include <fstream>
#include <chrono>
#include "Canvas.h"
#include "Utils.h"
#include "Tree.h"
#include "config.h"
#include "random"

int build_tree(Tree *tree1, Tree *tree2){
    std::ofstream myfile;
    myfile.open ("path_raw.txt", std::ios_base::app);
    std::default_random_engine generator;

//    std::uniform_real_distribution<> angle_dis(0, 360);

    std::uniform_real_distribution<> sample_dir_x(BB.first.first, BB.second.first);
    std::uniform_real_distribution<> sample_dir_y(BB.first.second, BB.second.second);
    int iterations = 0;
    Tree* tree = tree1;
    Tree* sec_tree = tree2;
    while (iterations++<MAX_ITERATIONS){
        if(iterations%2==0){tree = tree1; sec_tree = tree2;} else{tree = tree2; sec_tree = tree1;}

//        Node parent = tree->pick_parent();
//        float sampled_angle = angle_dis(generator);
//        Node new_node = Utils::extend(parent, Utils::rotate(parent, tree->canvas->end, sampled_angle), STEP_SIZE);


        Node sampled_dir = std::make_tuple(sample_dir_x(generator), sample_dir_y(generator));
        Node parent = Utils::nearest_neighbour(sampled_dir, tree->nodes);
        Node new_node = Utils::extend(parent, sampled_dir, STEP_SIZE);

        if(std::get<0>(sampled_dir) > 30 && 10<std::get<1>(sampled_dir) && std::get<1>(sampled_dir) < 17 && tree->id==1 && iterations>1000){
            int count = 0;
        }

        if (tree->add_node(parent, new_node)){
            if(print_file) {
                myfile << std::get<0>(parent) << " " << std::get<1>(parent) << " " <<  std::get<0>(new_node) << " " << std::get<1>(new_node) << " " << tree->id << "\n";
            }
            if (Utils::eul_dist(new_node, tree->canvas->end)<0.2){
                myfile.close();
                return iterations;
            }
            for(auto node: sec_tree->nodes){
                if (Utils::eul_dist(new_node, node)<0.2){
                    myfile.close();
                    return iterations;
                }
            }
        }
        if(iterations%1000==0){std::cout<< iterations << std::endl;}
    }
    myfile.close();
    return -1;
}

int main() {
    if(print_file){ std::ofstream myfile; myfile.open ("path_raw.txt", std::ios_base::trunc | std::ios_base::out); myfile.close();}

    Canvas canvas1;
    canvas1.start = start_node;
    canvas1.end = end_node;
    if (canvas1.add_obs_from_image(path_to_obs)) return 0;
//     canvas1.add_obs_from_file(path_to_obs);
    canvas1.init_obs_tree(BB.first, BB.second, canvas1.obstacles);
//    canvas1.obs_tree->print_all_points();
    Tree tree1(&canvas1, STEP_SIZE, 0);

    Canvas canvas2;
    canvas2.start = end_node;
    canvas2.end = start_node;
    if (canvas2.add_obs_from_image(path_to_obs)) return 0;
    // canvas2.add_obs_from_file(path_to_obs);
    canvas2.init_obs_tree(BB.first, BB.second, canvas2.obstacles);
    Tree tree2(&canvas2, STEP_SIZE, 1);

    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    int iterations = build_tree(&tree1, &tree2);
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> time_span = t2 - t1;
    std::cout << "Time spent: " << time_span.count() << " ms" << std::endl;
    std::cout << iterations << std::endl;
    return 0;
}
