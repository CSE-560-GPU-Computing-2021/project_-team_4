//
// Created by paras on 4/5/2021.
//

#ifndef RRT_CPU_UTILS_H
#define RRT_CPU_UTILS_H

#include <tuple>
#include <vector>

#define Node std::tuple<float, float>

class Utils {
public:
    static Node extend(Node start, Node end, float step_size);
    static Node rotate(Node center, Node node, float angle);
    static float eul_dist(Node node1, Node node2);
    static Node nearest_neighbour(Node node, std::vector<Node> nodes);
    static Node get_new_node(Node parent, float angle);

    static float eul_dist(std::pair<float, float> node1, std::pair<float, float> node2);
};


#endif //RRT_CPU_UTILS_H
