#include "DrawBench.h"
#include "CircleShape.h"
#include "RectagleShape.h"
#include "HiResTimer.h"
#include <time.h>
#include <random>


DrawBench::DrawBench(IApplication& app)
    : app_(app)
    , render_(app.getRender())
    , countFrames_(0)
{
}

uint8_t randU8(uint8_t min = 0, uint8_t max = 255)
{
    static std::random_device rd;
    static std::mt19937 rng(rd());
    static std::uniform_int_distribution<unsigned short> uni(min, max);
    return (uint8_t)uni(rng);
}

Color randColor()
{
    return { randU8(),randU8(),randU8(),randU8(60, 255) };
}

void DrawBench::run(int countShapes, float shapeSize)
{
    int w, h;
    app_.getWindowsSize(w, h);
    const float stepX = (float)w / (float)countShapes;
    const float stepY = (float)h / (float)countShapes;
    float startShapeSize = shapeSize * 0.1f;
    bool createCircle = false;

    for (float posX = 0; posX < (float)w; posX += stepX)
        for (float posY = 0; posY < (float)h; posY += stepY)
        {
            createCircle = !createCircle;
            ShapeBasePtr shape;
            if (createCircle) {
                shape = std::make_unique<CircleShape>(startShapeSize*0.5f, posX, posY, randColor());
            }
            else {
                float x1 = posX - startShapeSize*0.5f;
                float y1 = posY - startShapeSize*0.5f;
                float x2 = posX + startShapeSize*0.5f;
                float y2 = posY + startShapeSize*0.5f;
                shape = std::make_unique<RectagleShape>(x1, y1, x2, y2, randColor());
            }
            shapes_.push_back(std::move(shape));
            startShapeSize += 0.1;
        }

    lastFrameCheck_ = Clock::now();
    app_.run(
        std::bind(&DrawBench::drawFrame, this),
        std::bind(&DrawBench::keyDownCallback, this, std::placeholders::_1)
    );
}

void DrawBench::drawFrame()
{
    static const auto oneSec = std::chrono::seconds(1);
    const auto& now = Clock::now();

    startDraw_ = hiTimer_.now();
    for (const auto& shape : shapes_)
        render_.drawShape(*shape);

    if (now - lastFrameCheck_ > oneSec) {
        double drawTime = hiTimer_.now() - startDraw_;
        std::string title = std::to_string(countFrames_) + "|" + std::to_string(drawTime);
        app_.setWindowTitle(title);
        countFrames_ = 0;
        lastFrameCheck_ = now;
    }
    countFrames_++;
}

void DrawBench::keyDownCallback(int key)
{
    if (key == 41) {
        app_.stop();
    }
}
