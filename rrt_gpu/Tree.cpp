//
// Created by paras on 4/5/2021.
//

#include <random>
#include <time.h>
#include <iostream>
#include "Tree.h"
#include "Utils.h"
#include "collision_gpu.h"


Tree::Tree(Canvas *canvas_, Node start_, Node end_, float step_size_, int id_) {
    canvas = canvas_;
    start = start_;
    end = end_;
    id = id_;
    step_size = step_size_;
    nodes.push_back(start);
    parent_map[start] = start;
}

bool Tree::add_node(Node parent, Node node, bool collided) {
//    if(canvas->is_colliding(node) != collided){
////        std::cout << node.first << " " << node.second << " " << collided << "Parallel collision differs\n";
//    }
//    if (!collided && Utils::eul_dist(parent, node) > STEP_SIZE/1.1){
//        nodes.push_back(node);
//        parent_map[node] = parent;
//        return true;
//    }
    if (!canvas->is_colliding(node) && Utils::eul_dist(parent, node) > STEP_SIZE/1.1){
        nodes.push_back(node);
        parent_map[node] = parent;
        return true;
    }
    return false;
}