#pragma once

class GLFWwindow;
class Controller;
class View
{
public:
    static View *getInstance(unsigned short width = 0, unsigned short height = 0, const char *name = "");
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

    View(unsigned short width, unsigned short height, const char *name);
    ~View();
};