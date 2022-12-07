#include "EV_VkInstance.h"

namespace EV
{
    EV_Create_VkInstance::EV_Create_VkInstance()
    {
        /* From the specification:
        If not NULL, [pApplicationInfo] helps implementations recognize behavior inherent 
        to classes of applications. So that's what it is for.
        IHVs (independent hardware vendors) are going to provide application-specific optimizations 
        for any program that's popular enough to attract that kind of interest. That's inevitable.
        So Vulkan has two choices: it can either pretend that the inevitable is somehow not 
        going to happen, which means IHVs will do it anyway, using various heuristics to detect your 
        application. Or your application can just introduce itself and cut out the middle-man.
        Vulkan permits you to do the latter. And well-behaved engines will likely do likewise on 
        your program's behalf. */
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Easy Vulkan App";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        // A structure with all the parameters needed to create VkInstance
        InstanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        InstanceCreateInfo.pApplicationInfo = &appInfo;

        // We get the number of necessary vulkan extensions for glfw to work and their list
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;

        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        // Passing the number of extensions and their list to create VkInstance
        InstanceCreateInfo.enabledExtensionCount = glfwExtensionCount;
        InstanceCreateInfo.ppEnabledExtensionNames = glfwExtensions;
        
        // Enable validation layers
        #ifndef NDEBUG 
            InstanceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(RequiredValidationLayers.size());
            InstanceCreateInfo.ppEnabledLayerNames = RequiredValidationLayers.data();   
        #else
            InstanceCreateInfo.enabledLayerCount = 0;    
        #endif
    }

    void EV_Create_VkInstance::operator()(VkInstance& instance)
        {
            // Create VkInstance
            VkResult createInstanceResult = vkCreateInstance(&InstanceCreateInfo, nullptr, &instance);

            // We check if there were any errors when creating VkInstance
            if (createInstanceResult != VK_SUCCESS)
                throw std::runtime_error("Failed to create VkInstance!\nYou can see errors on specification: https://registry.khronos.org/VulkanSC/specs/1.0-extensions/man/html/VkResult.html\nError code: " + createInstanceResult);
        }

    void EV_Destroy_VkInstance(VkInstance& instance)
    {
        vkDestroyInstance(instance, nullptr);
    }
}