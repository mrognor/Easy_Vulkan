#pragma once 

#include "EV_Classes.h"
#include "EV_Instance.h"

namespace EV
{
    class EV_Window
    {
    private:
        // Easy vulkan instance ptr
        EV_Instance* Instance = nullptr;
        
        // Pointer to glfw window
        GLFWwindow* GLFW_Window;
        
        // Cross-platform connection between os window and vulkan lib
        VkSurfaceKHR WindowSurface;

        // Window width
        int WindowWidth = 700;
        
        // Window height
        int WindowHeight = 500;

        // Window name
        std::string WindowTitle = "Easy Vulkan App";

        // Variable for tracking the state of an object. True if created otherwise false.
        // Will be false after calling the Destroy method
        bool IsCreated = false; 
    public:
        // Default constructor
        EV_Window();

       /*!
            \~russian \brief Метод возвращает указатель на окно библиотеки GLFW
     

            \~english \brief The method returns a pointer to the GLFW library window
        */
        GLFWwindow* GetGLFWWindow() { return GLFW_Window; }

        /*!
            \~russian \brief Метод возвращает ширину окна в пикселях
     

            \~english \brief The method returns the width of the window in pixels
        */
        int GetWindowWidth() { return WindowWidth; }

        /*!
            \~russian \brief Метод возвращает высоту окна в пикселях
     

            \~english \brief The method returns the height of the window in pixels
        */
        int GetWindowHeight() { return WindowHeight; }

        /*!
            \~russian \brief Метод возвращает заголовок окна
     

            \~english \brief The method returns the window title
        */
        std::string GetWindowTitle() { return WindowTitle; }

        /*!
            \~russian \brief Метод возвращает необходимые для работы библиотеки расширения Vulkan
     

            \~english \brief The method returns the Vulkan extensions necessary for the library to work
        */
        std::vector<const char*> GetRequiredExtensions();

        /*!
            \~russian \brief Возвращает true если объект был создан и еще не уничтожен, а иначе вернет false
     

            \~english \brief Return true if VkInstance was created and was not destroyed yet. Otherwise return false.
        */
        bool GetIsCreated() { return IsCreated; }

        /*!
            \~russian \brief Метод возвращает указатель на поверхность VkSurfaceKHR
     

            \~english \brief The method returns a pointer to the VkSurfaceKHR
        */
        VkSurfaceKHR* GetWindowSurface() { return &WindowSurface; }
        
        /*!
            \~russian \brief Метод для установки ширины окна
     

            \~english \brief Method for setting the window width
        */
        void SetWindowWidth(int windowWidth) { WindowWidth = windowWidth; }

        /*!
            \~russian \brief Метод для установки высоты окна
     

            \~english \brief Method for setting the window height
        */
        void SetWindowHeight(int windowHeight) { WindowHeight = windowHeight; }

        /*!
            \~russian \brief Метод для установки заголовка окна
     

            \~english \brief Method for setting the window title
        */
        void SetWindowTitle(std::string windowTitle) { WindowTitle = windowTitle; }

        /*!
            \~russian \brief Метод для установки указателя на EV_Instance
     

            \~english \brief Method for setting the pointer to EV_Instance
        */
        void SetInstance(EV_Instance* instance) { Instance = instance; }


        void Create();
        void Tick();
        void Destroy(); 

        /**
			\brief Wrapper function for glfwWindowHint

            You can find more information here https://www.glfw.org/docs/3.3/group__window.html#ga7d9c8c62384b1e2821c4dc48952d2033
			
            \param[in] hint The [window hint](window_hints) to set.
            \param[in] value The new value of the window hint.
		*/
        void SetWindowHint(int hint, int value);
    };
}