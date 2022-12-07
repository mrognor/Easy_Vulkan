#pragma once

#include "EV_Include.h"

namespace EV
{
    class EV_Enable_VkValidationLayers
    {
    private:
        bool CheckValidationLayerSupport();
        
    public:
        void operator()();


    };
}