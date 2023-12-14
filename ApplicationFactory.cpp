#include "ApplicationFactory.h"
#include "SdlApplication.h"
#include "GlfwApplication.h"
#include "SokolApplication.h"

namespace ApplicationFactory
{
    ApplicationPtr createSdlApplication()
    {
        return std::make_unique<SdlApplication>();
    }

    ApplicationPtr createGlfwApplication()
    {
        return std::make_unique<GlfwApplication>();
    }

    ApplicationPtr createSokolApplication()
    {
        return std::make_unique<SokolApplication>();
    }
}

