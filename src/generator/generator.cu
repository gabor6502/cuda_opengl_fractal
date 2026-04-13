#include "generator.cuh"
#include "generator.h"

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <GLFW/glfw3.h> // NEEDED for cuda gl to compile
#include "cuda_gl_interop.h"

#include <iostream>

// the standard cuda return checking macro
#define CUDA_CHECK_RETURN(value)                                     \
{                                                                    \
    cudaError_t _m_cudaStat = value;                                 \
    if ( _m_cudaStat != cudaSuccess)                                 \
    {                                                                \
        fprintf(stderr, "Error %s at line %d in file %s\n",          \
            cudaGetErrorString(_m_cudaStat), __LINE__, __FILE__);    \
        exit(EXIT_FAILURE);                                          \
    }                                                                \
} 

__host__ void initCUDA()
{
    printf("initializing CUDA (+ opengl interop) ... ");

     int deviceCount = 0;
    cudaDeviceProp deviceProp;

        // make sure the hardware is CUDA compatible
    CUDA_CHECK_RETURN(cudaGetDeviceCount(&deviceCount));

    if (deviceCount == 0)
    {
        printf("\nCUDA is not supported on this machine!\n");
        exit(EXIT_FAILURE);
    }
    CUDA_CHECK_RETURN(cudaGLSetGLDevice(DEVICE));

    CUDA_CHECK_RETURN(cudaGetDeviceProperties(&deviceProp, DEVICE));
}