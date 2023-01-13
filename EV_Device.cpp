#include "EV_Device.h"

namespace EV
{
    bool EV_Device::GetQueueFamiliesIndexes(const VkPhysicalDevice& physicalDevice, uint32_t& graphicsFamilyIndex)
    {
        // Get amount of queue families
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);

        // Get all queue families
        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies.data());

        int i = 0;
        bool wasFoundGraphicsQueue = false;

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

        if (wasFoundGraphicsQueue)
            return true;
        else return false;
    }

    std::vector<VkPhysicalDevice> EV_Device::GetPhysicalDevices()
    {
        // Get all gpus supported vulkan amount
        uint32_t physicalDeviceCount = 0;
        vkEnumeratePhysicalDevices(*Instance->GetVkInstance(), &physicalDeviceCount, nullptr);
        
        // Get all gpus supported vulkan
        std::vector<VkPhysicalDevice> physicalDevices(physicalDeviceCount);
        vkEnumeratePhysicalDevices(*Instance->GetVkInstance(), &physicalDeviceCount, physicalDevices.data());
        return physicalDevices;
    }

    void EV_Device::Create()
    {
        // Check if EV_Instance variable was setup
        if (Instance == nullptr)
            throw std::runtime_error("From EV_Device: You forget to setup EV_Instance variable!");
        
        // Check if EV_Instance variable was created before EV_Device
        if (!Instance->IsCreated())
            throw std::runtime_error("From EV_Device: You forget to create EV_Instance variable!");

        // Get all gpus with vulkan support
        std::vector<VkPhysicalDevice> physicalDevices = GetPhysicalDevices();

        if (physicalDevices.size() == 0) 
            throw std::runtime_error("From EV_Device: Failed to find GPUs with Vulkan support!");
            
        // Find first suitable device. Have to write code to pich discrete gpu
        bool wasPickedGPU = false;
        
        // Variable to store graphics familiy index on picked gpu
        uint32_t graphicsFamilyIndex;

        for (const VkPhysicalDevice& physicalDevice : physicalDevices)
        {
            if (GetQueueFamiliesIndexes(physicalDevice, graphicsFamilyIndex))
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
            throw std::runtime_error("From EV_Device: Failed to find suitable gpu!");

        // Pass info to struct to create queue to logical device
        VkDeviceQueueCreateInfo queueCreateInfo{};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = graphicsFamilyIndex;
        queueCreateInfo.queueCount = 1;
        // Maybe let user change this value. After adding second queue type
        float queuePriority = 1.0f;
        queueCreateInfo.pQueuePriorities = &queuePriority;

        // Requested physcial device features
        VkPhysicalDeviceFeatures deviceFeatures{};

        // Logical device create info
        VkDeviceCreateInfo logicalDeviceCreateInfo{};
        logicalDeviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        logicalDeviceCreateInfo.pQueueCreateInfos = &queueCreateInfo;
        logicalDeviceCreateInfo.queueCreateInfoCount = 1;
        logicalDeviceCreateInfo.pEnabledFeatures = &deviceFeatures;

        // Create VkDevice result
        VkResult createResult = vkCreateDevice(PhysicalDevice, &logicalDeviceCreateInfo, nullptr, &LogicalDevice);

        // Check VkDevice creation result
        if (createResult != VK_SUCCESS)
            throw std::runtime_error("From EV_Device: Failed to create VkDevice! vkCreateDevice error code: " + std::to_string(createResult));

        // Get graphics queue
        vkGetDeviceQueue(LogicalDevice, graphicsFamilyIndex, 0, &GraphicsQueue);
    }  

    void EV_Device::Destroy()
    {
        vkDestroyDevice(LogicalDevice, nullptr);
    } 
}
