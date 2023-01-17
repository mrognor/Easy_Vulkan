#include <iostream>

#include "EV_App.h"
#include "EV_Window.h"
#include "EV_Instance.h"
#include "EV_Functions.h"
#include "EV_Device.h"

class MyApp : public EV::EV_App
{
private:
    EV::EV_Window Window;
    EV::EV_Instance Instance;
    EV::EV_Device Device;
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
        // Device.SetPhysicalDevice(0);
    }

    void Create() override 
    {
        Instance.Create();
        Window.Create();
        Device.Create();
    }

    void Run() override 
    {
        PrintInfo();

        Window.Tick();
    }

    void Cleanup() override 
    {
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

        std::vector<VkExtensionProperties> availalbleExtensions = Instance.GetAvailableExtensions();
        std::cout << "Available extensions:" << std::endl;
        for (const VkExtensionProperties& it : availalbleExtensions)
            std::cout << "\t" << it.extensionName << std::endl; 

        // Print info about validation layers
        std::vector<const char*> requiredValidationLayers = Instance.GetRequiredValidationLayers();
        std::cout << "Required validation layers:" << std::endl;
        for (const char*& it : requiredValidationLayers)
            std::cout << "\t" << it << std::endl;

        std::vector<VkLayerProperties> availalbleValidationLayers = Instance.GetAvailableValidationLayers();
        std::cout << "Available validation layers:" << std::endl;
        for (const VkLayerProperties& it : availalbleValidationLayers)
            std::cout << "\t" << it.layerName << std::endl;

        // Print info about available gpus
        std::vector<VkPhysicalDevice> physicalDevices = Device.GetPhysicalDevices();
        std::cout << "Available gpus:" << std::endl;
        for (const VkPhysicalDevice& it : physicalDevices)
        {
            EV::PrintVkPhysicalDeviceQueuesInfo(it, Window.GetWindowSurface(), "\t");
        }

        // Print info about picked gpu
        std::cout << "Picked gpu:" << std::endl;
        VkPhysicalDevice* pickedPhysicalDevice = Device.GetPickedPhysicalDevice();
        VkPhysicalDeviceProperties physicalDeviceProperties;
        vkGetPhysicalDeviceProperties(*pickedPhysicalDevice, &physicalDeviceProperties);
        std::cout << "\t" << physicalDeviceProperties.deviceName << std::endl;
    }
};

int main() 
{
    MyApp app;

    try 
    {
        app.Start();
    } 
    catch (const std::exception& e) 
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}