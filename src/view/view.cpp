#include "view.h"
#include <glad.h>
#include <GLFW/glfw3.h>
#include <shaderman.h>
#include <controller.h>
#include <assert.h>
#include <iostream>

// -- Callbacks --
void View::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
    this->width = width;
    this->height = height;
}

// -- Static Methods --

View *View::instance = nullptr;
View *View::getInstance(unsigned int width, unsigned int height, const char *name)
{
    if (!View::instance)
    {
        View::instance = new View(width, height, name);
    }

    return View::instance;
}

void View::destroyInstance()
{
    if (!View::instance)
    {
        return;
    }

    delete View::instance;
    View::instance = nullptr;
}

// -- Constructor/Destructor --

View::View(unsigned int width, unsigned int height, const char *name)
    : width(width), height(height)
{

    assert(width > 0);
    assert(height > 0);

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->window = glfwCreateWindow(width, height, name, NULL, NULL);
    if (window == NULL)
    {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return;
        
    }
    glfwMakeContextCurrent(this->window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD\n");
        return;
    }
    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(this->window, [](GLFWwindow *window, int width, int height)
                                   { instance->framebuffer_size_callback(window, width, height); });

    // -- Setup Shaders --
    Shaderman shademan;

    shademan.setVertexShader("/home/elan/development/cpp/CUDAGLFractal/src/shaderman/shaders/vshader.glsl");
    shademan.setFragmentShader("/home/elan/development/cpp/CUDAGLFractal/src/shaderman/shaders/fshader.glsl");

    bool shadersInit = shademan.initShaders();
    if (!shadersInit)
    {
        printf("\nshaders failed to init, exiting\n");
        return;
    }
    glUseProgram(shademan.getProgram());

    initialized = true;
}

View::~View()
{
    if (initialized)
    {
        glfwTerminate();
    }
}

// -- Instance Methods --
void View::display(GLuint ebo, Controller & controller)
{
    if (!initialized)
    {
        return;
    }
    // -- Render --
    while (!glfwWindowShouldClose(this->window))
    {
        // - render square -
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // - update -
        controller.update();

        glfwSwapBuffers(this->window);
        glfwPollEvents();
    }
}