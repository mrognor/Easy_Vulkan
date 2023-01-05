#pragma once 

#include "EV_Classes.h"
#include "EV_Functions.h"

namespace EV
{
    class EV_VK_ValidationLayers
    {
    private:
        VkInstance* VulkanInstance = nullptr;
        std::vector<const char*> RequiredValidationLayers; 
        
        VkDebugUtilsMessengerCreateInfoEXT DebugMessengerCreateInfo{};
        VkDebugUtilsMessengerEXT DebugMessenger;  
        PFN_vkDebugUtilsMessengerCallbackEXT ValidationLayersMessageHandler = EV::EV_DefaultValidationLayersCallback;

    public:
        EV_VK_ValidationLayers(VkInstance* vulkanInstance) : VulkanInstance(vulkanInstance) {}

        std::vector<const char*> GetRequiredValidationLayers() { return RequiredValidationLayers; }
        VkDebugUtilsMessengerCreateInfoEXT* GetDebugMessengerCreateInfo() { return &DebugMessengerCreateInfo;}

        void AddRequiredValidationLayer(const char* requiredValidationLayer);
        void AddRequiredValidationLayers(const std::vector<const char*>& requiredValidationLayers);
        void SetValidationLayersMessageHandler(PFN_vkDebugUtilsMessengerCallbackEXT validationLayersMessageHandler);

        void Create();
        void Destroy();
    };
}