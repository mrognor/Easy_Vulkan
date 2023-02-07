#pragma once 

#include <map>
#include <string>

#include "EV_Classes.h"

namespace EV
{
    /*!
        \~english \brief Prototype of the application base class

        \~english You can use your class to manage library classes since EV_App does not contain any logic. 
        \~english This class provides a convenient template for creating applications using EasyVulkan

        \~russian \brief Прототип класса приложения

        \~russian Вы можете использовать свой класс для управления классами библиотеки так как EV_App не содержит никакой логики.
        \~russian Данный класс предоставляет удобный шаблон для создания приложений с использование EasyVulkan
    */
    class EV_App
    {
    public:
        /*!
            \brief Метод запускающий все приложение

            Вызывает все методы класса в правильном порядке.
            @code
            Setup()
            Create()
            OnStart()
            Tick()
            OnEnd()
            Cleanup()
            @endcode
            Описание методов представлено ниже
        */
        void Run();

        /*!
            \brief Метод для настройки всех классов библиотеки

            В данном методе нужно настроить все используемые классы с помощью их методов
        */
        virtual void Setup() = 0;

        /*!
            \brief Метод для создания всех классов библиотеки

            Большинство классов библиотеки содержат метод Create().
            Эти методы создают соответствующие объекты Vulkan`а.

            \warning Порядок создания классов очень важен
        */
        virtual void Create() = 0;
        virtual void OnStart() = 0;
        virtual void Tick() = 0;
        virtual void OnEnd() = 0;
        virtual void Cleanup() = 0;
    };
}