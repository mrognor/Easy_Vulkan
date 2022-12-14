#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>

namespace EV
{
    class EV_App;
    
    class EV_GLFW_Window;
    
    class EV_VK_Instance;
    class EV_VK_Device;
}