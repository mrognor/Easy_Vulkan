#pragma once

#include "EV_Classes.h"

namespace EV
{
    class EV_VK_Instance
    {
    private:
        VkInstance VulkanInstance;
        std::vector<const char*> RequiredExtensions;

    public:
        VkInstance& GetVkInstance() {return VulkanInstance;}
        std::vector<const char*> GetRequiredExtensions() { return RequiredExtensions; }
        
        void AddRequiredExtensions(std::vector<const char*> requiredExtensions);

        void Create();
        void Destroy();
    };
}