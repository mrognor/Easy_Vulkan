#include "EV_App.h"

namespace EV
{
    void EV_App::Create() {}
    
    void EV_App::Cleanup() {}
    
    void EV_App::Run() 
    {
        Setup();

        Create();

        MainLoop();

        Cleanup();
    }
}