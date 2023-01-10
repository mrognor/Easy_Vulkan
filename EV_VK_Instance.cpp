#include "EV_VK_Instance.h"

namespace EV
{
    std::vector<VkExtensionProperties> EV_VK_Instance::GetAvailableExtensions()
    {
        // Count available extensions
        uint32_t availableExtensionsCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &availableExtensionsCount, nullptr);
        
        // Get all available extensions
        std::vector<VkExtensionProperties> availableExtensions(availableExtensionsCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &availableExtensionsCount, availableExtensions.data());
        return availableExtensions;
    }

    void EV_VK_Instance::CreateDebugMessenger(const VkDebugUtilsMessengerCreateInfoEXT& debugMessengerCreateInfo)
    {
        // Get available layers count
        uint32_t availableLayersCount;
        vkEnumerateInstanceLayerProperties(&availableLayersCount, nullptr);

        // Get available layers
        std::vector<VkLayerProperties> availableLayers(availableLayersCount);
        vkEnumerateInstanceLayerProperties(&availableLayersCount, availableLayers.data());

        // Checking the availability of all requested layers
        for (const char* requiredLayerName : RequiredValidationLayers)
        {
            bool requiredLayerFound = false;

            for (const auto& availableLayerProperties : availableLayers)
            {
                if (std::string(requiredLayerName) == std::string(availableLayerProperties.layerName)) 
                {
                    requiredLayerFound = true;
                    break;
                }
            }

            if (!requiredLayerFound) 
                throw std::runtime_error("Validation layer requested, but not available! Layer name: " + std::string(requiredLayerName));
        }

        // Create debug messenger
        VkResult createDebugMessengerResult;
        PFN_vkCreateDebugUtilsMessengerEXT createDebugMessengerFunc = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(VulkanInstance, "vkCreateDebugUtilsMessengerEXT");
        
        if (createDebugMessengerFunc != nullptr)
        { 
            createDebugMessengerResult = createDebugMessengerFunc(VulkanInstance, &debugMessengerCreateInfo, nullptr, &DebugMessenger);
            
            if (createDebugMessengerResult != VK_SUCCESS) 
                throw std::runtime_error("Failed to set up debug messenger! Error code: " + std::to_string(createDebugMessengerResult)
                + "\nMore info about error codes here: https://registry.khronos.org/VulkanSC/specs/1.0-extensions/man/html/VkResult.html");
        }
        else 
            throw std::runtime_error("Failed to load vkCreateDebugUtilsMessengerEXT! Check extensions and vulkan installation");
    }

    void EV_VK_Instance::Create()
    {
        /* From the specification:
        If not NULL, [pApplicationInfo] helps implementations recognize behavior inherent
        to classes of applications. So that's what it is for.
        IHVs (independent hardware vendors) are going to provide application-specific optimizations
        for any program that's popular enough to attract that kind of interest. That's inevitable.
        So Vulkan has two choices: it can either pretend that the inevitable is somehow not
        going to happen, which means IHVs will do it anyway, using various heuristics to detect your
        application. Or your application can just introduce itself and cut out the middle-man.
        Vulkan permits you to do the latter. And well-behaved engines will likely do likewise on
        your program's behalf. */

        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Easy Vulkan App";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        // A structure with all the parameters needed to create VkInstance
        VkInstanceCreateInfo vulkanInstanceCreateInfo{};
        vulkanInstanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        vulkanInstanceCreateInfo.pApplicationInfo = &appInfo;

        // Passing the number of extensions and their list to create VkInstance
        std::vector<VkExtensionProperties> availableExtensions = GetAvailableExtensions();

        for (VkExtensionProperties availableExtension : availableExtensions)
        {
            std::string unFoundExtension;
            
            for (const char*& requiredExtension : RequiredExtensions)
            {
                unFoundExtension = std::string(requiredExtension);
                if (unFoundExtension == std::string(availableExtension.extensionName))
                {
                    unFoundExtension = "none";
                    break;
                }
            }

            if (unFoundExtension != "none")
                throw std::runtime_error("Requested extension not available! Extension name: " + unFoundExtension);
        }

        vulkanInstanceCreateInfo.enabledExtensionCount = RequiredExtensions.size();
        vulkanInstanceCreateInfo.ppEnabledExtensionNames = RequiredExtensions.data();
           
        #ifndef NDEBUG
        // Passing information about validation layers
        vulkanInstanceCreateInfo.enabledLayerCount = static_cast<uint32_t>(RequiredValidationLayers.size());
        vulkanInstanceCreateInfo.ppEnabledLayerNames = RequiredValidationLayers.data();

        // Fill debug messenger create info struct
        VkDebugUtilsMessengerCreateInfoEXT debugMessengerCreateInfo{};
        debugMessengerCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        debugMessengerCreateInfo.messageSeverity = DebugMessengerSeverityFlags;
        debugMessengerCreateInfo.messageType = DebugMessengerMessageTypeFlags;
        debugMessengerCreateInfo.pfnUserCallback = DebugMessengerCallback;
        vulkanInstanceCreateInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &debugMessengerCreateInfo;
        #else
        vulkanInstanceCreateInfo.enabledLayerCount = 0;
        #endif

        // Create VkInstance
        VkResult createResult = vkCreateInstance(&vulkanInstanceCreateInfo, nullptr, &VulkanInstance);

        // Check VkInstance creation result
        if (createResult != VK_SUCCESS)
        {
            std::string errorMsg = "Failed to create VkInstance! vkCreateInstance error code: ";
            errorMsg += std::to_string(createResult);
            errorMsg += "\nMore info about vkCreateInstance here: https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/vkCreateInstance.html";
            errorMsg += "\nMore info about error codes here: https://registry.khronos.org/VulkanSC/specs/1.0-extensions/man/html/VkResult.html";
            throw std::runtime_error(errorMsg);
        }

        #ifndef NDEBUG
        CreateDebugMessenger(debugMessengerCreateInfo);
        #endif
    }

    void EV_VK_Instance::Destroy()
    {
        #ifndef NDEBUG
        PFN_vkDestroyDebugUtilsMessengerEXT destroyDebugMessengerFunc = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(VulkanInstance, "vkDestroyDebugUtilsMessengerEXT");
        if (destroyDebugMessengerFunc != nullptr) 
            destroyDebugMessengerFunc(VulkanInstance, DebugMessenger, nullptr);
        else throw std::runtime_error("Failed to load func vkDestroyDebugUtilsMessengerEXT!");
        #endif

        vkDestroyInstance(VulkanInstance, nullptr);
    }
}