#include "SokolRender.h"
#include "SokolApplication.h"


SokolRender::SokolRender(SokolApplication& app)
    : app_(&app)
{

}

void SokolRender::drawShape(const BaseShape& shape)
{
    app_->drawShape(shape);
}
