#pragma once 

#include "EV_Classes.h"
#include "EV_Instance.h"

namespace EV
{
    // Required EV_Instance var
    class EV_Device
    {
    private:
        EV_Instance* Instance = nullptr;
        VkPhysicalDevice PhysicalDevice = VK_NULL_HANDLE;
        VkDevice LogicalDevice;
        VkQueue GraphicsQueue;

        // Return false if one of them was not found
        bool GetQueueFamiliesIndexes(const VkPhysicalDevice& physicalDevice, uint32_t& graphicsFamilyIndex);
    public: 
        /// This function return vector of physical devices with vulkan support
        std::vector<VkPhysicalDevice> GetPhysicalDevices();
        VkPhysicalDevice* GetPickedPhysicalDevice() { return &PhysicalDevice; }
        VkDevice* GetLogicalDevice() { return &LogicalDevice; }
        VkQueue* GetGraphicsQueue() { return &GraphicsQueue; }

        void SetVkInstance(EV_Instance* vulkanInstance) { Instance = vulkanInstance; }
        void Create();

        void Destroy();
    };
}