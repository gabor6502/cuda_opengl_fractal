#include "generator.cuh"
#include "generator.h"

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <GLFW/glfw3.h> // NEEDED for cuda gl to compile
#include "cuda_gl_interop.h"

#include <iostream>
#include <assert.h>

// three channels for red, green, and blue
#define RGB_CHANNELS 3

// the standard cuda return checking macro
#define CUDA_CHECK_RETURN(value)                                          \
    {                                                                     \
        cudaError_t _m_cudaStat = value;                                  \
        if (_m_cudaStat != cudaSuccess)                                   \
        {                                                                 \
            fprintf(stderr, "Error %s at line %d in file %s\n",           \
                    cudaGetErrorString(_m_cudaStat), __LINE__, __FILE__); \
            exit(EXIT_FAILURE);                                           \
        }                                                                 \
    }

__host__ void initCUDA(unsigned short image_width, unsigned short image_height,
                       float *d_dwell_map,
                       float *d_image_colours1, float *d_image_colours2,
                       cudaGraphicsResource_t pbo_resource1,
                       cudaGraphicsResource_t pbo_resource2,
                       GLuint pbo1, GLuint pbo2)
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
    //CUDA_CHECK_RETURN(cudaGLSetGLDevice(DEVICE)); // deprecated
    CUDA_CHECK_RETURN(cudaSetDevice(DEVICE));

    CUDA_CHECK_RETURN(cudaGetDeviceProperties(&deviceProp, DEVICE));

    printf("allocating device memory ... ");
    CUDA_CHECK_RETURN(cudaMalloc((void **)&d_dwell_map, sizeof(unsigned int) * image_width * image_height));

    size_t device_image_size;

    CUDA_CHECK_RETURN(cudaGraphicsGLRegisterBuffer(&pbo_resource1, pbo1, cudaGraphicsRegisterFlagsWriteDiscard));
    CUDA_CHECK_RETURN(cudaGraphicsMapResources(1, &pbo_resource1));
    CUDA_CHECK_RETURN(cudaGraphicsResourceGetMappedPointer((void **)&d_image_colours1, &device_image_size, pbo_resource1));
    assert(device_image_size == sizeof(float) * image_width * image_height * RGB_CHANNELS);
    // CUDA_CHECK_RETURN(cudaGraphicsUnmapResources(1, &pbo_resource1)); see comment below

    CUDA_CHECK_RETURN(cudaGraphicsGLRegisterBuffer(&pbo_resource2, pbo2, cudaGraphicsRegisterFlagsWriteDiscard));
    CUDA_CHECK_RETURN(cudaGraphicsMapResources(1, &pbo_resource2));
    CUDA_CHECK_RETURN(cudaGraphicsResourceGetMappedPointer((void **)&d_image_colours2, &device_image_size, pbo_resource2));
    assert(device_image_size == sizeof(float) * image_width * image_height * RGB_CHANNELS);
    CUDA_CHECK_RETURN(cudaGraphicsUnmapResources(1, &pbo_resource2));
}

void destroyCUDA(float *d_dwell_map, cudaGraphicsResource_t curr_pbo_resource)
{
    CUDA_CHECK_RETURN(cudaFree((void *)d_dwell_map));

    CUDA_CHECK_RETURN(cudaGraphicsUnmapResources(1, &curr_pbo_resource));

    // NEED TO FIND A WAY TO FREE THE PBOS

    CUDA_CHECK_RETURN(cudaDeviceReset());
}