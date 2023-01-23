#include <iostream>

#include "EV_App.h"
#include "EV_Window.h"
#include "EV_Instance.h"
#include "EV_Functions.h"
#include "EV_Device.h"
#include "EV_Swapchain.h"

class MyApp : public EV::EV_App
{
private:
    EV::EV_Window Window;
    EV::EV_Instance Instance;
    EV::EV_Device Device;
    EV::EV_Swapchain Swapchain;
public:
    void Setup() override 
    {
        Window.SetWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        Window.SetInstance(&Instance);

        Instance.AddRequiredExtensions(Window.GetRequiredExtensions());
        Instance.AddRequiredExtension("VK_EXT_debug_utils");
        Instance.AddRequiredValidationLayer("VK_LAYER_KHRONOS_validation");

        Device.SetInstance(&Instance);
        Device.SetWindow(&Window);
        Device.AddRequiredExtension("VK_KHR_swapchain");
        // Device.SetPhysicalDevice(0);

        Swapchain.SetWindow(&Window);
        Swapchain.SetDevice(&Device);
        // Swapchain.SetPickWindowSurfaceFormatFunc(PickWindowSurfaceFormat);
        // Swapchain.SetPickWindowSurfacePresentationModeFunc(PickkWindowSurfacePresentationMode);
    }

    void Create() override 
    {
        Instance.Create();
        Window.Create();
        Device.Create();
        Swapchain.Create();
    }

    void OnStart() override 
    {
        PrintInfo();
    }

    void Tick() override
    {
        Window.Tick();
    }

    void OnEnd() override
    {

    }

    void Cleanup() override 
    {
        Swapchain.Destroy();
        Device.Destroy();
        Window.Destroy();
        Instance.Destroy();
    }

    void PrintInfo()
    {
        // Print info about extensions
        std::vector<const char*> requiredExtensions = Instance.GetRequiredExtensions();
        std::cout << "Required extensions:" << std::endl;
        for (const char*& it : requiredExtensions)
            std::cout << "\t" << it << std::endl; 
        std::cout << std::endl; 

        std::vector<VkExtensionProperties> availalbleExtensions = Instance.GetAvailableExtensions();
        std::cout << "Available extensions:" << std::endl;
        for (const VkExtensionProperties& it : availalbleExtensions)
            std::cout << "\t" << it.extensionName << std::endl; 
        std::cout << std::endl;

        // Print info about validation layers
        std::vector<const char*> requiredValidationLayers = Instance.GetRequiredValidationLayers();
        std::cout << "Required validation layers:" << std::endl;
        for (const char*& it : requiredValidationLayers)
            std::cout << "\t" << it << std::endl;
        std::cout << std::endl;

        std::vector<VkLayerProperties> availableValidationLayers = Instance.GetAvailableValidationLayers();
        std::cout << "Available validation layers:" << std::endl;
        for (const VkLayerProperties& it : availableValidationLayers)
            std::cout << "\t" << it.layerName << std::endl;
        std::cout << std::endl;

        std::vector<const char*> requiredDeviceExtensions = Device.GetRequiredExtensions();
        std::cout << "Required device extensions:" << std::endl;
        for (const char*& it : requiredDeviceExtensions) 
            std::cout << "\t" << it << std::endl;
        std::cout << std::endl;

        // Print info about available gpus
        std::vector<VkPhysicalDevice> physicalDevices = Device.GetPhysicalDevices();
        std::cout << "Available gpus:" << std::endl;
        for (const VkPhysicalDevice& it : physicalDevices)
        {
            EV::PrintVkPhysicalDeviceQueuesInfo(it, Window.GetWindowSurface(), "\t");
            std::cout << std::endl;
        }

        // Print info about picked gpu
        std::cout << "Picked gpu:" << std::endl;
        VkPhysicalDevice* pickedPhysicalDevice = Device.GetPickedPhysicalDevice();
        VkPhysicalDeviceProperties physicalDeviceProperties;
        vkGetPhysicalDeviceProperties(*pickedPhysicalDevice, &physicalDeviceProperties);
        std::cout << "\t" << physicalDeviceProperties.deviceName << std::endl;

        // Print info about picked gpu queues
        std::cout << "\tPicked gpu graphics queue:" << std::endl;
        std::cout << "\t\t" << Device.GetGraphicsQueueIndex() << std::endl;
        std::cout << "\tPicked gpu presentation queue:" << std::endl;
        std::cout << "\t\t" << Device.GetPresentationQueueIndex() << std::endl;
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