#pragma once
#include <memory>
#include <inttypes.h>
#include "Color.h"

enum class ShapeType
{
    Undefined,
    Circle,
    Rectangle
};

struct BaseShape
{
    BaseShape(ShapeType type, Color color)
        : type(type)
        , color(color)
    {}
    ShapeType type;
    Color color;
};

using ShapeBasePtr = std::unique_ptr<BaseShape>;

