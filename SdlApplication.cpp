#include "SdlApplication.h"
#include "SdlRender.h"
#include "SDL2/SDL.h"


SdlApplication::SdlApplication()
    : window_(nullptr)
{

}

bool SdlApplication::initialize(int w, int h, int samplesCount, Color clearColor)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        return false;
    }

    uint32_t flags = SDL_WINDOW_SHOWN;
    window_ = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);
    if (window_ == nullptr) {
        return false;
    }

    render_ = std::make_unique<SdlRender>(window_);
    if (!render_->init(samplesCount, clearColor)) {
        return false;
    }
    return true;
}

void SdlApplication::run(DrawFrameCallback drawFrameCallback, KeyDownCallback keyDownCallback)
{
    static SDL_Event event;
    workFlag_ = true;

    while (workFlag_)
    {
        while (SDL_PollEvent(&event)) {
            switch (event.type)
            {
            case SDL_QUIT:
                workFlag_ = false;
                break;
            case SDL_KEYDOWN: {
                SDL_KeyboardEvent& ev = (SDL_KeyboardEvent&)event;
                keyDownCallback(ev.keysym.scancode);
            } break;
            }
        }

        render_->beginFrame();
        drawFrameCallback();
        render_->endFrame();
    }
}

void SdlApplication::stop()
{
    workFlag_ = false;
}

IRender& SdlApplication::getRender()
{
    return *render_.get();
}

void SdlApplication::getWindowsSize(int& w, int& h)
{
    SDL_GetWindowSize(window_, &w, &h);
}

void SdlApplication::setWindowTitle(const std::string& title)
{
    SDL_SetWindowTitle(window_, title.c_str());
}
