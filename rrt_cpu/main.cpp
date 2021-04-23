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
    generator.seed(SEED);
    if(print_file) {
        myfile << std::get<0>(tree1->start) << " " << std::get<1>(tree1->start) << " " <<  std::get<0>(tree1->end) << " " << std::get<1>(tree1->end) << "\n";
    }
    std::uniform_real_distribution<> sample_dir_x(BB.first.first, BB.second.first);
    std::uniform_real_distribution<> sample_dir_y(BB.first.second, BB.second.second);
    int iterations = 0;
    Tree* tree = tree1;
//    Tree* sec_tree = tree2;
    while (iterations++<MAX_ITERATIONS){
//        if(iterations%2==0){tree = tree1; sec_tree = tree2;} else{tree = tree2; sec_tree = tree1;}

        Node sampled_dir = std::make_tuple(sample_dir_x(generator), sample_dir_y(generator));
        Node parent = Utils::nearest_neighbour(sampled_dir, tree->nodes);
        Node new_node = Utils::extend(parent, sampled_dir, STEP_SIZE);

        if (tree->add_node(parent, new_node)){
            if(print_file) {
                myfile << std::get<0>(parent) << " " << std::get<1>(parent) << " " <<  std::get<0>(new_node) << " " << std::get<1>(new_node) << " " << tree->id << "\n";
            }
            if (Utils::eul_dist(new_node, tree->end)<STEP_SIZE){
                myfile.close();
                return iterations;
            }
//            for(auto node: sec_tree->nodes){
//                if (Utils::eul_dist(new_node, node)<STEP_SIZE){
//                    myfile.close();
//                    return iterations;
//                }
//            }
        }
        if(iterations%1000==0){std::cout<< iterations << std::endl;}
    }
    myfile.close();
//        Node parent = tree->pick_parent();
//        float sampled_angle = angle_dis(generator);
//        Node new_node = Utils::extend(parent, Utils::rotate(parent, tree->canvas->end, sampled_angle), STEP_SIZE);


    return -1;
}

int main() {
    if(print_file){ std::ofstream myfile; myfile.open ("path_raw.txt", std::ios_base::trunc | std::ios_base::out); myfile.close();}
//    std::ofstream myfile;
//    myfile.open("quad_false_nodes.txt", std::ios_base::trunc | std::ios_base::out);
//    myfile.close();

    Canvas canvas;
    canvas.add_obs_from_file(path_to_obs);
    canvas.init_obs_tree(BB.first, BB.second, canvas.obstacles);
//    canvas1.obs_tree->print_all_points();

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
