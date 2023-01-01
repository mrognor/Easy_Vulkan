#pragma once

#include "EV_Classes.h"

namespace EV
{
    class EV_VK_Instance
    {
    private:
        VkInstance VulkanInstance;
    
    public:
        VkInstance& GetVkInstance() {return VulkanInstance;}
        void Create();
    };
}