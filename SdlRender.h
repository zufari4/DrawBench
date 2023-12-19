#pragma once
#include "IRender.h"
#include <vector>
#include <map>

struct SDL_Renderer;
struct SDL_Window;
struct SDL_Vertex;

class SdlRender : public IRender
{
public:
    SdlRender(SDL_Window* window);
    bool init(int saplesCount, Color clearColor);
    void beginFrame();
    void endFrame();
    void drawShape(const BaseShape& shape) override;
private:
    void getVertexes(const BaseShape& shape, SDL_Vertex** pvb, int** ppib, int& vbCount, int& ibCount);

    SDL_Window* window_;
    SDL_Renderer* renderer_;
    Color clearColor_;
    std::vector<SDL_Vertex> vb_;
    std::vector<int> ib_;
    int currVbOffset_;
    int currIbOffset_;

    struct VbPos
    {
        int vbOffset;
        int ibOffset;
        int vbCount;
        int ibCount;
    };
    std::map<const BaseShape*, VbPos> vbLink_;
};

