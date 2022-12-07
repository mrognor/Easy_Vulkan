#pragma once

#include "EV_Include.h"

namespace EV
{
    class EV_Create_VkInstance
    {
    public:
        void operator()(VkInstance& instance);
    };

    void EV_Destroy_VkInstance(VkInstance& instance);
}