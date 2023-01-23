#include "EV_Swapchain.h"

namespace EV
{
    void EV_Swapchain::SetSwapchainTransform(VkSurfaceTransformFlagBitsKHR swapchainTransform, bool disable)
    { 
        if(disable)
            IsSwapchainTransformEnabled = false;
        else
        { 
            IsSwapchainTransformEnabled = true;
            swapchainTransform = swapchainTransform; 
        }
    }

    void EV_Swapchain::Create()
    {
        // Check if EV_Device variable was setup
        if (Device == nullptr)
            throw std::runtime_error("From EV_Swapchain::Create: You forget to setup EV_Device variable!");
        
        // Check if EV_Device variable was created before EV_Swapchain
        if (!Device->IsCreated())
            throw std::runtime_error("From EV_Swapchain::Create: You forget to create EV_Device variable! EV_Swapchain must be created after EV_Device!");

        // Check if EV_Window variable was setup
        if (Window == nullptr)
            throw std::runtime_error("From EV_Swapchain::Create: You forget to setup EV_Window variable!");
        
        // Check if EV_Window variable was created before EV_Device
        if (!Window->IsCreated())
            throw std::runtime_error("From EV_Swapchain::Create: You forget to create EV_Window variable! EV_Swapchain must be created after EV_Window!");

        // Get window surface formats
        std::vector<VkSurfaceFormatKHR> windowSurfaceFormats = Device->GetWindowSurfaceFormats();

        // Set first available surface format
        VkSurfaceFormatKHR windowSurfaceFormat = windowSurfaceFormats[0];

        // Check if it is user-set function to pickd surface format
        if(PickWindowSurfaceFormat == nullptr)
        {
            for (const auto& availableFormat : windowSurfaceFormats) 
            {
                if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) 
                    windowSurfaceFormat = availableFormat;
            }
        }
        else windowSurfaceFormat = PickWindowSurfaceFormat(windowSurfaceFormats);

        // Get window surface presentation modes
        std::vector<VkPresentModeKHR> windowSurfacePresentationModes = Device->GetWindowSurfacePresentationModes();

        VkPresentModeKHR windowSurfacePresentationMode = VK_PRESENT_MODE_FIFO_KHR;

        if (PickWindowSurfacePresentationMode == nullptr)
        {
            for (const auto& availablePresentMode : windowSurfacePresentationModes) 
            {
                if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) 
                    windowSurfacePresentationMode = VK_PRESENT_MODE_MAILBOX_KHR;
            }
        }
        else windowSurfacePresentationMode = PickWindowSurfacePresentationMode(windowSurfacePresentationModes);

        // Set swapchain extent. Extent equals swapchain images resolution
        VkSurfaceCapabilitiesKHR windowSurfaceCapabilities = Device->GetWindowSurfaceCapabilities();

        VkExtent2D swapchainExtent;

        // Get swapchain extent
        if (windowSurfaceCapabilities.currentExtent.width != -1)
            swapchainExtent = windowSurfaceCapabilities.currentExtent;
        else
        {
            int width, height;
            glfwGetFramebufferSize(Window->GetGLFWWindow(), &width, &height);

            swapchainExtent = { static_cast<uint32_t>(width), static_cast<uint32_t>(height) };

            // Clamp extent width
            if (swapchainExtent.width < windowSurfaceCapabilities.minImageExtent.width)
                swapchainExtent.width = windowSurfaceCapabilities.minImageExtent.width;
            if (swapchainExtent.width > windowSurfaceCapabilities.maxImageExtent.width)
                swapchainExtent.width = windowSurfaceCapabilities.maxImageExtent.width;

            // Clamp extent height
            if (swapchainExtent.height < windowSurfaceCapabilities.minImageExtent.height)
                swapchainExtent.height = windowSurfaceCapabilities.minImageExtent.height;
            if (swapchainExtent.height > windowSurfaceCapabilities.maxImageExtent.height)
                swapchainExtent.height = windowSurfaceCapabilities.maxImageExtent.height;
        }

        // Amount of images in swapchain
        uint32_t swapchainImageCount = windowSurfaceCapabilities.minImageCount + 1;
        // Checks what swapchainImageCount not bigger then maxImageCount.
        // If max image count equals 0 that means that no max limit
        if (windowSurfaceCapabilities.maxImageCount > 0 && swapchainImageCount > windowSurfaceCapabilities.maxImageCount) 
            swapchainImageCount = windowSurfaceCapabilities.maxImageCount;
        
        // Swapchain create info
        VkSwapchainCreateInfoKHR swapchainCreateInfo{};
        swapchainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        swapchainCreateInfo.surface = *Window->GetWindowSurface();
        swapchainCreateInfo.minImageCount = swapchainImageCount;
        swapchainCreateInfo.imageFormat = windowSurfaceFormat.format;
        swapchainCreateInfo.imageColorSpace = windowSurfaceFormat.colorSpace;
        swapchainCreateInfo.imageExtent = swapchainExtent;
        swapchainCreateInfo.imageArrayLayers = SwapchainImageArrayLayers;
        swapchainCreateInfo.imageUsage = SwapchainImageUsage;

        // VK_SHARING_MODE_Exclusive may be better performance
        // but require queue ownership transfer
        // https://registry.khronos.org/vulkan/specs/1.3-extensions/html/vkspec.html#synchronization-queue-transfers
        if (Device->GetGraphicsQueueIndex() != Device->GetPresentationQueueIndex()) 
        {
            uint32_t queueFamilyIndices[] = {Device->GetGraphicsQueueIndex(), Device->GetPresentationQueueIndex()};
            swapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
            swapchainCreateInfo.queueFamilyIndexCount = 2;
            swapchainCreateInfo.pQueueFamilyIndices = queueFamilyIndices;
        } 
        else 
        {
            swapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
            swapchainCreateInfo.queueFamilyIndexCount = 0; 
            swapchainCreateInfo.pQueueFamilyIndices = nullptr;
        }

        // Set swapchain transform
        if (IsSwapchainTransformEnabled)
            swapchainCreateInfo.preTransform = SwapchainTransform;
        else
            swapchainCreateInfo.preTransform = windowSurfaceCapabilities.currentTransform;

        // Set swapchain alpha channel
        swapchainCreateInfo.compositeAlpha = SwapchainAlphaFlag;
        // Set swapchain presentation mode
        swapchainCreateInfo.presentMode = windowSurfacePresentationMode;
        // Set swapchain clipped or not
        swapchainCreateInfo.clipped = SwapchainClipped; 
        // Set old swapchain
        swapchainCreateInfo.oldSwapchain = OldSwapchain;     

        VkResult swapchainCreateResult = vkCreateSwapchainKHR(*Device->GetLogicalDevice(), &swapchainCreateInfo, nullptr, &SwapChain);

        if (swapchainCreateResult != VK_SUCCESS) 
            throw std::runtime_error("From EV_Swapchain::Create: Failed to create VkSwapchainKHR! vkCreateSwapchainKHR error code: " + std::to_string(swapchainCreateResult));
    }

    void EV_Swapchain::Destroy()
    {
        vkDestroySwapchainKHR(*Device->GetLogicalDevice(), SwapChain, nullptr);
    }
}