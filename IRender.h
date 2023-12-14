#pragma once
#include "BaseShape.h"
#include "Color.h"
#include <memory>


class IRender
{
public:
    IRender() {}
    virtual ~IRender() {}
    virtual bool init(int saplesCount, Color clearColor) = 0;
    virtual void beginFrame() = 0;
    virtual void endFrame() = 0;
    virtual void drawShape(const BaseShape& shape) = 0;
};

using RenderPtr = std::unique_ptr<IRender>;

