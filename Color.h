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

#define EXP_RGBA(color) color._.r, color._.g, color._.b, color._.a