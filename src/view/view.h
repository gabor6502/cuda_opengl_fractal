#pragma once

class GLFWwindow;
class Controller;
class View
{
public:
    static View *getInstance(unsigned int width = 0, unsigned int height = 0, const char *name = "");
    static void destroyInstance();

    void display(unsigned int ebo, Controller & controller);
    void framebuffer_size_callback(GLFWwindow *window, int width, int heigh);

    inline unsigned int getWidth() { return width; }
    inline unsigned int getHeight() { return height; }
    inline bool isInitialized() { return initialized; }

private:
    static View *instance;

    GLFWwindow *window;
    unsigned int width, height;
    bool initialized = false;

    View(unsigned int width, unsigned int height, const char *name);
    ~View();
};