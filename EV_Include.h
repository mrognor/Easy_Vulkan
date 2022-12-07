#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>

namespace EV
{
    // Vector with all required validation layers
    extern std::vector<const char*> RequiredValidationLayers;
}