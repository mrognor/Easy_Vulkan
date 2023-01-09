#include "EV_VK_Device.h"

namespace EV
{
    bool EV_VK_Device::IsPhysicalDeviceSuitable(const VkPhysicalDevice& physicalDevice)
    {
        return true;
    }

    void EV_VK_Device::Create()
    {
        if (VulkanInstance == nullptr)
            throw std::runtime_error("From EV_VK_Device: You forget to setup VkInstance variable!");

        // Get all gpus supported vulkan amount
        uint32_t physicalDeviceCount = 0;
        vkEnumeratePhysicalDevices(*VulkanInstance, &physicalDeviceCount, nullptr);

        if (physicalDeviceCount == 0) 
            throw std::runtime_error("From EV_VK_Device: Failed to find GPUs with Vulkan support!");
        
        // Get all gpus supported vulkan
        std::vector<VkPhysicalDevice> physicalDevices(physicalDeviceCount);
        vkEnumeratePhysicalDevices(*VulkanInstance, &physicalDeviceCount, physicalDevices.data());
    
        // Find first suitable device. Have to write code to pich discrete gpu
        bool wasPickedGPU = false;
        for (const VkPhysicalDevice& physicalDevice : physicalDevices)
        {
            if (IsPhysicalDeviceSuitable(physicalDevice))
            {
                // Get physical device properties
                VkPhysicalDeviceProperties physicalDeviceProperties;
                vkGetPhysicalDeviceProperties(physicalDevice, &physicalDeviceProperties);

                if (wasPickedGPU == false)
                {
                    PhysicalDevice = physicalDevice;
                    wasPickedGPU = true;
                    continue;
                }
                else 
                {
                    if (physicalDeviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
                    {
                        PhysicalDevice = physicalDevice;
                        break;
                    }
                }
            }
        }

        if (wasPickedGPU == false)
            throw std::runtime_error("From EV_VK_Device: Failed to find suitable gpu!");

        // Get physical device properties
        VkPhysicalDeviceProperties physicalDeviceProperties;
        vkGetPhysicalDeviceProperties(PhysicalDevice, &physicalDeviceProperties);
        std::cout << physicalDeviceProperties.deviceName << std::endl;
    }   
}
