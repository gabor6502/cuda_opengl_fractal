#pragma once

// maximum magnitude of an element of the mandelbrot set, squared
#define MAX_MAG_SQ 4

// use first device found
#define DEVICE 0

class cudaGraphicsResource;
typedef cudaGraphicsResource *cudaGraphicsResource_t;

class Generator
{
public:

    static Generator * getInstance();
    static void destroyInstance();

    inline double getZoom() { return zoom; }
    inline unsigned short getIterations() { return iterations; }

    inline void setZoom(double zoom) { this->zoom = zoom; }
    inline void setIterations(unsigned short i) { iterations = i; }
    inline void setImageWidth(unsigned short width) { image_width = width; }
    inline void setImageHeight(unsigned short height) { image_height = height; }
    

private:
    static Generator *instance;
    Generator();
    ~Generator();

    // fractal generation transforms and parameters
    unsigned short iterations;
    double tx = 0.0f, ty = 0.0f;
    double zoom = 1.0f;
    unsigned short image_width, image_height;

    // opengl interop
    cudaGraphicsResource_t curr_pbo_resource;
    cudaGraphicsResource_t pbo_resource1;
    cudaGraphicsResource_t pbo_resource2;
};