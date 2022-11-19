#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>

namespace EV
{
    class EV_InitWindow
    {
    public:
        int WindowWidth = 800;
        int WindowHeight = 600;
        std::string WindowTitle = "Vulkan app";

        void operator()(GLFWwindow* &window);
    };

    void EV_CleanupWindow(GLFWwindow* &window);
}   