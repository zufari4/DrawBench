#pragma once
#include "IApplication.h"

class SokolApplication : public IApplication
{
public:
    bool initialize(int w, int h, int samplesCount, Color clearColor) override;
    void run(DrawFrameCallback, KeyDownCallback) override;
    void stop() override;
    IRender& getRender() override;
    void getWindowsSize(int& w, int& h) override;
    void setWindowTitle(const std::string& title) override;

private:
    RenderPtr render_;
};

