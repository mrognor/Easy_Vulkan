#include "EV_VkValidationLayers.h"

namespace EV
{
    std::vector<const char*> RequiredValidationLayers = {"VK_LAYER_KHRONOS_validation"};

    bool EV_Enable_VkValidationLayers::CheckValidationLayerSupport()
    {
        // Get available validation layer count
        uint32_t availableValidationLayerCount;
        vkEnumerateInstanceLayerProperties(&availableValidationLayerCount, nullptr);

        // Get all available validation layers names
        std::vector<VkLayerProperties> availableValidationLayers(availableValidationLayerCount);
        vkEnumerateInstanceLayerProperties(&availableValidationLayerCount, availableValidationLayers.data());

        // Iterate all requested validation layers
        for (const std::string layerName : RequiredValidationLayers) 
        {
            bool layerFound = false;
            // Check if requested validation layer exist
            for (const auto& layerProperties : availableValidationLayers) 
            {
                if (std::string(layerProperties.layerName) == std::string(layerName)) 
                {
                    layerFound = true;
                    break;
                }
            }

        // If the requested layer is unavailable, the function returns a false
        if (!layerFound) 
            return false;
        }
        std::cout << "T" << std::endl;
        // Return true if all requested layers available
        return true;
    }

    void EV_Enable_VkValidationLayers::operator()()
    {
        CheckValidationLayerSupport();
    }
}