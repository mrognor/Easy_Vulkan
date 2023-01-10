#include "EV_App.h"

namespace EV
{
    void EV_App::Start() 
    {
        Setup();

        Create();

        Run();

        Cleanup();
    }
}