//
// Created by paras on 4/5/2021.
//

#ifndef RRT_CPU_QUADTREE_H
#define RRT_CPU_QUADTREE_H

#include <vector>
#define point std::pair<float, float>

class Quadtree {
public:
    Quadtree(point topleft, point botright);
    void insert(point node);

    std::vector<point> nodes;
    point botLeft, topRight;
    Quadtree *botLeftTree = NULL;
    Quadtree *botRightTree = NULL;
    Quadtree *topLeftTree = NULL;
    Quadtree *topRightTree = NULL;

    bool in_BB(point node);

    std::vector<point> search(std::pair<float, float> node);

    bool isColliding(std::pair<float, float> node);

    void print_all_points();
};


#endif //RRT_CPU_QUADTREE_H
