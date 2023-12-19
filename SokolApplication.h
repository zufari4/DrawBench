#pragma once
#include "IApplication.h"
#include <vector>
#include <map>

struct sgp_vec2;
struct CircleShape;
struct sapp_event;

class SokolApplication : public IApplication
{
public:
    SokolApplication();

    bool initialize(int w, int h, int samplesCount, Color clearColor) override;
    void run(DrawFrameCallback, KeyDownCallback) override;
    void stop() override;
    IRender& getRender() override;
    void getWindowsSize(int& w, int& h) override;
    void setWindowTitle(const std::string& title) override;

    void drawShape(const BaseShape& shape);
    void initGp();
    void drawFrame();
    void onEvent(const sapp_event* ev);

private:
    void queryPoints(const BaseShape& shape, sgp_vec2** ppVb, uint32_t& count);

    RenderPtr render_;
    int winWidth_;
    int winHeight_;
    int saplesCount_;
    Color4f clearColor_;
    DrawFrameCallback drawCb_;
    KeyDownCallback keyDownCb_;
    std::vector<sgp_vec2> vb_;
    int currVbOffset_;

    struct VbPos
    {
        int vbOffset;
        int vbCount;
    };
    std::map<const BaseShape*, VbPos> vbLink_;
};

