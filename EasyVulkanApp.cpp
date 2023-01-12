#include <iostream>

#include "EV_App.h"
#include "EV_GLFW_Window.h"
#include "EV_VK_Instance.h"
#include "EV_Functions.h"
#include "EV_VK_Device.h"

class MyApp : public EV::EV_App
{
private:
    EV::EV_GLFW_Window GLFW_Window;
    EV::EV_VK_Instance VK_Instance;
    EV::EV_VK_Device VK_Device;
public:
    void Setup() override 
    {
        GLFW_Window.SetWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        VK_Instance.AddRequiredExtensions(GLFW_Window.GetRequiredExtensions());
        VK_Instance.AddRequiredExtension("VK_EXT_debug_utils");
        VK_Instance.AddRequiredValidationLayer("VK_LAYER_KHRONOS_validation");

        VK_Device.SetVkInstance(&VK_Instance);
    }

    void Create() override 
    {
        GLFW_Window.Create();
        VK_Instance.Create();
        VK_Device.Create();
    }

    void Run() override 
    {
        PrintInfo();

        GLFW_Window.Tick();
    }

    void Cleanup() override 
    {
        VK_Instance.Destroy();

        GLFW_Window.Destroy();
    }

    void PrintInfo()
    {
                // Print info about extensions
        std::vector<const char*> requiredExtensions = VK_Instance.GetRequiredExtensions();
        std::cout << "Required extensions:" << std::endl;
        for (const char*& it : requiredExtensions)
            std::cout << "\t" << it << std::endl; 

        std::vector<VkExtensionProperties> availalbleExtensions = VK_Instance.GetAvailableExtensions();
        std::cout << "Available extensions:" << std::endl;
        for (const VkExtensionProperties& it : availalbleExtensions)
            std::cout << "\t" << it.extensionName << std::endl; 

        // Print info about validation layers
        std::vector<const char*> requiredValidationLayers = VK_Instance.GetRequiredValidationLayers();
        std::cout << "Required validation layers:" << std::endl;
        for (const char*& it : requiredValidationLayers)
            std::cout << "\t" << it << std::endl;

        std::vector<VkLayerProperties> availalbleValidationLayers = VK_Instance.GetAvailableValidationLayers();
        std::cout << "Available validation layers:" << std::endl;
        for (const VkLayerProperties& it : availalbleValidationLayers)
            std::cout << "\t" << it.layerName << std::endl;

        // Print info about available gpus
        std::vector<VkPhysicalDevice> physicalDevices = VK_Device.GetPhysicalDevices();
        std::cout << "Available gpus:" << std::endl;
        for (const VkPhysicalDevice& it : physicalDevices)
        {
            VkPhysicalDeviceProperties physicalDeviceProperties;
            vkGetPhysicalDeviceProperties(it, &physicalDeviceProperties);
            std::cout << "\t" << physicalDeviceProperties.deviceName << std::endl;
        }

        // Print info about picked gpu
        std::cout << "Picked gpu:" << std::endl;
        VkPhysicalDevice* pickedPhysicalDevice = VK_Device.GetPickedPhysicalDevice();
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