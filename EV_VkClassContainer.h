#pragma once

#include <string>

#include "EV_Classes.h"
#include "EV_App.h"

namespace EV
{
    class EV_VkClassContainer
    {
    protected:
        std::string DataType;
        EV_App* App = nullptr;
    public:
        EV_VkClassContainer(EV_App* app, std::string dataType);
        
        virtual void* GetData() = 0;
        std::string GetDataType();

        virtual void Setup() = 0;
        virtual void Create() = 0;
        virtual void CleanUp() = 0;
    };
}