#pragma once
#include <inttypes.h>

union Color
{
    Color(int _i) : i((uint32_t)_i) {}
    Color(uint32_t _i) : i(_i) {}
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) : _{ a,b,g,r } {}
    Color(int r, int g, int b, int a = 255) : _{ (uint8_t)a,(uint8_t)b,(uint8_t)g,(uint8_t)r } {}
    uint32_t i;
    struct {
        uint8_t a;
        uint8_t b;
        uint8_t g;
        uint8_t r;
    } _;
};

struct Color4f
{
    Color4f(Color c)
        : r(c._.r / 255.0f)
        , g(c._.g / 255.0f)
        , b(c._.b / 255.0f)
        , a(c._.a / 255.0f)
    {}
    float r;
    float g;
    float b;
    float a;
};

#define EXP_RGBA(color) color.r, color.g, color.b, color.a