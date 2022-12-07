#pragma once

#include "EV_Include.h"

namespace EV
{
    class EV_Create_GLFWwindow
    {
    public:
        int WindowWidth = 800;
        int WindowHeight = 600;
        std::string WindowTitle = "Vulkan app";

        void operator()(GLFWwindow* &window);
    };

    void EV_Destroy_GLFWwindow(GLFWwindow* &window);
}   