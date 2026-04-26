#pragma once

// maximum magnitude of an element of the mandelbrot set, squared
#define MAX_MAG_SQ 4

// use first device found
#define DEVICE 0

 // red, green, and blue channels
#define PIXEL_CHANNELS 3

class cudaGraphicsResource;
typedef cudaGraphicsResource *cudaGraphicsResource_t;
typedef unsigned int GLuint;

class Generator
{
public:

    static Generator * getInstance(unsigned short width, unsigned short height);
    static void destroyInstance();

    inline double getZoom() { return zoom; }
    inline unsigned short getIterations() { return iterations; }

    inline void setZoom(double zoom) { this->zoom = zoom; }
    inline void setIterations(unsigned short i) { iterations = i; } 

    void bindCurrentPBOToBuffer();

private:
    static Generator *instance;
    Generator(unsigned short width, unsigned short height);
    ~Generator();

    // fractal generation transforms and parameters
    unsigned short iterations;
    double tx = 0.0f, ty = 0.0f;
    double zoom = 1.0f;
    unsigned short image_width, image_height;

    // opengl interop
    GLuint curr_pbo;
    GLuint pbo1, pbo2;
    cudaGraphicsResource_t curr_pbo_resource;
    cudaGraphicsResource_t pbo_resource1 = 0;
    cudaGraphicsResource_t pbo_resource2 = 0;

    // CUDA specific device buffers
    float * curr_d_image_colours = nullptr;
    float * d_image_colours1 = nullptr;
    float * d_image_colours2 = nullptr;
    float * d_dwell_map = nullptr;
};