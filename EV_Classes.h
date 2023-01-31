#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <map>
#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>

namespace EV
{
    class EV_App;
    
    class EV_Window;
    
    class EV_Instance;
    class EV_Device;
    class EV_Swapchain;
    class EV_GraphicsPipeline;
}