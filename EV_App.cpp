#include "EV_App.h"

namespace EV
{
    void EV_App::Run() 
    {
        Setup();

        Create();

        OnStart();

        Tick();

        OnEnd();

        Cleanup();
    }
}