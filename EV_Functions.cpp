#include "EV_Functions.h"

namespace EV
{
    void PrintVkPhysicalDeviceQueuesInfo(const VkPhysicalDevice& physicalDevice, VkSurfaceKHR* windowSurface)
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
        std::cout << "Device name: " << physicalDeviceProperties.deviceName << std::endl;

        int i = 0;
        for (const auto& queueFamily : queueFamilies) 
        {
            // Check presentation support
            VkBool32 presentationSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i, *windowSurface, &presentationSupport);

            std::cout << "\tQueue " << std::to_string(i) << ": Graphics support: " << (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) 
                << " Presentation support: " << presentationSupport << std::endl;
            
            i++;
        }
    }
}