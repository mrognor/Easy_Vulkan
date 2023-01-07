#pragma once 

#include "EV_Classes.h"

namespace EV
{
    class EV_VK_Device
    {
    private:
        VkInstance* VulkanInstance = nullptr;
        
        VkPhysicalDevice PhysicalDevice = VK_NULL_HANDLE;

        bool IsPhysicalDeviceSuitable(const VkPhysicalDevice& physicalDevice);
    public: 
        void SetVkInstance(VkInstance* vulkanInstance) { VulkanInstance = vulkanInstance; }
        void Create();
    };
}