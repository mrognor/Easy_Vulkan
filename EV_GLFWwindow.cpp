#include "EV_GLFWwindow.h"

namespace EV
{
    void EV_Create_GLFWwindow::operator()(GLFWwindow* &window)
    {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        window = glfwCreateWindow(WindowWidth, WindowHeight, WindowTitle.c_str(), nullptr, nullptr);
    }

    void EV_Destroy_GLFWwindow(GLFWwindow* &window)
    {
        glfwDestroyWindow(window);
        glfwTerminate();
    }
}