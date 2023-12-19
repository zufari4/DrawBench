#include "SdlRender.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_hints.h"
#include "CircleShape.h"
#include "RectagleShape.h"
#define _USE_MATH_DEFINES
#include <math.h>

#define PI2 6.28318530717958647692f


SdlRender::SdlRender(SDL_Window* window)
    : renderer_(nullptr)
    , window_(window)
    , clearColor_(0)
    , currVbOffset_(0)
    , currIbOffset_(0)
{
}

bool SdlRender::init(int saplesCount, Color clearColor)
{
    clearColor_ = clearColor;
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");
    SDL_SetHint(SDL_HINT_RENDER_LINE_METHOD, "3");
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, saplesCount);
    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer_ == nullptr) {
        return false;
    }
    SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_BLEND);
    vb_.resize(100000, { 0 });
    ib_.resize(100000*2, { 0 });

    return true;
}

void SdlRender::beginFrame()
{
    SDL_SetRenderDrawColor(renderer_, EXP_RGBA(clearColor_._));
    SDL_RenderClear(renderer_);
}

void SdlRender::endFrame()
{
    SDL_RenderPresent(renderer_);
}

SDL_Color getColor(Color c)
{
    return { EXP_RGBA(c._) };
}

void makeCircleVertexes(const CircleShape& shape, SDL_Vertex* vb, int* ib, int& vbCount, int& ibCount)
{
    int numSegments = getCircleNumSegments(shape.radius);
    const float theta = PI2 / float(numSegments);
    const float c = cosf(theta);
    const float s = sinf(theta);
    float t;
    float x = shape.radius;
    float y = 0;
    vbCount = 0;
    ibCount = 0;

    vb[vbCount].color = getColor(shape.color);
    vb[vbCount].position.x = shape.cx;
    vb[vbCount++].position.y = shape.cy;

    for (int i = 0; i < numSegments; i++) {
        vb[vbCount].color = getColor(shape.color);
        vb[vbCount].position.x = shape.cx + x;
        vb[vbCount++].position.y = shape.cy + y;
        t = x;
        x = c * x - s * y;
        y = s * t + c * y;
    }

    for (int i = 1; i < numSegments; ++i) {
        ib[ibCount++] = 0;
        ib[ibCount++] = i;
        ib[ibCount++] = i+1;
    }

    ib[ibCount++] = 0;
    ib[ibCount++] = 1;
    ib[ibCount++] = numSegments;
}

void makeRectVertexes(const RectagleShape& shape, SDL_Vertex* vb, int* ib, int& vbCount, int& ibCount)
{
    vbCount = 4;
    ibCount = 6;
    float hw = shape.w * 0.5f;
    float hh = shape.h * 0.5f;

    vb[0].color = getColor(shape.color);
    vb[0].position.x = shape.cx - hw;
    vb[0].position.y = shape.cy - hh;

    vb[1].color = getColor(shape.color);
    vb[1].position.x = shape.cx + hw;
    vb[1].position.y = shape.cy - hh;

    vb[2].color = getColor(shape.color);
    vb[2].position.x = shape.cx + hw;
    vb[2].position.y = shape.cy + hh;

    vb[3].color = getColor(shape.color);
    vb[3].position.x = shape.cx - hw;
    vb[3].position.y = shape.cy + hh;

    ib[0] = 0;
    ib[1] = 1;
    ib[2] = 3;
    ib[3] = 3;
    ib[4] = 2;
    ib[5] = 1;
}

void SdlRender::drawShape(const BaseShape& shape)
{
    int vbCount;
    int ibCount;
    SDL_Vertex* vb;
    int* ib;
    getVertexes(shape, &vb, &ib, vbCount, ibCount);
    SDL_RenderGeometry(renderer_, nullptr, vb, vbCount, ib, ibCount);
}

void SdlRender::getVertexes(const BaseShape& shape, SDL_Vertex** ppvb, int** ppib, int& vbCount, int& ibCount)
{
    const auto it = vbLink_.find(&shape);
    if (it == vbLink_.end()) {
        *ppvb = &vb_[currVbOffset_];
        *ppib = &ib_[currIbOffset_];

        if (shape.type == ShapeType::Rectangle) {
            makeRectVertexes((const RectagleShape&)shape, *ppvb, *ppib, vbCount, ibCount);
        }
        else if (shape.type == ShapeType::Circle) {
            makeCircleVertexes((const CircleShape&)shape, *ppvb, *ppib, vbCount, ibCount);
        }
        auto& place = vbLink_[&shape];
        place.vbOffset = currVbOffset_;
        place.ibOffset = currIbOffset_;
        place.vbCount  = vbCount;
        place.ibCount  = ibCount;

        currVbOffset_ += vbCount;
        currIbOffset_ += ibCount;
    }
    else {
        *ppvb = &vb_[it->second.vbOffset];
        *ppib = &ib_[it->second.ibOffset];
        vbCount = it->second.vbCount;
        ibCount = it->second.ibCount;
    }
}