#include <iostream>
#include <stdexcept>

#include "EV_Init_GLFWwindow.h"

class VulkanApp
{
private:
    GLFWwindow* Window;
public:
    void Run() 
    {
        EV::EV_Init_GLFWwindow WindowCreateObject;
        // WindowCreateObject.WindowWidth = 1000;
        // WindowCreateObject.WindowHeight = 800;
        // WindowCreateObject.WindowTitle = "VkApp";
        WindowCreateObject(Window);

        InitVulkan();
        MainLoop();
        Cleanup();
    }

private:
    void InitVulkan()
    {

    }

    void MainLoop() 
    {
        while (!glfwWindowShouldClose(Window)) 
        {
            glfwPollEvents();
        }
    }

    void Cleanup() 
    {
        EV::EV_Cleanup_GLFWwindow(Window);
    }
};

int main() 
{
    VulkanApp app;

    try 
    {
        app.Run();
    } 
    catch (const std::exception& e) 
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}