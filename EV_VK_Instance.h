#pragma once

#include "EV_Classes.h"

namespace EV
{
    class EV_VK_Instance
    {
    private:
        VkInstance VulkanInstance;
        std::vector<const char*> RequiredExtensions;
        std::vector<const char*> RequiredValidationLayers;

    public:
        VkInstance& GetVkInstance() {return VulkanInstance;}
        std::vector<const char*> GetRequiredExtensions() { return RequiredExtensions; }
        std::vector<const char*> GetRequiredValidationLayers() { return RequiredValidationLayers; }

        void AddRequiredExtension(const char* requiredExtension);
        void AddRequiredExtensions(const std::vector<const char*>& requiredExtensions);
        void AddRequiredValidationLayer(const char* requiredValidationLayer);
        void AddRequiredValidationLayers(const std::vector<const char*>& requiredValidationLayers);

        void Create();
        void Destroy();
    };
}