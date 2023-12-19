#pragma once
#include "IRender.h"

class SokolApplication;

class SokolRender : public IRender
{
public:
    SokolRender(SokolApplication& app);
    void drawShape(const BaseShape& shape) override;

private:
    SokolApplication* app_;

};

