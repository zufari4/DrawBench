#pragma once
#include "BaseShape.h"
#include "Color.h"
#include <memory>


class IRender
{
public:
    IRender() {}
    virtual ~IRender() {}
    virtual void drawShape(const BaseShape& shape) = 0;
};

using RenderPtr = std::unique_ptr<IRender>;

