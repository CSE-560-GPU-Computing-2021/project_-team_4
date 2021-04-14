//
// Created by paras on 13/04/21.
//

#ifndef ASSIGNMENT01_TREE_H
#define ASSIGNMENT01_TREE_H



#include <tuple>
#include <vector>
#include <map>
#include "Canvas.h"
#include "config.h"

class Tree {
public:
    Tree(Canvas *canvas, Node start, Node end, float step_size, int id);
    bool add_node(Node parent, Node node, bool collided);

    Canvas *canvas;
    int id;
    Node start;
    Node end;
    float step_size;
    std::vector<Node> nodes;
    std::map<Node, Node> parent_map;
};



#endif //ASSIGNMENT01_TREE_H
