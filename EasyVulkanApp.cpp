#include <iostream>

#include "EV_App.h"
#include "EV_GLFW_Window.h"
#include "EV_VK_Instance.h"
#include "EV_VK_ValidationLayers.h"
#include "EV_Functions.h"

class MyApp : public EV::EV_App
{
private:
    EV::EV_GLFW_Window GLFW_Window;
    EV::EV_VK_Instance VK_Instance;

    #ifndef NDEBUG
    EV::EV_VK_ValidationLayers VK_ValidationLayers{VK_Instance.GetVkInstance()};
    #endif

public:
    void Setup() override 
    {
        GLFW_Window.SetWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        
        #ifndef NDEBUG
        VK_ValidationLayers.AddRequiredValidationLayer("VK_LAYER_KHRONOS_validation");
        VK_ValidationLayers.SetValidationLayersMessageHandler(EV::EV_DefaultValidationLayersCallback);
        #endif

        VK_Instance.AddRequiredExtensions(GLFW_Window.GetRequiredExtensions());

        #ifndef NDEBUG
        VK_Instance.AddRequiredExtension("VK_EXT_debug_utils");
        VK_Instance.AddRequiredValidationLayer("VK_LAYER_KHRONOS_validation");
        VK_Instance.SetDebugMessengerCreateInfo(VK_ValidationLayers.GetDebugMessengerCreateInfo());
        #endif

    }

    void Create() override 
    {
        GLFW_Window.Create();
        VK_Instance.Create();

        #ifndef NDEBUG
        VK_ValidationLayers.Create();
        #endif
    }

    void MainLoop() override 
    {
        GLFW_Window.Tick();
    }

    void Cleanup() override 
    {
        #ifndef NDEBUG
        VK_ValidationLayers.Destroy();
        #endif

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