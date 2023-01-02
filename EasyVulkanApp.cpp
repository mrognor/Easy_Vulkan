#include <iostream>

#include "EV_App.h"
#include "EV_GLFW_Window.h"
#include "EV_VK_Instance.h"

class MyApp : public EV::EV_App
{
private:
    EV::EV_GLFW_Window GLFW_Window;
    EV::EV_VK_Instance VK_Instance;
public:
    void Setup() override 
    {
        GLFW_Window.SetWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        VK_Instance.AddRequiredExtensions(GLFW_Window.GetRequiredExtensions());
    }

    void Create() override 
    {
        GLFW_Window.Create();
        VK_Instance.Create();
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