#include "EV_Device.h"

namespace EV
{
    std::vector<VkExtensionProperties> EV_Device::GetAvailableExtensions(const VkPhysicalDevice& physicalDevice)
    {
        uint32_t extensionCount;
        vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> availableExtensions(extensionCount);
        vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, availableExtensions.data());
        return availableExtensions;
    }

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

        // Check if it is at least one physical device with vulkan support
        if (physicalDevices.size() == 0) 
            throw std::runtime_error("From EV_Device::Create: Failed to find GPUs with Vulkan support!");
        
        // Map with all suitable physical devices graphics family inexes
        std::multimap<int, uint32_t> graphicsQueueFamilyIndexes;
        // Map with all suitable physical devices presentation family inexes
        std::multimap<int, uint32_t> presentationQueueFamilyIndexes;
        // Map with all suitable physical devices
        std::multimap<int, VkPhysicalDevice> suitablePhysicalDevices;

        // For loop to all availble gpus
        for (const VkPhysicalDevice& physicalDevice : physicalDevices)
        {
            // Get all available extensions
            std::vector<VkExtensionProperties> availableExtensions = GetAvailableExtensions(physicalDevice);
            
            // Checking required device extensions support
            for (const char*& requiredExtension : RequiredExtensions)
            {
                bool isFoundExtension = false;
                
                for (VkExtensionProperties availableExtension : availableExtensions)
                {
                    if (std::string(requiredExtension) == std::string(availableExtension.extensionName))
                    {
                        isFoundExtension = true;
                        break;
                    }
                }

                if (!isFoundExtension)
                    throw std::runtime_error("From EV_Device::Create: Requested extension not available! Extension name: " + std::string(requiredExtension));
            }

            // Variable to store graphics familiy index on current gpu
            uint32_t graphicsFamilyIndex;
            // Variable to store presentation familiy index on current gpu
            uint32_t presentationFamilyIndex;

            // Check device suitability
            if (GetQueueFamiliesIndexes(physicalDevice, graphicsFamilyIndex, presentationFamilyIndex))
            {
                // Get physical device properties
                VkPhysicalDeviceProperties physicalDeviceProperties;
                vkGetPhysicalDeviceProperties(physicalDevice, &physicalDeviceProperties);

                // Check if preferred device set
                if (IsPreferredDeviceSet)
                {
                    if (physicalDeviceProperties.deviceID == PreferredDeviceID)
                    {
                        PhysicalDevice = physicalDevice;
                        suitablePhysicalDevices.insert(std::pair<int, VkPhysicalDevice>(5, physicalDevice));
                        break;
                    }
                }
                else
                {
                    int gpuScores = 0;
                    switch (physicalDeviceProperties.deviceType)
                    {
                    case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
                        gpuScores = 4;
                        break;
                    
                    case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
                        gpuScores = 3;
                        break;
                    
                    case VK_PHYSICAL_DEVICE_TYPE_CPU:
                        gpuScores = 2;
                        break;

                    case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
                        gpuScores = 1;
                        break;

                    default:
                        gpuScores = 0;
                        break;
                    }
    
                    suitablePhysicalDevices.insert(std::pair<int, VkPhysicalDevice>(gpuScores, physicalDevice));
                    graphicsQueueFamilyIndexes.insert(std::pair<int, uint32_t>(gpuScores, graphicsFamilyIndex));
                    presentationQueueFamilyIndexes.insert(std::pair<int, uint32_t>(gpuScores, presentationFamilyIndex));
                }
            }
        }

        // Check if it is at least one suitable physical device
        if (suitablePhysicalDevices.size() == 0)
        {
            if (IsPreferredDeviceSet)
                throw std::runtime_error("From EV_Device::Create: Failed to find GPU! GPU id: " + 
                std::to_string(PreferredDeviceID) + " \nThis error means that you set it somewhere");
            else
                throw std::runtime_error("From EV_Device::Create: Failed to find suitable GPU!");
        }
        else 
        {
            PhysicalDevice = suitablePhysicalDevices.rbegin()->second;
            GraphicsQueueIndex = graphicsQueueFamilyIndexes.rbegin()->second;
            PresentationQueueIndex = presentationQueueFamilyIndexes.rbegin()->second;
        }

        // Pass info to struct to create queues to logical device
        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;

        // Checks that graphics queue index and presentation queue index not same
        int queuesCount = 1;
        if (GraphicsQueueIndex != PresentationQueueIndex)
            queuesCount++;

        for (int i = 1; i <= queuesCount; i++)
        {
            VkDeviceQueueCreateInfo queueCreateInfo{};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            
            switch(i)
            {
                case 1: queueCreateInfo.queueFamilyIndex = GraphicsQueueIndex; break;
                case 2: queueCreateInfo.queueFamilyIndex = PresentationQueueIndex; break;
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
        logicalDeviceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(RequiredExtensions.size());
        logicalDeviceCreateInfo.ppEnabledExtensionNames = RequiredExtensions.data();

        // Create VkDevice result
        VkResult createResult = vkCreateDevice(PhysicalDevice, &logicalDeviceCreateInfo, nullptr, &LogicalDevice);

        // Check VkDevice creation result
        if (createResult != VK_SUCCESS)
            throw std::runtime_error("From EV_Device::Create: Failed to create VkDevice! vkCreateDevice error code: " + std::to_string(createResult));

        // Get graphics queue
        vkGetDeviceQueue(LogicalDevice, GraphicsQueueIndex, 0, &GraphicsQueue);
        vkGetDeviceQueue(LogicalDevice, PresentationQueueIndex, 0, &PresentationQueue);

        bIsCreated = true;
    }  

    void EV_Device::Destroy()
    {
        vkDestroyDevice(LogicalDevice, nullptr);
        bIsCreated = false;
    } 
}
