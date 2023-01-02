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
    }
}