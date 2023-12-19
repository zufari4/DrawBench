#pragma once
#include "BaseShape.h"

struct RectagleShape: BaseShape
{
    RectagleShape(float cx, float cy, float w, float h, Color color)
        : BaseShape(ShapeType::Rectangle, color)
        , cx(cx)
        , cy(cy)
        , w(w)
        , h(h)
    {}
    float cx, cy;
    float w, h;
};

