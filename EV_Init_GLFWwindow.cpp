#include "EV_Init_GLFWwindow.h"

namespace EV
{
    void EV_Init_GLFWwindow::operator()(GLFWwindow* &window)
    {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        window = glfwCreateWindow(WindowWidth, WindowHeight, WindowTitle.c_str(), nullptr, nullptr);
    }

    void EV_Cleanup_GLFWwindow(GLFWwindow* &window)
    {
        glfwDestroyWindow(window);
        glfwTerminate();
    }
}