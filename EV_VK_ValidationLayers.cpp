#include "EV_VK_ValidationLayers.h"

namespace EV
{
    void EV::EV_VK_ValidationLayers::AddRequiredValidationLayer(const char* requiredValidationLayer)
    {
        RequiredValidationLayers.push_back(requiredValidationLayer);
    }

    void EV::EV_VK_ValidationLayers::AddRequiredValidationLayers(const std::vector<const char*>& requiredValidationLayers)
    {
        RequiredValidationLayers.insert(RequiredValidationLayers.end(), requiredValidationLayers.begin(), requiredValidationLayers.end());
    }

    void EV::EV_VK_ValidationLayers::SetValidationLayersMessageHandler(PFN_vkDebugUtilsMessengerCallbackEXT validationLayersMessageHandler)
    {
        ValidationLayersMessageHandler = validationLayersMessageHandler;
    }

    void EV::EV_VK_ValidationLayers::Create()
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

        // Fill debug messenger create info struct
        DebugMessengerCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        DebugMessengerCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        DebugMessengerCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        DebugMessengerCreateInfo.pfnUserCallback = EV::EV_DefaultValidationLayersCallback;
        DebugMessengerCreateInfo.pUserData = nullptr; // Optional

        // Create debug messenger
        VkResult createDebugMessengerResult = CreateDebugUtilsMessengerEXT(VulkanInstance, &DebugMessengerCreateInfo, nullptr, &DebugMessenger);

        if (createDebugMessengerResult != VK_SUCCESS) 
            throw std::runtime_error("Failed to set up debug messenger! Error code: " + std::to_string(createDebugMessengerResult)
            + "\nMore info about error codes here: https://registry.khronos.org/VulkanSC/specs/1.0-extensions/man/html/VkResult.html");

    }

    void EV::EV_VK_ValidationLayers::Destroy()
    {   
        DestroyDebugUtilsMessengerEXT(*VulkanInstance, DebugMessenger, nullptr);
    }
}