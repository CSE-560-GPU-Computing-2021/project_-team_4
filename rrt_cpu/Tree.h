//
// Created by paras on 4/5/2021.
//

#ifndef RRT_CPU_TREE_H
#define RRT_CPU_TREE_H

#include <tuple>
#include <vector>
#include <map>
#include "Canvas.h"

#define Node std::tuple<float, float>

class Tree {
public:
    Tree(Canvas *canvas, Node start, Node end, float step_size, int id);
    bool add_node(Node parent, Node node);

    Canvas *canvas;
    int id;
    Node start;
    Node end;
    float step_size;
    std::vector<Node> nodes;
    std::map<Node, Node> parent_map;
};


#endif //RRT_CPU_TREE_H
