#pragma once

#include "EV_Classes.h"
#include "EV_Device.h"
#include "EV_Window.h"

namespace EV
{
    class EV_Swapchain
    {
    private:
        EV_Device* Device = nullptr;
        EV_Window* Window = nullptr;

        VkSurfaceFormatKHR (*PickWindowSurfaceFormat)(std::vector<VkSurfaceFormatKHR>) = nullptr;
        VkPresentModeKHR (*PickWindowSurfacePresentationMode)(std::vector<VkPresentModeKHR>) = nullptr;
    public:
        void SetDevice(EV_Device* device) { Device = device; }
        void SetWindow(EV_Window* window) { Window = window; }
        // Set function to choose window surface format. Disabled by default. Set to nullptr to disable
        void SetPickWindowSurfaceFormatFunc(VkSurfaceFormatKHR (*pickWindowSurfaceFormat)(std::vector<VkSurfaceFormatKHR>)) { PickWindowSurfaceFormat = pickWindowSurfaceFormat; }
        // Set function to choose window surface presentation mode. Disabled by default. Set to nullptr to disable
        void SetPickWindowSurfacePresentationModeFunc(VkPresentModeKHR (*pickWindowSurfacePresentationMode)(std::vector<VkPresentModeKHR>)) { PickWindowSurfacePresentationMode = pickWindowSurfacePresentationMode; }
        
        void Create();
        void Destroy();
    };
}