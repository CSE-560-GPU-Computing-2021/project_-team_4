//
// Created by paras on 13/04/21.
//

#ifndef ASSIGNMENT01_CONFIG_H
#define ASSIGNMENT01_CONFIG_H

#endif //ASSIGNMENT01_CONFIG_H

#include <tuple>
#define Node std::pair<float, float>
#define clearance 0.52f
#define SEED 7
#define path_to_obs "../map2.txt"
#define start_node Node(780.f, 300.f)
#define end_node Node(10.f, 380.f)
#define MAX_ITERATIONS 70000
#define STEP_SIZE 0.4
#define print_file true
#define BB std::make_pair(std::make_pair(0.f, 0.f), std::make_pair(800.f, 400.f))
#define SINGLE_CHECK_TIME false
#define PRINT_ITERATIONS true