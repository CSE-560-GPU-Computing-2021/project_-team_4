//
// Created by paras on 4/5/2021.
//

#include <fstream>
#include <iostream>

#include "Quadtree.h"
#include "config.h"
#include "Utils.h"
std::ofstream myfile;
bool init = true;

bool strict_A_lt_B(point A, point B){
    if (A.first < B.first + E && A.second < B.second + E){
        return true;
    }
    return false;
}


Quadtree::Quadtree(point topleft_, point botright_) {
    botLeft = topleft_;
    topRight = botright_;
}

void Quadtree::insert(point node_) {
    if(!in_BB(node_)){
        return;
    }
    if (abs(botLeft.first - topRight.first) < QUAD_OFFSET + E || abs(botLeft.second - topRight.second) < QUAD_OFFSET + E){
//        myfile.open("quadtree_nodes.txt", std::ios_base::app);
//        myfile << node_.first << " " << node_.second << "\n";
//        myfile.close();

//        if(init){myfile.open("quadtree.txt", std::ios_base::app); init = false;}
//        myfile << botLeft.first << " " << botLeft.second << " " <<  topRight.first << " " << topRight.second << "\n";
//        myfile.close();
        nodes.push_back(node_);
        return;
    }
    if(strict_A_lt_B(botLeft, node_) && strict_A_lt_B(node_, std::make_pair((topRight.first + botLeft.first) / 2, (topRight.second + botLeft.second) / 2))) {
        if(botLeftTree==NULL) botLeftTree = new Quadtree(botLeft, std::make_pair((topRight.first + botLeft.first) / 2,
                                                           (topRight.second + botLeft.second) / 2));
        myfile.open("quadtree.txt", std::ios_base::app);
        myfile << botLeft.first << " " << botLeft.second << " " <<  topRight.first << " " << topRight.second << "\n";
        myfile.close();
        botLeftTree->insert(node_);
        return;        return;

    }
    else if(strict_A_lt_B(std::make_pair((topRight.first + botLeft.first) / 2, botLeft.second), node_) && strict_A_lt_B(node_, std::make_pair(topRight.first, (topRight.second + botLeft.second) / 2))) {
        if(botRightTree==NULL) botRightTree = new Quadtree(std::make_pair((topRight.first + botLeft.first) / 2, botLeft.second),
                                    std::make_pair(topRight.first, (topRight.second + botLeft.second) / 2));
        myfile.open("quadtree.txt", std::ios_base::app);
        myfile << botLeft.first << " " << botLeft.second << " " <<  topRight.first << " " << topRight.second << "\n";
        myfile.close();
        botRightTree->insert(node_);
        return;
    }
    else if(strict_A_lt_B(std::make_pair(botLeft.first, (topRight.second + botLeft.second) / 2), node_) && strict_A_lt_B(node_, std::make_pair((topRight.first + botLeft.first) / 2, topRight.second))) {
        if(topLeftTree==NULL)topLeftTree = new Quadtree(std::make_pair(botLeft.first, (topRight.second + botLeft.second) / 2),
                                   std::make_pair((topRight.first + botLeft.first) / 2, topRight.second));
        myfile.open("quadtree.txt", std::ios_base::app);
        myfile << botLeft.first << " " << botLeft.second << " " <<  topRight.first << " " << topRight.second << "\n";
        myfile.close();
        topLeftTree->insert(node_);
        return;
    }
    else{
        if(topRightTree==NULL)topRightTree = new Quadtree(
                std::make_pair((topRight.first + botLeft.first) / 2, (topRight.second + botLeft.second) / 2), topRight);
        myfile.open("quadtree.txt", std::ios_base::app);
        myfile << botLeft.first << " " << botLeft.second << " " <<  topRight.first << " " << topRight.second << "\n";
        myfile.close();
        topRightTree->insert(node_);
        return;
    }

//    botLeftTree->insert(node_);
//    topLeftTree->insert(node_);
//    botRightTree->insert(node_);
//    topRightTree->insert(node_);
}

std::vector<point> Quadtree::search(point node_){
    if ((strict_A_lt_B(botLeft, node_) && strict_A_lt_B(node_, topRight)) && (abs(botLeft.first - topRight.first) < QUAD_OFFSET || abs(botLeft.second - topRight.second) < QUAD_OFFSET)){
//        std::cout << nodes.size() << " " << botLeft.first << " " << botLeft.second << " " <<  topRight.first << " " << topRight.second << "\n";
        return nodes;
    }
    if(strict_A_lt_B(botLeft, node_) && strict_A_lt_B(node_, std::make_pair((topRight.first + botLeft.first) / 2, (topRight.second + botLeft.second) / 2))) {
        if (botLeftTree == NULL){return{};}
        return botLeftTree->search(node_);
    }
    else if(strict_A_lt_B(std::make_pair((topRight.first + botLeft.first) / 2, botLeft.second), node_) && strict_A_lt_B(node_, std::make_pair(topRight.first, (topRight.second + botLeft.second) / 2))) {
        if (botRightTree == NULL){return{};}
        return botRightTree->search(node_);
    }
    else if(strict_A_lt_B(std::make_pair(botLeft.first, (topRight.second + botLeft.second) / 2), node_) && strict_A_lt_B(node_, std::make_pair((topRight.first + botLeft.first) / 2, topRight.second))) {
        if (topLeftTree == NULL){return{};}
        return topLeftTree->search(node_);
    }
    else {
        if (topRightTree == NULL){return{};}
        return topRightTree->search(node_);
    }
}

bool Quadtree::isColliding(point node){
    std::vector<point> diagonals = {node, std::make_pair(node.first + clearance, node.second + clearance), std::make_pair(node.first + clearance, node.second - clearance), std::make_pair(node.first - clearance, node.second + clearance), std::make_pair(node.first - clearance, node.second - clearance)};
    for (auto diag: diagonals){
        std::vector<point> collision_points = search(diag);
//        if(collision_points.empty()){std::cout << 0 << " " << diag.first << " " << diag.second << std::endl;}
        for(auto obs: collision_points){
            if (Utils::eul_dist(obs, node) < clearance){
//                std::cout<< "Found " << node.first << " " << node.second << std::endl;
                return true;
            }
        }
    }
//    std::cout<< "Not found " << node.first << " " << node.second << std::endl;
    return false;
}

bool Quadtree::in_BB(point node) {
    if (strict_A_lt_B(botLeft, node) && strict_A_lt_B(node, topRight)){
       return true;
    }
    return false;
}


void Quadtree::print_all_points(){
    if (!nodes.empty()) {
        myfile.open("quadtree_nodes.txt", std::ios_base::app);
        for(auto node_: nodes) {
            myfile << node_.first << " " << node_.second << "\n";
        }
        myfile.close();
        return;
    }
    if(topLeftTree!=NULL)topLeftTree->print_all_points();
    if(topRightTree!=NULL)topRightTree->print_all_points();
    if(botLeftTree!=NULL)botLeftTree->print_all_points();
    if(botRightTree!=NULL)botRightTree->print_all_points();
}