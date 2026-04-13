#pragma once

class View;
class Generator;

class Controller
{
public:
    static Controller *getInstance(unsigned short width = 0, unsigned short height = 0, const char *name = "");
    static void destroyInstance();

    void run();
    bool isInitialized();

    void update();

private:
    static Controller *instance;
    Controller(unsigned short width, unsigned short height, const char *name);
    ~Controller();

    View *view = nullptr;
    Generator *generator = nullptr;

    unsigned int vbo, ebo, vao;

};