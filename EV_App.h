#pragma once 

#include <map>
#include <string>

#include "EV_Classes.h"

namespace EV
{
    class EV_App
    {
    public:
        void Start();

        virtual void Setup() = 0;
        virtual void Create() = 0;
        virtual void Run() = 0;
        virtual void Cleanup() = 0;
    };
}