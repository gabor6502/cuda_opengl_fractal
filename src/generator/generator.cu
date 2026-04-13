#include "generator.cuh"
#include "generator.h"

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <GLFW/glfw3.h> // NEEDED for cuda gl to compile
#include "cuda_gl_interop.h"

#include <iostream>

__host__ void sayhi()
{
    printf("hi!\n");
}