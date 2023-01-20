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

        std::vector<const char*> RequiredExtensions;
        // Bool variable to store info about picking physical device
        bool IsPreferredDeviceSet = false;
        // Variable to store preferred device id
        uint32_t PreferredDeviceID;

        // Return false if one of queue family was not found. Put found indexec in 2 and 3 param
        bool GetQueueFamiliesIndexes(const VkPhysicalDevice& physicalDevice, uint32_t& graphicsFamilyIndex, uint32_t& presentationFamilyIndex);
    public: 
        /// This function return vector of physical devices with vulkan support
        std::vector<VkPhysicalDevice> GetPhysicalDevices();
        VkPhysicalDevice* GetPickedPhysicalDevice() { return &PhysicalDevice; }
        VkDevice* GetLogicalDevice() { return &LogicalDevice; }
        VkQueue* GetGraphicsQueue() { return &GraphicsQueue; }
        std::vector<VkExtensionProperties> GetAvailableExtensions(const VkPhysicalDevice& physicalDevice);
        std::vector<const char*> GetRequiredExtensions() { return RequiredExtensions; }

        void AddRequiredExtension(const char* requiredExtension) { RequiredExtensions.push_back(requiredExtension); };
        void AddRequiredExtensions(const std::vector<const char*>& requiredExtensions) { RequiredExtensions.insert(RequiredExtensions.end(), requiredExtensions.begin(), requiredExtensions.end()); };
        void SetInstance(EV_Instance* vulkanInstance) { Instance = vulkanInstance; }
        void SetWindow(EV_Window* window) { Window = window; }
        // Function to set physical device
        void SetPhysicalDevice(uint32_t deviceID) { IsPreferredDeviceSet = true; PreferredDeviceID = deviceID; };

        void Create();

        void Destroy();
    };
}