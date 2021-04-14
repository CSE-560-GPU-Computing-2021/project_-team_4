//
// Created by paras on 4/5/2021.
//

#ifndef RRT_CPU_CANVAS_H
#define RRT_CPU_CANVAS_H

#include <tuple>
#include <vector>
#include "config.h"
#include "Quadtree.h"

#define Node std::tuple<float, float>

class Canvas {
public:
    std::vector<Node> obstacles;
    void add_obs_from_file(std::string path_to_file);
    bool is_colliding(Node node);
    bool is_colliding2(Node node);
    void init_obs_tree(point topLeft, point botRight, std::vector<Node> obs);
    Quadtree *obs_tree;
};


#endif //RRT_CPU_CANVAS_H
