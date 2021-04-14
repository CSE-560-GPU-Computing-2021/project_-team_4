//
// Created by paras on 13/04/21.
//

#ifndef ASSIGNMENT01_UTILS_H
#define ASSIGNMENT01_UTILS_H


#include <tuple>
#include <vector>
#include "config.h"

class Utils {
public:
    static Node extend(Node start, Node end, float step_size);
    static Node rotate(Node center, Node node, float angle);
    static float eul_dist(Node node1, Node node2);
    static Node nearest_neighbour(Node node, std::vector<Node> nodes);
    static Node get_new_node(Node parent, float angle);
};


#endif //ASSIGNMENT01_UTILS_H
