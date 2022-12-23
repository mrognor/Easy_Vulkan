#include "EV_App.h"

namespace EV
{
    void EV_App::Create() {}
    
    void EV_App::Cleanup() {}
    
    std::map<std::string, EV_VkClassContainer*>* EV_App::GetVkClasses()
    {
        return &VkClasses;
    }

    void EV_App::Run() 
    {
        Setup();

        Create();

        MainLoop();

        Cleanup();
    }
}