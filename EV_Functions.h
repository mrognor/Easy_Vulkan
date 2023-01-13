#pragma once

#include "EV_Classes.h"

namespace EV
{
    /// Default validation layers messages handler
    static VKAPI_ATTR VkBool32 VKAPI_CALL EV_DefaultValidationLayersCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData)
    {
        if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) 
            std::cerr << "From validation layer: " << pCallbackData->pMessage << std::endl;

        return VK_FALSE;
    }
}