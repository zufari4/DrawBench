#include "GlfwApplication.h"
#include "GlfwRender.h"


bool GlfwApplication::initialize(int w, int h, int samplesCount, Color clearColor)
{
    render_ = std::make_unique<GlfwRender>();
    return ((GlfwRender*)render_.get())->init(samplesCount, clearColor);
}

void GlfwApplication::run(DrawFrameCallback drawFrameCallback, KeyDownCallback keyDownKallback)
{

}

void GlfwApplication::stop()
{

}

IRender& GlfwApplication::getRender()
{
    return *render_.get();
}

void GlfwApplication::getWindowsSize(int& w, int& h)
{

}

void GlfwApplication::setWindowTitle(const std::string& title)
{

}
