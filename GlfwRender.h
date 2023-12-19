#pragma once
#include "IRender.h"

class GlfwRender : public IRender
{
public:
    bool init(int saplesCount, Color clearColor);
    void beginFrame();
    void endFrame();
    void drawShape(const BaseShape& shape) override;
};

