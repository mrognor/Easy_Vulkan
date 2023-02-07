#pragma once 

#include <map>
#include <string>

#include "EV_Classes.h"

namespace EV
{
    /*!
        \~english \brief Prototype of the application base class

        \~english You can use your class to manage library classes since EV_App does not contain any logic. 
        \~english This class provides a convenient template for creating applications using Vulkan

        \~russian \brief Прототип класса приложения

        \~russian Вы можете использовать свой класс для управления классами библиотеки так как EV_App не содержит никакой логики.
        \~russian Данный класс предоставляет удобный шаблон для создания приложений с использование Vulkan
    */
    class EV_App
    {
    public:
        void Run();

        virtual void Setup() = 0;
        virtual void Create() = 0;
        virtual void OnStart() = 0;
        virtual void Tick() = 0;
        virtual void OnEnd() = 0;
        virtual void Cleanup() = 0;
    };
}