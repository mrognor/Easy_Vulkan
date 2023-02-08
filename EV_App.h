#pragma once 

#include <map>
#include <string>

#include "EV_Classes.h"

namespace EV
{
    /*!
        \~russian \brief Прототип класса приложения

        \~russian Данный класс предоставляет удобный интерфейс для создания приложений с использование EasyVulkan.
        \~russian Вы можете использовать свой класс для управления классами библиотеки.
        

        \~english \brief Prototype of the application base class

        \~english This class provides a convenient interface for creating applications using EasyVulkan.
        \~english You can use your class to manage library classes.
    */
    class EV_App
    {
    public:
        /*!
            \~russian \brief Метод запускающий приложение

            \~russian Вызывает все методы класса в правильном порядке.

            @code
                Setup()
                Create()
                OnStart()
                Tick()
                OnEnd()
                Cleanup()
            @endcode


            \~english \brief The method that launches the application

            \~english Calls all methods of the class in the correct order.

            @code
                Setup()
                Create()
                OnStart()
                Tick()
                OnEnd()
                Cleanup()
            @endcode
        */
        void Run();

        /*!
            \~russian \brief Метод для настройки всех классов библиотеки

            \~russian В данном методе нужно настроить все используемые классы с помощью их методов
            

            \~english \brief Method for configuring all library classes

            \~english In this method, you need to configure all the classes used using their methods
        */
        virtual void Setup() = 0;

        /*!
            \~russian \brief Метод для создания всех классов библиотеки

            \~russian Большинство классов библиотеки содержат метод Create().
            \~russian Эти методы создают соответствующие объекты Vulkan`а.

            \~russian \warning Порядок создания классов очень важен


            \~english \brief Method for creating all library classes

            \~english Most library classes contain the Create() method.
            \~english These methods create the corresponding Vulkan objects.

            \~english \warning The order in which classes are created is very important
        */
        virtual void Create() = 0;

        /*!
            \~russian \brief Метод для выполнения логики перед главным циклом приложения

            \~russian На момент вызова этого метода все объекты библиотеки и все объекты Vulkan уже созданы.


            \~english \brief Method for executing logic before the main application loop

            \~english At the time of calling this method, all library objects and all Vulkan objects have already been created.
        */
        virtual void OnStart() = 0;

        /*!
            \~russian \brief Метод для главного цикла приложения


            \~english \brief Method for the main application loop
        */
        virtual void Tick() = 0;

        /*!
            \~russian \brief Метод для выполнения логики после главного цикла приложения

            \~russian На момент вызова этого метода все объекты библиотеки и все объекты Vulkan еще созданы.

            \~english \brief Method for executing logic after the main application loop

            \~english At the time of calling this method, all library objects and all Vulkan objects are still created.
        */
        virtual void OnEnd() = 0;

        /*!
            \~russian \brief Метод для удаления всех объектов библиотеки и объектов Vulkan

            \~russian \warning Порядок удаления классов очень важен

            \~english \brief Method for executing logic after the main application loop

            \~english \warning The order of deleting classes is very important
        */
        virtual void Cleanup() = 0;
    };
}