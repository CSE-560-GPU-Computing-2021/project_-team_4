cmake_minimum_required(VERSION 3.17)
project(rrt_cpu)
find_package(CUDAToolkit)
set(CMAKE_CUDA_STANDARD 14)

add_executable(rrt_cpu main.cpp Tree.cpp Tree.h Canvas.cpp Canvas.h Utils.cpp Utils.h config.h Quadtree.cpp Quadtree.h main_single_rrt.cpp)

set_target_properties(
        rrt_cpu
        PROPERTIES
        CUDA_SEPARABLE_COMPILATION ON)

target_include_directories(${PROJECT_NAME} PRIVATE ${CUDAToolkit_INCLUDE_DIRS})
target_compile_options(${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CUDA>:
        --keep # Keep PTX code
        >)