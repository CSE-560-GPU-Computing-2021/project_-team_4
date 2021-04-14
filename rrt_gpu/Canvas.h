//
// Created by paras on 13/04/21.
//

#ifndef ASSIGNMENT01_CANVAS_H
#define ASSIGNMENT01_CANVAS_H



#include <tuple>
#include <vector>
#include "config.h"

class Canvas {
public:
    std::vector<Node> obstacles;
    Node* obstacles_gpu;
    void add_obs_from_file(std::string path_to_file);
    bool is_colliding(Node node);
};

#endif //ASSIGNMENT01_CANVAS_H
