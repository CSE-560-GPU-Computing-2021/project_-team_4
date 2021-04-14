//
// Created by paras on 13/04/21.
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
            obstacles.emplace_back(std::make_pair(v[0], v[1]));
        }
        obs_file.close();
    }
    else std::cout << "Unable to open file";
}

bool Canvas::is_colliding(Node node) {
    for(auto obs: obstacles){
        if (Utils::eul_dist(node, obs) < clearance){
            return true;
        }
    }
    return false;
}