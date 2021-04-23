//
// Created by paras on 4/5/2021.
//

#ifndef RRT_CPU_CONFIG_H
#define RRT_CPU_CONFIG_H

#endif //RRT_CPU_CONFIG_H

#include <tuple>
#define Node std::tuple<float, float>
#define SEED 4
#define clearance 1.f
#define path_to_obs "../map5.txt"
#define start_node Node(780.f, 302.f)
#define end_node Node(10.f, 380.f)
//#define start_node Node(35.f, 17.f)
//#define end_node Node(10.f, 15.f)
#define MAX_ITERATIONS 70000
#define STEP_SIZE 0.5
#define print_file false
#define QUAD_OFFSET 2*clearance
#define QUADTREE true
#define BB std::make_pair(std::make_pair(0.f, 0.f), std::make_pair(800.f, 400.f))
#define E 0.00001

