#include "ApplicationFactory.h"
#include "DrawBench.h"

int main()
{
    auto app = ApplicationFactory::createSdlApplication();
    if (!app->initialize(1280, 800, 6, {25,25,25}))
        return 1;
    DrawBench drawBench(*app);
    drawBench.run(30, 10);

    return 0;
}

