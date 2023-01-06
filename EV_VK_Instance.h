#pragma once

#include "EV_Classes.h"
#include "EV_Functions.h"

namespace EV
{
    class EV_VK_Instance
    {
    private:
        VkInstance VulkanInstance;
        VkDebugUtilsMessengerCreateInfoEXT* DebugMessengerCreateInfo = nullptr;
        std::vector<const char*> RequiredExtensions;
        std::vector<const char*> RequiredValidationLayers;

        // Useless in release mode. Put inside ifndef
        VkDebugUtilsMessageSeverityFlagsEXT DebugMessengerSeverityFlags = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | 
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | 
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        // Useless in release mode. Put inside ifndef
        VkDebugUtilsMessageTypeFlagsEXT DebugMessengerMessageTypeFlags = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | 
        VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        // Useless in release mode. Put inside ifndef
        PFN_vkDebugUtilsMessengerCallbackEXT DebugMessengerCallback = EV::EV_DefaultValidationLayersCallback;
        // Useless in release mode. Put inside ifndef
        VkDebugUtilsMessengerEXT DebugMessenger;  

        void CreateDebugMessenger(const VkDebugUtilsMessengerCreateInfoEXT& debugMessengerCreateInfo);

    public:
        VkInstance* GetVkInstance() {return &VulkanInstance;}
        std::vector<const char*> GetRequiredExtensions() { return RequiredExtensions; }
        std::vector<const char*> GetRequiredValidationLayers() { return RequiredValidationLayers; }

        void AddRequiredExtension(const char* requiredExtension) { RequiredExtensions.push_back(requiredExtension); };
        void AddRequiredExtensions(const std::vector<const char*>& requiredExtensions) { RequiredExtensions.insert(RequiredExtensions.end(), requiredExtensions.begin(), requiredExtensions.end()); };
        void AddRequiredValidationLayer(const char* requiredValidationLayer) { RequiredValidationLayers.push_back(requiredValidationLayer); };
        void AddRequiredValidationLayers(const std::vector<const char*>& requiredValidationLayers) { RequiredValidationLayers.insert(RequiredValidationLayers.end(), requiredValidationLayers.begin(), requiredValidationLayers.end()); };
        
        void SetDebugMessengerSeverityFlags(VkDebugUtilsMessageSeverityFlagsEXT debugMessengerSeverityFlags ) { DebugMessengerSeverityFlags = debugMessengerSeverityFlags; }
        void SetDebugMessengerMessageTypeFlags(VkDebugUtilsMessageTypeFlagsEXT debugMessengerMessageTypeFlags) { DebugMessengerMessageTypeFlags = debugMessengerMessageTypeFlags; }
        void SetDebugMessengerCallback(PFN_vkDebugUtilsMessengerCallbackEXT debugMessengerCallback) { DebugMessengerCallback = debugMessengerCallback; }
        
        void Create();
        void Destroy();
    };
}