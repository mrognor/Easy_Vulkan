#include "EV_Window.h"

namespace EV
{
    EV_Window::EV_Window()
    {
        // Checking that it was possible to initialize library 
        if (!glfwInit())
            throw(std::runtime_error("From EV_Window::EV_Window: Failed to init glfw!"));
    }

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
        // Check if EV_Instance variable was setup
        if (Instance == nullptr)
            throw std::runtime_error("From EV_Window::Create: You forget to setup EV_Instance variable!");
        
        // Check if EV_Instance variable was created before EV_Window
        if (!Instance->GetIsCreated())
            throw std::runtime_error("From EV_Window::Create You forget to create EV_Instance variable! EV_Window must be created after EV_Instance!");

        // Inform the library that it is not necessary to create a OpenGL context
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        // Create GLFWwindow
        GLFW_Window = glfwCreateWindow(WindowWidth, WindowHeight, WindowTitle.c_str(), nullptr, nullptr);

        // Create window surface
        VkResult createWindowSurfaceResult = glfwCreateWindowSurface(*Instance->GetVkInstance(), GLFW_Window, nullptr, &WindowSurface);

        if (createWindowSurfaceResult != VK_SUCCESS)
            throw std::runtime_error("From EV_Window::Create: Failed to create window surface! glfwCreateWindowSurface error code: " + std::to_string(createWindowSurfaceResult));

        IsCreated = true;
    }

    void EV_Window::Tick()
    {
        // Window loop 
        while (!glfwWindowShouldClose(GLFW_Window)) 
            glfwPollEvents();
    }

    void EV_Window::Destroy()
    {
        if (!Instance->GetIsCreated())
            throw std::runtime_error("From EV_Window::Destroy: EV_Instance was destroyed earlier! EV_Window must be destroyed before EV_Instance!");
        
        // Destroy window surface
        vkDestroySurfaceKHR(*Instance->GetVkInstance(), WindowSurface, nullptr);
        // Destroy window
        glfwDestroyWindow(GLFW_Window);
        // Unload glfw library
        glfwTerminate();

        IsCreated = false;
    }

    void EV_Window::SetWindowHint(int hint, int value)
    {
        glfwWindowHint(hint, value);
    }
}