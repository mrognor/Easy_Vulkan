#pragma once 

#include "EV_Classes.h"
#include "EV_VK_Instance.h"

namespace EV
{
    // Required EV_VK_Instance var
    class EV_VK_Device
    {
    private:
        EV_VK_Instance* VulkanInstance = nullptr;
        
        VkPhysicalDevice PhysicalDevice = VK_NULL_HANDLE;

        bool IsPhysicalDeviceSuitable(const VkPhysicalDevice& physicalDevice);
    public: 
        /// This function return vector of physical devices with vulkan support
        std::vector<VkPhysicalDevice> GetPhysicalDevices();
        VkPhysicalDevice* GetPickedPhysicalDevice() { return &PhysicalDevice; }

        void SetVkInstance(EV_VK_Instance* vulkanInstance) { VulkanInstance = vulkanInstance; }
        void Create();
    };
}