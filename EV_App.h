#pragma once 

#include <map>
#include <string>

#include "EV_Classes.h"
#include "EV_VkClassContainer.h"

namespace EV
{
    class EV_App
    {
    private:
        void Create();
        void Cleanup();

    protected:
        std::map<std::string, EV_VkClassContainer*> VkClasses;

    public:
        void Run();
        virtual void Setup() = 0;
        virtual void MainLoop() = 0;
    };
}