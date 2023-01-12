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
        /// This function return vector of physical devices with vulkan support
        std::vector<VkPhysicalDevice> GetPhysicalDevices();
        VkPhysicalDevice* GetPickedPhysicalDevice() { return &PhysicalDevice; }

        void SetVkInstance(VkInstance* vulkanInstance) { VulkanInstance = vulkanInstance; }
        void Create();
    };
}