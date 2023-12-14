#pragma once
#include "IRender.h"
#include <functional>
#include <string>

using DrawFrameCallback = std::function<void(void)>;
using KeyDownCallback = std::function<void(int)>;

class IApplication
{
public:
    IApplication() {}
    virtual ~IApplication() {}
    virtual bool initialize(int w, int h, int samplesCount, Color clearColor) = 0;
    virtual void run(DrawFrameCallback, KeyDownCallback) = 0;
    virtual void stop() = 0;
    virtual IRender& getRender() = 0;
    virtual void getWindowsSize(int& w, int& h) = 0;
    virtual void setWindowTitle(const std::string& title) = 0;
};

using ApplicationPtr = std::unique_ptr<IApplication>;

