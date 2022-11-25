#include <iostream>
#include <stdexcept>

#include "EV_GLFWwindow.h"
#include "EV_VkInstance.h"

class VulkanApp
{
private:
    GLFWwindow* GLFWwindow;
    VkInstance VulkanInstance;
public:
    void Run() 
    {
        // Create GLFWwindow
        EV::EV_Create_GLFWwindow GLFWwindowCreateObject;
        // GLFWwindowCreateObject.WindowWidth = 1000;
        // GLFWwindowCreateObject.WindowHeight = 800;
        // GLFWwindowCreateObject.WindowTitle = "VkApp";
        GLFWwindowCreateObject(GLFWwindow);
        
        // Create VkInstance
        EV::EV_Create_VkInstance VkInstanceCreateObject;
        VkInstanceCreateObject(VulkanInstance);

        MainLoop();
        Cleanup();
    }

private:
    void MainLoop() 
    {
        while (!glfwWindowShouldClose(GLFWwindow)) 
        {
            glfwPollEvents();
        }
    }

    void Cleanup() 
    {
        EV::EV_Destroy_GLFWwindow(GLFWwindow);
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