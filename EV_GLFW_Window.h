#pragma once 

#include "EV_Classes.h"

namespace EV
{
    class EV_GLFW_Window
    {
    private:
        GLFWwindow* GLFW_Window;

        int WindowWidth = 700;
        int WindowHeight = 500;
        std::string WindowTitle = "Easy Vulkan App";

    public:
        EV_GLFW_Window() { glfwInit(); /* Init window library */}

        GLFWwindow* GetGLFWWindow() { return GLFW_Window; }
        int GetWindowWidth() { return WindowWidth; }
        int GetWindowHeight() { return WindowHeight; }
        std::string GetWindowTitle() { return WindowTitle; }
        std::vector<const char*> GetRequiredExtensions();
        
        void SetWindowWidth(int windowWidth) { WindowWidth = windowWidth; }
        void SetWindowHeight(int windowHeight) { WindowHeight = windowHeight; }
        void SetWindowTitle(std::string windowTitle) { WindowTitle = windowTitle; }

        void Create();
        void Tick();
        void Destroy(); 

        /**
			\brief Wrapper function for glfwWindowHint

            You can find more information here https://www.glfw.org/docs/3.3/group__window.html#ga7d9c8c62384b1e2821c4dc48952d2033
			
            \param[in] hint The [window hint](window_hints) to set.
            \param[in] value The new value of the window hint.
		*/
        void SetWindowHint(int hint, int value);
    };
}