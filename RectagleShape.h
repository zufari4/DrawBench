#pragma once
#include "BaseShape.h"

struct RectagleShape: BaseShape
{
    RectagleShape(float x1, float y1, float x2, float y2, Color color)
        : BaseShape(ShapeType::Rectangle, color)
        , x1(x1)
        , y1(y1)
        , x2(x2)
        , y2(y2)
    {}
    float x1, y1;
    float x2, y2;
};

