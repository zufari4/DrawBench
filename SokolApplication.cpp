#include "SokolApplication.h"
#include "SokolRender.h"

bool SokolApplication::initialize(int w, int h, int samplesCount, Color clearColor)
{
    render_ = std::make_unique<SokolRender>();
    return render_->init(samplesCount, clearColor);
}

void SokolApplication::run(DrawFrameCallback drawFrameCallback, KeyDownCallback keyDownCallback)
{

}

void SokolApplication::stop()
{

}

IRender& SokolApplication::getRender()
{
    return *render_.get();
}

void SokolApplication::getWindowsSize(int& w, int& h)
{

}

void SokolApplication::setWindowTitle(const std::string& title)
{

}
