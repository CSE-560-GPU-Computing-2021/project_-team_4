cmake_minimum_required(VERSION 3.10)

project(Assignment01 LANGUAGES CUDA CXX)

find_package(CUDAToolkit)

set(SOURCES
        main.cu
        Utils.cpp Utils.h Canvas.cpp Canvas.h config.h Tree.cpp Tree.h collision_gpu.cu collision_gpu.h)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${CUDAToolkit_INCLUDE_DIRS})
set_target_properties(${PROJECT_NAME} PROPERTIES 
											CUDA_SEPERABLE_COMPILATION ON
											)
target_compile_options(${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CUDA>:
											--keep # Keep PTX code 
											>)
