#pragma once
#include "IApplication.h"
#include "IRender.h"
#include "HiResTimer.h"
#include <vector>
#include <chrono>


class DrawBench
{
public:
    DrawBench(IApplication& app);
    void run(int countShapes, float shapeSize);

private:
    void drawFrame();
    void keyDownCallback(int key);

    using Clock = std::chrono::high_resolution_clock;

    IApplication& app_;
    IRender& render_;
    std::vector<ShapeBasePtr> shapes_;
    double startDraw_;
    Clock::time_point lastFrameCheck_;
    uint32_t countFrames_;
    HiResTimer hiTimer_;
};

