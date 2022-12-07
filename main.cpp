#include <iostream>
#include <stdexcept>

#include "EV_GLFWwindow.h"
#include "EV_VkInstance.h"
#include "EV_VkValidationLayers.h"

class VulkanApp
{
private:
    GLFWwindow* GLFW_Window;
    VkInstance VulkanInstance;
public:
    void Run() 
    {
        // Create GLFWwindow
        EV::EV_Create_GLFWwindow GLFWwindowCreateObject;
        // GLFWwindowCreateObject.WindowWidth = 1000;
        // GLFWwindowCreateObject.WindowHeight = 800;
        // GLFWwindowCreateObject.WindowTitle = "VkApp";
        GLFWwindowCreateObject(GLFW_Window);
        
        // Enable validation layers. 
        EV::EV_Enable_VkValidationLayers VkValidationLayersEnableObject;
        VkValidationLayersEnableObject();

        // Create VkInstance
        EV::EV_Create_VkInstance VkInstanceCreateObject;
        VkInstanceCreateObject(VulkanInstance);
        
        MainLoop();
        Cleanup();
    }

private:
    void MainLoop() 
    {
        while (!glfwWindowShouldClose(GLFW_Window)) 
        {
            glfwPollEvents();
        }
    }

    void Cleanup() 
    {
        EV::EV_Destroy_VkInstance(VulkanInstance);
        EV::EV_Destroy_GLFWwindow(GLFW_Window);
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