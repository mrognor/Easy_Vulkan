#pragma once 

#include "EV_Classes.h"
#include "EV_Instance.h"
#include "EV_Window.h"

namespace EV
{
    // Required EV_Instance var
    class EV_Device
    {
    private:
        EV_Instance* Instance = nullptr;
        EV_Window* Window = nullptr;

        VkPhysicalDevice PhysicalDevice = VK_NULL_HANDLE;
        VkDevice LogicalDevice;
        VkQueue GraphicsQueue;
        VkQueue PresentationQueue;
        
        // Return false if one of queue family was not found. Put found indexec in 2 and 3 param
        bool GetQueueFamiliesIndexes(const VkPhysicalDevice& physicalDevice, uint32_t& graphicsFamilyIndex, uint32_t& presentationFamilyIndex);
    public: 
        /// This function return vector of physical devices with vulkan support
        std::vector<VkPhysicalDevice> GetPhysicalDevices();
        VkPhysicalDevice* GetPickedPhysicalDevice() { return &PhysicalDevice; }
        VkDevice* GetLogicalDevice() { return &LogicalDevice; }
        VkQueue* GetGraphicsQueue() { return &GraphicsQueue; }

        void SetInstance(EV_Instance* vulkanInstance) { Instance = vulkanInstance; }
        void SetWindow(EV_Window* window) { Window = window; }

        void Create();

        void Destroy();
    };
}