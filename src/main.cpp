#include <iostream>
#include <controller.h>

#define WIDTH 800
#define HEIGHT 800
#define NAME "Cuda Fractal"

int main()
{

    printf("Initializing ... ");
    Controller *controller = Controller::getInstance(WIDTH, HEIGHT, NAME);
    printf("done.\n");

    if (!controller->isInitialized())
    {
        printf("Failed to initialize.\n");
        return -1;
    }

    printf("Running ... ");
    controller->run();
    printf("done.\n");


    printf("Deallocating ... ");
    Controller::destroyInstance();
    printf("done.\n");


    printf("\nEnd of line.\n");
    return 0;
}