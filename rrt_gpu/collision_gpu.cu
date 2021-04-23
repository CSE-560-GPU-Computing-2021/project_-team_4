#include "config.h"
#include "Utils.h"
#include "collision_gpu.h"
#include "iostream"
#define gpuErrchk(ans) { gpuAssert((ans), __FILE__, __LINE__); }
inline void gpuAssert(cudaError_t code, const char *file, int line, bool abort=true)
{
    if (code != cudaSuccess)
    {
        fprintf(stderr,"GPUassert: %s %s %d\n", cudaGetErrorString(code), file, line);
        if (abort) exit(code);
    }
}

__device__ float eul_dist(std::pair<float, float> node1, std::pair<float, float> node2) {
    return sqrt(pow(node1.first - node2.first, 2) +  pow(node1.second - node2.second, 2));
}
__global__ void collision(Node node, Node* obstacles, bool* col, int obs_size){
    int obs_ind = blockDim.x*blockIdx.x + threadIdx.x;
    if(obs_ind < obs_size) {
        if (eul_dist(node, obstacles[obs_ind]) < clearance) {
//            printf("%d \n", obs_ind);
            *col = true;
        }
    }
}

void is_colliding_gpu(Node node, Node* obstacles, bool* col, int obs_size) {
//    std::cout << "Size: " <<obs_size <<"\n";/
    collision<<<(obs_size-1)/1024+1, 1024>>>(node, obstacles, col, obs_size);
    gpuErrchk( cudaPeekAtLastError() );
    gpuErrchk( cudaDeviceSynchronize() );
    cudaDeviceSynchronize();
//    std::cout << "check: " << *col << "\n";
}

