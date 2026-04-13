#include "controller.h"
#include "view.h"
#include <glad.h>
#include <assert.h>

// -- Static Methods --

Controller *Controller::instance = nullptr;
Controller *Controller::getInstance(unsigned int width, unsigned int height, const char *name)
{
    if (!Controller::instance)
    {
        Controller::instance = new Controller(width, height, name);

        // -- Setup Geometry --

        const int TRIANGLE_VERT_COUNT = 3; // three angles in a threeangle
        const int NUM_TRIANGLES = 2;

        const int VERTEX_LAYOUT_LOCATION = 0;

        const int STRIDE_LEN = 3;

        // two triangles make a square/quad
        const float verticies[] = 
        {
            // triangle positions (x,y,z)   
            1.0f,  1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,      
            -1.0f, -1.0f, 0.0f,        
            -1.0f,  1.0f, 0.0f,           
        };

        const unsigned int indicies[] =
        {
            0, 1, 3,
            1, 2, 3
        };

        // Create vertex buffer object for the square + verticies
        glGenBuffers(1, &instance->vbo);
        glBindBuffer(GL_ARRAY_BUFFER, instance->vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

        // Create an element/index buffer object for rendering the verticies as a square
        glGenBuffers(1, &instance->ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, instance->ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

        // Generate vertex array buffer for access to verticies in shaders
        glGenVertexArrays(1, &instance->vao);
        glBindVertexArray(instance->vao);
        glVertexAttribPointer(VERTEX_LAYOUT_LOCATION, TRIANGLE_VERT_COUNT, GL_FLOAT, GL_FALSE,
                              STRIDE_LEN * sizeof(float), (void *)0);
        glEnableVertexAttribArray(VERTEX_LAYOUT_LOCATION);
    }

    return Controller::instance;
}

void Controller::destroyInstance()
{
    assert(instance);
    if (!Controller::instance)
    {
        return;
    }

    delete Controller::instance;
    Controller::instance = nullptr;
}

// -- Constructor/Destructor --

Controller::Controller(unsigned int width, unsigned int height, const char *name)
{
    assert(width > 0);
    assert(height > 0);
    assert(name);
    this->view = View::getInstance(width, height, name);
}

Controller::~Controller()
{

    glDeleteBuffers(1, &ebo);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &vao);

    View::destroyInstance();
}

// -- Instance Methods --

bool Controller::isInitialized()
{ 
    return view && view->isInitialized(); 
}

void Controller::run()
{
    assert(view);
    if (!view)
    {
        return;
    }
    view->display(ebo, *this);
}

void Controller::update()
{
    // do nothing for now
}