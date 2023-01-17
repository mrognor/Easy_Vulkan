#include "EV_Functions.h"

namespace EV
{
    void PrintVkPhysicalDeviceQueuesInfo(const VkPhysicalDevice& physicalDevice, VkSurfaceKHR* windowSurface, std::string prefix)
    {
        // Get amount of queue families
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);

        // Get all queue families
        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies.data());

        // Get device name
        VkPhysicalDeviceProperties physicalDeviceProperties;
        vkGetPhysicalDeviceProperties(physicalDevice, &physicalDeviceProperties);
        std::cout << prefix << physicalDeviceProperties.deviceName << std::endl;

        std::cout << prefix;
        switch (physicalDeviceProperties.deviceType)
        {
        case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
            std::cout << "\tGPU type: discrete" << std::endl;
            break;

        case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
            std::cout << "\tGPU type: integrated" << std::endl;
            break;

        case VK_PHYSICAL_DEVICE_TYPE_CPU:
            std::cout << "\tGPU type: CPU" << std::endl;
            break;

        case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
            std::cout << "\tGPU type: virtual" << std::endl;
            break;

        default:
            std::cout << "\tGPU type: other" << std::endl;
            break;
        }

        std::cout << prefix << "\tVendor ID: " << physicalDeviceProperties.vendorID << std::endl;
        std::cout << prefix << "\tDevice ID: " << physicalDeviceProperties.deviceID << std::endl;
        std::cout << prefix << "\tDriver version: " << physicalDeviceProperties.driverVersion << std::endl;
        std::cout << prefix << "\tVulkan API version: " << physicalDeviceProperties.apiVersion << std::endl;
        std::cout << prefix << "\tAvailable queues:" << std::endl;

        int i = 0;
        for (const auto& queueFamily : queueFamilies) 
        {
            // Check presentation support
            VkBool32 presentationSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i, *windowSurface, &presentationSupport);

            std::cout << prefix << "\t\tQueue " << std::to_string(i) << ": Graphics support: " << (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) 
                << " Presentation support: " << presentationSupport << std::endl;
            
            i++;
        }
    }
}