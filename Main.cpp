#include "ApplicationFactory.h"
#include "DrawBench.h"

//#define ENGINE_SDL 1
#define ENGINE_SOKOL 1
//#define ENGINE_GLFW 1

#ifdef ENGINE_SDL
#define CREATE_APP() ApplicationFactory::createSdlApplication()
#endif
#ifdef ENGINE_SOKOL
#define CREATE_APP() ApplicationFactory::createSokolApplication()
#endif
#ifdef ENGINE_GLFW
#define CREATE_APP() ApplicationFactory::createGlfwApplication()
#endif

int main()
{
    auto app = CREATE_APP();

    if (!app->initialize(1280, 800, 8, {25,25,25}))
        return 1;
    DrawBench drawBench(*app);
    drawBench.run(30, 10);

    return 0;
}

