#include "EV_Device.h"

namespace EV
{
    bool EV_Device::GetQueueFamiliesIndexes(const VkPhysicalDevice& physicalDevice, uint32_t& graphicsFamilyIndex, uint32_t& presentationFamilyIndex)
    {
        // Get amount of queue families
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);

        // Get all queue families
        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies.data());

        int i = 0;
        bool wasFoundGraphicsQueue = false;
        bool wasFoundPresentationQueue = false;

        for (const auto& queueFamily : queueFamilies) 
        {
            // Find graphics queue index
            if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT && wasFoundGraphicsQueue == false) 
            {
                wasFoundGraphicsQueue = true;
                graphicsFamilyIndex = i;
            }

            // Find presentation queue index
            VkBool32 presentationSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i, *Window->GetWindowSurface(), &presentationSupport);

            if (presentationSupport == true)
            {
                if (wasFoundPresentationQueue == true)
                {
                    if (i != graphicsFamilyIndex)
                        presentationFamilyIndex = i; 
                }
                else
                {
                    presentationFamilyIndex = i; 
                    wasFoundPresentationQueue = true;
                }
            }       
            i++;
        }

        if (wasFoundGraphicsQueue && wasFoundPresentationQueue)
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
            throw std::runtime_error("From EV_Device::Create: You forget to setup EV_Instance variable!");
        
        // Check if EV_Instance variable was created before EV_Device
        if (!Instance->IsCreated())
            throw std::runtime_error("From EV_Device::Create: You forget to create EV_Instance variable! EV_Device must be created after EV_Instance!");

        // Check if EV_Window variable was setup
        if (Window == nullptr)
            throw std::runtime_error("From EV_Device::Create: You forget to setup EV_Window variable!");
        
        // Check if EV_Window variable was created before EV_Device
        if (!Window->IsCreated())
            throw std::runtime_error("From EV_Device::Create: You forget to create EV_Window variable! EV_Device must be created after EV_Window!");


        // Get all gpus with vulkan support
        std::vector<VkPhysicalDevice> physicalDevices = GetPhysicalDevices();

        if (physicalDevices.size() == 0) 
            throw std::runtime_error("From EV_Device::Create: Failed to find GPUs with Vulkan support!");
            
        // Find first suitable device. Have to write code to pich discrete gpu
        bool wasPickedGPU = false;
        
        // Variable to store graphics familiy index on picked gpu
        uint32_t graphicsFamilyIndex;
        // Variable to store presentation familiy index on picked gpu
        uint32_t presentationFamilyIndex;

        for (const VkPhysicalDevice& physicalDevice : physicalDevices)
        {
            if (GetQueueFamiliesIndexes(physicalDevice, graphicsFamilyIndex, presentationFamilyIndex))
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
            throw std::runtime_error("From EV_Device::Create: Failed to find suitable gpu!");

        // Pass info to struct to create queues to logical device
        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;

        int queuesCount = 1;
        if (graphicsFamilyIndex != presentationFamilyIndex)
            queuesCount++;

        for (int i = 1; i <= queuesCount; i++)
        {
            VkDeviceQueueCreateInfo queueCreateInfo{};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            
            switch(i)
            {
                case 1: queueCreateInfo.queueFamilyIndex = graphicsFamilyIndex; break;
                case 2: queueCreateInfo.queueFamilyIndex = presentationFamilyIndex; break;
            }

            queueCreateInfo.queueCount = 1;
            float queuePriority = 1.0f;
            queueCreateInfo.pQueuePriorities = &queuePriority;
            queueCreateInfos.push_back(queueCreateInfo);
        }


        // Requested physcial device features
        VkPhysicalDeviceFeatures deviceFeatures{};

        // Logical device create info
        VkDeviceCreateInfo logicalDeviceCreateInfo{};
        logicalDeviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        logicalDeviceCreateInfo.pQueueCreateInfos = queueCreateInfos.data();
        logicalDeviceCreateInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
        logicalDeviceCreateInfo.pEnabledFeatures = &deviceFeatures;

        // Create VkDevice result
        VkResult createResult = vkCreateDevice(PhysicalDevice, &logicalDeviceCreateInfo, nullptr, &LogicalDevice);

        // Check VkDevice creation result
        if (createResult != VK_SUCCESS)
            throw std::runtime_error("From EV_Device::Create: Failed to create VkDevice! vkCreateDevice error code: " + std::to_string(createResult));

        // Get graphics queue
        vkGetDeviceQueue(LogicalDevice, graphicsFamilyIndex, 0, &GraphicsQueue);
        vkGetDeviceQueue(LogicalDevice, presentationFamilyIndex, 0, &PresentationQueue);
    }  

    void EV_Device::Destroy()
    {
        vkDestroyDevice(LogicalDevice, nullptr);
    } 
}
