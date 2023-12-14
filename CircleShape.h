#pragma once
#include "BaseShape.h"
#include <functional>

struct CircleShape: BaseShape
{
    CircleShape(float radius, float cx, float cy, Color color) 
        : BaseShape(ShapeType::Circle, color)
        , radius(radius)
        , cx(cx)
        , cy(cy)
    {
    }

    float radius;
    float cx;
    float cy;
};

int  getCircleNumSegments(float radius);
