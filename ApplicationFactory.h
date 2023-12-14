#pragma once
#include "IApplication.h"
#include <memory>

class SdlApplication;
class GlfwApplication;
class SokolApplication;

namespace ApplicationFactory
{
    ApplicationPtr createSdlApplication();
    ApplicationPtr createGlfwApplication();
    ApplicationPtr createSokolApplication();
};

