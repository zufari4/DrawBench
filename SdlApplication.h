#pragma once

#include "IApplication.h"
#include <atomic>

struct SDL_Window;

class SdlApplication : public IApplication
{
public:
    SdlApplication();

    bool initialize(int w, int h, int samplesCount, Color clearColor) override;
    void run(DrawFrameCallback, KeyDownCallback) override;
    void stop() override;
    IRender& getRender() override;
    void getWindowsSize(int& w, int& h) override;
    void setWindowTitle(const std::string& title) override;

private:
    SDL_Window*   window_;
    RenderPtr     render_;
    std::atomic_bool workFlag_;
};

