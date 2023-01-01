#include "EV_GLFW_Window.h"

namespace EV
{
    void EV_GLFW_Window::Create()
    {
        // Inform the library that it is not necessary to create a OpenGL context
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        // Create GLFWwindow
        GLFW_Window = glfwCreateWindow(WindowWidth, WindowHeight, WindowTitle.c_str(), nullptr, nullptr);
    }

    void EV_GLFW_Window::Tick()
    {
        // Window loop 
        while (!glfwWindowShouldClose(GLFW_Window)) 
            glfwPollEvents();
    }

    void EV_GLFW_Window::Destroy()
    {
        // Destroy window
        glfwDestroyWindow(GLFW_Window);
        // Unload glfw library
        glfwTerminate();
    }

    void EV_GLFW_Window::SetWindowHint(int hint, int value)
    {
        glfwWindowHint(hint, value);
    }
}