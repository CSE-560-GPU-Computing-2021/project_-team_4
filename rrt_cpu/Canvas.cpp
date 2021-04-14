//
// Created by paras on 4/5/2021.
//

#include <fstream>
#include <sstream>
#include <iterator>
#include <iostream>
#include "Canvas.h"
#include "Utils.h"

void Canvas::add_obs_from_file(std::string path_to_file) {
    std::string line;
    std::string word;
    std::ifstream obs_file (path_to_file);
    if (obs_file.is_open())
    {
        while (getline (obs_file,line))
        {
            std::vector<float> v;
            std::istringstream line_(line);
            std::copy(std::istream_iterator<float>(line_),
                      std::istream_iterator<float>(),
                      std::back_inserter(v));
            obstacles.emplace_back(std::make_tuple(v[0], v[1]));
        }
        obs_file.close();
    }
    else std::cout << "Unable to open file";
}

bool Canvas::is_colliding2(std::tuple<float, float> node) {
    for(auto obs: obstacles){
        if (Utils::eul_dist(node, obs) < clearance){
            return true;
        }
    }
    return false;
}

bool Canvas::is_colliding(std::tuple<float, float> node) {
    return obs_tree->isColliding(std::make_pair(std::get<0>(node), std::get<1>(node)));
}

void Canvas::init_obs_tree(point topLeft, point botRight, std::vector<std::tuple<float, float>> obs_array) {
    obs_tree = new Quadtree(topLeft, botRight);
    for (auto obs: obs_array) {
        obs_tree->insert(std::make_pair(std::get<0>(obs), std::get<1>(obs)));
    }
}