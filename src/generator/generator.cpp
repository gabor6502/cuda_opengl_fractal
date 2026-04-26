#include "generator.h"
#include "generator.cuh"

#include <glad.h>

// -- Static Methods --

Generator *Generator::instance = nullptr;
Generator *Generator::getInstance(unsigned short width, unsigned short height)
{
    if (!instance)
    {
        instance = new Generator(width, height);
    }
    return instance;
}

void Generator::destroyInstance()
{
    if (!instance)
    {
        return;
    }
    delete instance;
    instance = nullptr;
}

// -- Constructor/Destructor --
Generator::Generator(unsigned short width, unsigned short height){ 
    image_width = width;
    image_height = height;

	glGenBuffers(1, &pbo1);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pbo1);
	glBufferData(GL_PIXEL_UNPACK_BUFFER, sizeof(float) * PIXEL_CHANNELS * width * height, 0, GL_STREAM_DRAW);

	glGenBuffers(1, &pbo2);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pbo2);
	glBufferData(GL_PIXEL_UNPACK_BUFFER, sizeof(float) * PIXEL_CHANNELS * width * height, 0, GL_STREAM_DRAW);

    initCUDA(image_width, image_height, d_dwell_map, d_image_colours1, d_image_colours2, pbo_resource1, pbo_resource2, pbo1, pbo2);

    // since CUDA renders the image first, then OpenGL consumes it, CUDA will be init with pbo 1
   curr_pbo_resource = pbo_resource1;
   curr_d_image_colours = d_image_colours1;

   // any other init?
}

Generator::~Generator()
{
    destroyCUDA(d_dwell_map, d_image_colours1, d_image_colours2, pbo_resource1, pbo_resource2);
}

// -- Instance Methods --
void Generator::bindCurrentPBOToBuffer()
{
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, curr_pbo);
}