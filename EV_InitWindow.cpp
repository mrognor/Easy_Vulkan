#include "EV_InitWindow.h"

namespace EV
{
    void EV_InitWindow::operator()(GLFWwindow* &window)
    {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        window = glfwCreateWindow(WindowWidth, WindowHeight, WindowTitle.c_str(), nullptr, nullptr);
    }

    void EV_CleanupWindow(GLFWwindow* &window)
    {
        glfwDestroyWindow(window);
        glfwTerminate();
    }
}