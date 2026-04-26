typedef unsigned int GLuint;

void initCUDA(unsigned short image_width, unsigned short image_height, 
              float *d_dwell_map, 
              float *d_image_colours1,  float *d_image_colours2, 
              cudaGraphicsResource_t pbo_resource1, 
              cudaGraphicsResource_t pbo_resource2, 
              GLuint pbo1, GLuint pbo2);

void destroyCUDA(float *d_dwell_map, float * d_image_colours1, float * d_image_colours2, 
                          cudaGraphicsResource_t pbo1, cudaGraphicsResource_t pbo2);