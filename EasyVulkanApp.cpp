#include <iostream>

#include "EV_App.h"
#include "EV_GLFW_Window.h"
#include "EV_VK_Instance.h"
#include "EV_VK_ValidationLayers.h"

class MyApp : public EV::EV_App
{
private:
    EV::EV_GLFW_Window GLFW_Window;
    EV::EV_VK_Instance VK_Instance;
    EV::EV_VK_ValidationLayers VK_ValidationLayers;
public:
    void Setup() override 
    {
        GLFW_Window.SetWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        
        VK_ValidationLayers.AddRequiredValidationLayer("VK_LAYER_KHRONOS_validation");

        VK_Instance.AddRequiredExtensions(GLFW_Window.GetRequiredExtensions());
        VK_Instance.AddRequiredValidationLayer("VK_LAYER_KHRONOS_validation");
    }

    void Create() override 
    {
        GLFW_Window.Create();
        VK_Instance.Create();
        VK_ValidationLayers.Create();
    }

    void MainLoop() override 
    {
        GLFW_Window.Tick();
    }

    void Cleanup() override 
    {
        VK_Instance.Destroy();
        GLFW_Window.Destroy();
    }
};

int main() 
{
    MyApp app;

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