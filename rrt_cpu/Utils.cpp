//
// Created by paras on 4/5/2021.
//

#include "Utils.h"
#include "math.h"

Node Utils::extend(Node start, Node end, float step_size) {
    float distance = eul_dist(start, end);
    float ratio = fmin(step_size/distance, 1);
//    float ratio = step_size/distance;
    return std::make_tuple((1 - ratio) * std::get<0>(start) + ratio * std::get<0>(end), ((1 - ratio) * std::get<1>(start) + ratio * std::get<1>(end)));
}

Node Utils::rotate(Node center, Node node, float angle) {
    angle *= M_PI / 180;
    float ox = std::get<0>(center);
    float oy = std::get<1>(center);
    float px = std::get<0>(node);
    float py = std::get<1>(node);
    float qx = ox + cos(angle) * (px - ox) - sin(angle) * (py - oy);
    float qy = oy + sin(angle) * (px - ox) + cos(angle) * (py - oy);
    return std::make_tuple(qx, qy);
}

float Utils::eul_dist(std::tuple<float, float> node1, std::tuple<float, float> node2) {
    return sqrt(pow(std::get<0>(node1) - std::get<0>(node2), 2) +  pow(std::get<1>(node1) - std::get<1>(node2), 2));
}

float Utils::eul_dist(std::pair<float, float> node1, std::pair<float, float> node2) {
    return sqrt(pow(node1.first - node2.first, 2) +  pow(node1.second - node2.second, 2));
}

Node Utils::nearest_neighbour(Node node, std::vector<Node> nodes) {
    Node nearest = nodes[0];
    float min_dist = eul_dist(nearest, node);
    for (auto node_:nodes){
        if (eul_dist(node, node_) < min_dist){
            min_dist = eul_dist(node, node_);
            nearest = node_;
        }
    }
    return nearest;
}
