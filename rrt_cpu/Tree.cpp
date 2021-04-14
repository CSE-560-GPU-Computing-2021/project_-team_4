//
// Created by paras on 4/5/2021.
//

#include <random>
#include <time.h>
#include <iostream>
#include "Tree.h"
#include "Utils.h"

std::default_random_engine generator;

Tree::Tree(Canvas *canvas_, Node start_, Node end_, float step_size_, int id_) {
    canvas = canvas_;
    start = start_;
    end = end_;
    id = id_;
    step_size = step_size_;
    nodes.push_back(start);
    parent_map[start] = start;
}

//Node Tree::pick_parent() {
////    generator.seed(time(0));
//    std::uniform_int_distribution<int> dis(0, nodes.size()-1);
//    int random_index = dis(generator);
//    Node parent = nodes[random_index];
//    return parent;
//}

bool Tree::add_node(Node parent, Node node) {
    if (QUADTREE){
        if (!canvas->is_colliding(node) && Utils::eul_dist(parent, node) > STEP_SIZE/1.1){
          nodes.push_back(node);
          parent_map[node] = parent;
          return true;
        }
    } else{
//        if (canvas->is_colliding(node) != canvas->is_colliding2(node) ){
//            std::cout << std::get<0>(node) << " " << std::get<1>(node) << std::endl;
//            canvas->is_colliding(node);
//        }
    if (!canvas->is_colliding2(node) && Utils::eul_dist(parent, node) > STEP_SIZE/1.1){
        nodes.push_back(node);
        parent_map[node] = parent;
        return true;
    }
    }
    return false;
}