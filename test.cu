#include<iostream>
#include<cstdio>
#include <cuda.h>

__global__ void cuda_hello(int *a, int *b, int *c){
    c[0] = a[0] + b[0];
    printf("hello\n");
}

int main() {
    int *a;
    cudaMallocManaged(&a, sizeof(int));
    int *b;
    cudaMallocManaged(&b, sizeof(int));
    int *c;
    cudaMallocManaged(&c, sizeof(int));
    a[0] = 1;
    b[0] = 2;
    c[0] = 0;
    cuda_hello<<<1,1>>>(a, b, c);
    cudaDeviceSynchronize();
    std::cout << "c:" << c[0] << std::endl; 
    cudaFree(a);
    cudaFree(b);
    cudaFree(c);
    auto error = cudaGetLastError();
    std::cout << cudaGetErrorString(error) << "\n";
    return EXIT_SUCCESS;
}