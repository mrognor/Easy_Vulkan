#include "EV_Window.h"

namespace EV
{
    std::vector<const char*> EV_Window::GetRequiredExtensions()
    {
        // Get the number of necessary vulkan extensions for glfw to work and their list
        uint32_t glfwRequiredExtensionCount = 0;
        const char** glfwRequiredExtensions;
        glfwRequiredExtensions = glfwGetRequiredInstanceExtensions(&glfwRequiredExtensionCount);

        // Return required extensions
        return std::vector<const char*> (glfwRequiredExtensions, glfwRequiredExtensions + glfwRequiredExtensionCount);
    }

    void EV_Window::Create()
    {
        // Inform the library that it is not necessary to create a OpenGL context
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        // Create GLFWwindow
        GLFW_Window = glfwCreateWindow(WindowWidth, WindowHeight, WindowTitle.c_str(), nullptr, nullptr);
    }

    void EV_Window::Tick()
    {
        // Window loop 
        while (!glfwWindowShouldClose(GLFW_Window)) 
            glfwPollEvents();
    }

    void EV_Window::Destroy()
    {
        // Destroy window
        glfwDestroyWindow(GLFW_Window);
        // Unload glfw library
        glfwTerminate();
    }

    void EV_Window::SetWindowHint(int hint, int value)
    {
        glfwWindowHint(hint, value);
    }
}