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

        // The imageArrayLayers specifies the amount of layers each image consists of. 
        // This is always 1 unless you are developing a stereoscopic 3D application.
        // Vulkan variable to set value in swapchain create info
        int SwapchainImageArrayLayers = 1;
        
        // The imageUsage bit field specifies what kind of operations we'll use the images in the swap chain for. 
        // It is also possible that you'll render images to a separate image first to perform operations 
        // like post-processing. In that case you may use a value like VK_IMAGE_USAGE_TRANSFER_DST_BIT instead 
        // and use a memory operation to transfer the rendered image to a swap chain image.
        // Vulkan variable to set value in swapchain create info
        // By default set to VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT
        VkImageUsageFlags SwapchainImageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

        // Bool variable to store info about swapchain transform enable
        bool IsSwapchainTransformEnabled = false;

        // Variable to store user defined transform
        VkSurfaceTransformFlagBitsKHR SwapchainTransform;

        // Swapchain alpha channel
        VkCompositeAlphaFlagBitsKHR SwapchainAlphaFlag = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;

        // Is swapchain clipped
        VkBool32 SwapchainClipped = VK_TRUE;

        VkSwapchainKHR OldSwapchain = VK_NULL_HANDLE;

        // VkSwapchain itself
        VkSwapchainKHR Swapchain;

        // Images from swapchain
        std::vector<VkImage> SwapchainImages;

        // Resolution of images in swapchain
        VkExtent2D SwapchainExtent;

        // Image format in swapchain
        VkFormat SwapchainImageFormat;

        // Image viewss in swapchain
        std::vector<VkImageView> SwapchainImageViews;

        // Image view type. By default set to VK_IMAGE_VIEW_TYPE_2D
        VkImageViewType ImageViewType = VK_IMAGE_VIEW_TYPE_2D;

        // Image view components swizzle. Red, green, blue, alpha. By default all set to VK_COMPONENT_SWIZZLE_IDENTITY
        VkComponentSwizzle ImageViewComponentSwizzles[4] = {VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY};

        VkSurfaceFormatKHR (*PickWindowSurfaceFormat)(std::vector<VkSurfaceFormatKHR>) = nullptr;
        VkPresentModeKHR (*PickWindowSurfacePresentationMode)(std::vector<VkPresentModeKHR>) = nullptr;
    public:
        void SetDevice(EV_Device* device) { Device = device; }
        void SetWindow(EV_Window* window) { Window = window; }

        // The imageArrayLayers specifies the amount of layers each image consists of. 
        // This is always 1 unless you are developing a stereoscopic 3D application.
        // Vulkan variable to set value in swapchain create info
        void SetSwapchainImageArrayLayers(int swapchainImageArrayLayers) { SwapchainImageArrayLayers = swapchainImageArrayLayers; }
        
        // The imageUsage bit field specifies what kind of operations we'll use the images in the swap chain for. 
        // It is also possible that you'll render images to a separate image first to perform operations 
        // like post-processing. In that case you may use a value like VK_IMAGE_USAGE_TRANSFER_DST_BIT instead 
        // and use a memory operation to transfer the rendered image to a swap chain image.
        // Vulkan variable to set value in swapchain create info
        // By default set to VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT
        void SetSwapchainImageUsage(VkImageUsageFlags swapchainImageUsage) { SwapchainImageUsage = swapchainImageUsage; }
        
        // Set function to choose window surface format. Disabled by default. Set to nullptr to disable
        void SetPickWindowSurfaceFormatFunc(VkSurfaceFormatKHR (*pickWindowSurfaceFormat)(std::vector<VkSurfaceFormatKHR>)) { PickWindowSurfaceFormat = pickWindowSurfaceFormat; }
        
        // Set function to choose window surface presentation mode. Disabled by default. Set to nullptr to disable
        void SetPickWindowSurfacePresentationModeFunc(VkPresentModeKHR (*pickWindowSurfacePresentationMode)(std::vector<VkPresentModeKHR>)) { PickWindowSurfacePresentationMode = pickWindowSurfacePresentationMode; }
        
        // Set swapchain transform support. If second parametr set to true it will be disable transform. 
        void SetSwapchainTransform(VkSurfaceTransformFlagBitsKHR swapchainTransform, bool disable = false); 

        // Set swapchain alpha flag
        void SetSwapchainAlphaFlag(VkCompositeAlphaFlagBitsKHR swapchainAlphaFlag) { SwapchainAlphaFlag = swapchainAlphaFlag; }
        
        // Set is swapchain clipped
        void SetSwapchainClipped(VkBool32 swapchainClipped) { SwapchainClipped = swapchainClipped; }
        void SetOldSwapchain(VkSwapchainKHR oldSwapchain) { OldSwapchain = oldSwapchain; }

        // Set image view component swizzle by channel. 0 is for red, 1 is for green, 2 is for blue, 3 is for alpha. 
        // By default all set to VK_COMPONENT_SWIZZLE_IDENTITY
        void SetImageViewComponentSwizzle(int channel, VkComponentSwizzle componentSwizzle) { ImageViewComponentSwizzles[channel] = componentSwizzle; }
        
        VkSwapchainKHR* GetSwapchain() { return &Swapchain; }
        VkExtent2D GetSwapchainExtent() { return SwapchainExtent; }
        VkFormat GetSwapchainImageFormat() { return SwapchainImageFormat; }

        void Create();
        void Destroy();
    };
}