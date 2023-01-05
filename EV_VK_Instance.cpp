#include "EV_VK_Instance.h"

namespace EV
{
    void EV_VK_Instance::AddRequiredExtension(const char* requiredExtension)
    {
        RequiredExtensions.push_back(requiredExtension);
    }

    void EV_VK_Instance::AddRequiredExtensions(const std::vector<const char*>& requiredExtensions)
    {
        RequiredExtensions.insert(RequiredExtensions.end(), requiredExtensions.begin(), requiredExtensions.end());
    }

    void EV_VK_Instance::AddRequiredValidationLayer(const char* requiredValidationLayer)
    {
        RequiredValidationLayers.push_back(requiredValidationLayer);
    }

    void EV_VK_Instance::AddRequiredValidationLayers(const std::vector<const char*>& requiredValidationLayers)
    {
        RequiredValidationLayers.insert(RequiredValidationLayers.end(), requiredValidationLayers.begin(), requiredValidationLayers.end());
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
        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        // Passing the number of extensions and their list to create VkInstance
        createInfo.enabledExtensionCount = RequiredExtensions.size();
        createInfo.ppEnabledExtensionNames = RequiredExtensions.data();

        // Passing information about validation layers
        createInfo.enabledLayerCount = static_cast<uint32_t>(RequiredValidationLayers.size());
        createInfo.ppEnabledLayerNames = RequiredValidationLayers.data();
           
        // Fill debug messenger create info struct
        VkDebugUtilsMessengerCreateInfoEXT MessengerCreateInfo{};
        MessengerCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        MessengerCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | 
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | 
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        MessengerCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | 
        VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        MessengerCreateInfo.pfnUserCallback = EV::EV_DefaultValidationLayersCallback;
        createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &MessengerCreateInfo;


        // Create VkInstance
        VkResult createResult = vkCreateInstance(&createInfo, nullptr, &VulkanInstance);

        // Check VkInstance creation result
        if (createResult != VK_SUCCESS)
        {
            std::string errorMsg = "Failed to create VkInstance! vkCreateInstance error code: ";
            errorMsg += std::to_string(createResult);
            errorMsg += "\nMore info about vkCreateInstance here: https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/vkCreateInstance.html";
            errorMsg += "\nMore info about error codes here: https://registry.khronos.org/VulkanSC/specs/1.0-extensions/man/html/VkResult.html";
            throw std::runtime_error(errorMsg);
        }
    }

    void EV_VK_Instance::Destroy()
    {
        vkDestroyInstance(VulkanInstance, nullptr);
    }
}