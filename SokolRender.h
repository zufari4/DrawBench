#pragma once
#include "IRender.h"

class SokolRender : public IRender
{
public:
    bool init(int saplesCount, Color clearColor) override;
    void beginFrame() override;
    void endFrame() override;
    void drawShape(const BaseShape& shape) override;
};

