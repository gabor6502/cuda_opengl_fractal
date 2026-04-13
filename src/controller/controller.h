#pragma once

class View;

class Controller
{
public:
    static Controller *getInstance(unsigned int width = 0, unsigned int height = 0, const char *name = "");
    static void destroyInstance();

    void run();
    bool isInitialized();

    void update();

private:
    static Controller *instance;
    Controller(unsigned int width, unsigned int height, const char *name);
    ~Controller();

    View *view = nullptr;
    unsigned int vbo, ebo, vao;

};