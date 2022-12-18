#pragma once

#include <string>

#include "EV_Classes.h"
#include "EV_App.h"

namespace EV
{
    class EV_VkClassContainer
    {
    protected:
        void* Data;
        std::string DataType;
        EV_App* App;
    public:
        EV_VkClassContainer(EV_App* app) : App(app) {};
        virtual void Setup() = 0;
        virtual void Create() = 0;
        virtual void CleanUp() = 0;
    };
}