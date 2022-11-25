#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <stdexcept>

namespace EV
{
    class EV_Create_VkInstance
    {
    public:
        void operator()(VkInstance& instance);
    };
}