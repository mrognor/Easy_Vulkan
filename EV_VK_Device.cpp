#include "EV_VK_Device.h"

namespace EV
{
    bool EV_VK_Device::IsPhysicalDeviceSuitable(const VkPhysicalDevice& physicalDevice)
    {
        // Get amount of queue families
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);

        // Get all queue families
        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies.data());

        int i = 0;
        bool wasFoundGraphicsQueue = false;
        int graphicsFamilyIndex;

        for (const auto& queueFamily : queueFamilies) 
        {
            if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) 
            {
                wasFoundGraphicsQueue = true;
                graphicsFamilyIndex = i;
                break;
            }
            i++;
        }

        return true;
    }

    std::vector<VkPhysicalDevice> EV_VK_Device::GetPhysicalDevices()
    {
        // Get all gpus supported vulkan amount
        uint32_t physicalDeviceCount = 0;
        vkEnumeratePhysicalDevices(*VulkanInstance->GetVkInstance(), &physicalDeviceCount, nullptr);
        
        // Get all gpus supported vulkan
        std::vector<VkPhysicalDevice> physicalDevices(physicalDeviceCount);
        vkEnumeratePhysicalDevices(*VulkanInstance->GetVkInstance(), &physicalDeviceCount, physicalDevices.data());
        return physicalDevices;
    }

    void EV_VK_Device::Create()
    {
        // Check if EV_VK_Instance variable was setup
        if (VulkanInstance == nullptr)
            throw std::runtime_error("From EV_VK_Device: You forget to setup EV_VK_Instance variable!");
        
        // Check if EV_VK_Instance variable was created before EV_VK_Device
        if (!VulkanInstance->IsCreated())
            throw std::runtime_error("From EV_VK_Device: You forget to create EV_VK_Instance variable!");

        // Get all gpus with vulkan support
        std::vector<VkPhysicalDevice> physicalDevices = GetPhysicalDevices();

        if (physicalDevices.size() == 0) 
            throw std::runtime_error("From EV_VK_Device: Failed to find GPUs with Vulkan support!");
            
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
