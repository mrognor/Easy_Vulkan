#pragma once 

#include "EV_Classes.h"

namespace EV
{
    class EV_VK_ValidationLayers
    {
    private:
        std::vector<const char*> RequiredValidationLayers;    
    public:
        std::vector<const char*> GetRequiredValidationLayers() { return RequiredValidationLayers; }

        void AddRequiredValidationLayer(const char* requiredValidationLayer);
        void AddRequiredValidationLayers(const std::vector<const char*>& requiredValidationLayers);

        void Create();
    };
}