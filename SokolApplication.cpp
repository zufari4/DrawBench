#include "SokolApplication.h"
#include "SokolRender.h"
#include "CircleShape.h"
#include "RectagleShape.h"
#define SOKOL_IMPL
#define SOKOL_D3D11
#define SOKOL_NO_ENTRY
#include "sokol_app.h"
#include "sokol_gfx.h"
#include "sokol_glue.h"
#include "sokol_gp.h"
#include <cmath>


SokolApplication* g_appPointer = nullptr;

void init()
{
    if (g_appPointer) g_appPointer->initGp();
}

void frame()
{
    if (g_appPointer) g_appPointer->drawFrame();
}

void event(const sapp_event* ev)
{
    if (g_appPointer) g_appPointer->onEvent(ev);
}

SokolApplication::SokolApplication()
    : winWidth_(0)
    , winHeight_(0)
    , saplesCount_(0)
    , clearColor_(Color(0))
    , render_(std::make_unique<SokolRender>(*this))
    , currVbOffset_(0)
{
}

bool SokolApplication::initialize(int w, int h, int samplesCount, Color clearColor)
{
    winWidth_ = w;
    winHeight_ = h;
    saplesCount_ = samplesCount;
    clearColor_ = Color(clearColor);
    g_appPointer = this;
    vb_.resize(100000, { 0 });

    return true;
}

void SokolApplication::run(DrawFrameCallback drawFrameCallback, KeyDownCallback keyDownCallback)
{
    drawCb_ = drawFrameCallback;
    keyDownCb_ = keyDownCallback;

    sapp_desc desc{ 0 };
    desc.init_cb = init;
    desc.frame_cb = frame;
    desc.event_cb = event;
    desc.width  = winWidth_;
    desc.height = winHeight_;
    desc.sample_count = saplesCount_;

    sapp_run(desc);

    sgp_shutdown();
    sg_shutdown();
}

void SokolApplication::stop()
{
    sapp_request_quit();
}

IRender& SokolApplication::getRender()
{
    return *render_.get();
}

void SokolApplication::getWindowsSize(int& w, int& h)
{
    w = winWidth_;
    h = winHeight_;
}

void SokolApplication::setWindowTitle(const std::string& title)
{
    sapp_set_window_title(title.c_str());
}

void SokolApplication::initGp()
{
    // Initialize Sokol GFX.
    sg_desc sgdesc{ 0 };
    sgdesc.context = sapp_sgcontext();
    sg_setup(&sgdesc);

    if(!sg_isvalid()) {
        fprintf(stderr, "Failed to create Sokol GFX context!\n");
        exit(-1);
    }

    // Initialize Sokol GP, adjust the size of command buffers for your own use.
    sgp_desc sgpdesc = {0};
    sgp_setup(&sgpdesc);
    if(!sgp_is_valid()) {
        fprintf(stderr, "Failed to create Sokol GP context: %s\n", sgp_get_error_message(sgp_get_last_error()));
        exit(-1);
    }
}

void SokolApplication::drawFrame()
{
    // begin draw commands queue
    int width = sapp_width(), height = sapp_height();
    sgp_begin(width, height);

    // draw background
    sgp_set_color(0.05f, 0.05f, 0.05f, 1.0f);
    sgp_clear();

    sgp_set_blend_mode(SGP_BLENDMODE_BLEND);

    if (drawCb_) drawCb_();

    // dispatch draw commands
    static const sg_pass_action pass_action = {0};
    sg_begin_default_pass(&pass_action, width, height);
    sgp_flush();
    sgp_end();
    sg_end_pass();
    sg_commit();
}

void SokolApplication::onEvent(const sapp_event* ev)
{
    if (ev->type == SAPP_EVENTTYPE_KEY_DOWN) {
        keyDownCb_((int)ev->key_code);
    }
}

#define PI2 6.28318530717958647692f

void makeCirclePoints(const CircleShape& shape, sgp_vec2* vb, uint32_t& vbCount)
{
    int numSegments = getCircleNumSegments(shape.radius)/3;
    if (numSegments < 3) numSegments = 3;
    const float theta = PI2 / float(numSegments);
    const float c = cosf(theta);
    const float s = sinf(theta);
    float t;
    float x = shape.radius;
    float y = 0;
    vbCount = 0;
    std::vector<sgp_vec2> tmp(numSegments, {0});

    for (int i = 0; i < numSegments; i++) {
        sgp_vec2& v = tmp[vbCount++];
        v.x = x;
        v.y = y;
        t = x;
        x = c * x - s * y;
        y = s * t + c * y;
    }
    vbCount = 0;
    vb[vbCount++] = tmp[0];

    int max = (int)std::ceilf((float)numSegments / 2.0f);
    for (int i = 1; i <= max; i++) {
        vb[vbCount++] = tmp[i];
        vb[vbCount++] = tmp[numSegments-i];
    }
}

void makeRectPoints(const RectagleShape& shape, sgp_vec2* vb, uint32_t& vbCount)
{
    vbCount = 4;
    float hw = shape.w * 0.5f;
    float hh = shape.h * 0.5f;

    vb[0].x = 0 - hw;
    vb[0].y = 0 - hh;

    vb[1].x = 0 + hw;
    vb[1].y = 0 - hh;

    vb[2].x = 0 - hw;
    vb[2].y = 0 + hh;

    vb[3].x = 0 + hw;
    vb[3].y = 0 + hh;
}

void SokolApplication::queryPoints(const BaseShape& shape, sgp_vec2** ppVb, uint32_t& count)
{
    const auto it = vbLink_.find(&shape);
    if (it == vbLink_.end()) {
        *ppVb = &vb_[currVbOffset_];
        if (shape.type == ShapeType::Circle) {
            makeCirclePoints((const CircleShape&)shape, *ppVb, count);
        }
        else if (shape.type == ShapeType::Rectangle) {
            makeRectPoints((const RectagleShape&)shape, *ppVb, count);
        }

        auto& place = vbLink_[&shape];
        place.vbOffset = currVbOffset_;
        place.vbCount  = count;

        currVbOffset_ += count;
    }
    else {
        *ppVb = &vb_[it->second.vbOffset];
        count = it->second.vbCount;
    }
}

void SokolApplication::drawShape(const BaseShape& shape)
{
    if (shape.type == ShapeType::Rectangle) {
        sgp_vec2* pVb;
        uint32_t count;
        const auto& rect = (const RectagleShape&)shape;
        queryPoints(rect, &pVb, count);

        Color4f c(shape.color);
        sgp_set_color(EXP_RGBA(c));
        sgp_push_transform();
        sgp_translate(rect.cx, rect.cy);
        sgp_rotate_at(rect.angle, 0, 0);
        
        sgp_draw_filled_triangles_strip(pVb, count);
        sgp_pop_transform();
    }
    else if (shape.type == ShapeType::Circle) {
        Color4f c(shape.color);
        sgp_set_color(c.r, c.g, c.b, 0.5f);
        sgp_vec2* pVb;
        uint32_t count;
        const auto& circle = (const CircleShape&)shape;
        queryPoints(circle, &pVb, count);

        sgp_push_transform();
        sgp_translate(circle.cx, circle.cy);
        sgp_rotate_at(circle.angle, 0, 0);
        sgp_draw_filled_triangles_strip(pVb, count);
        sgp_pop_transform();
    }
}