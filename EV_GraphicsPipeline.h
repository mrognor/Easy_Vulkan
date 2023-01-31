#pragma once

#include "EV_Classes.h"
#include "EV_Device.h"
#include "EV_Functions.h"

struct ShaderInfo
{
    std::string FileName;
    VkShaderStageFlagBits ShaderType;
    std::string EntryPointFunctionName = "main";
    VkSpecializationInfo* SpecializationInfo = nullptr;
};

namespace EV
{
    class EV_GraphicsPipeline
    {
    private:
        EV_Device* Device = nullptr;

        // Vector with all shader names and their types
        std::vector<ShaderInfo> ShadersInfos;
        // Vector with all shader structs to create graphics pipeline
        std::vector<VkPipelineShaderStageCreateInfo> pipelineShaderStageCreateInfos;
    public:
        void SetDevice(EV_Device* device) { Device = device; }
        // Function to set info about shader. 
        // First parametr is shader file name
        // Second paramert is shader type
        // Third parametr is optional and set shader entry point. 
        // That means that it's possible to combine multiple fragment shaders into a 
        // single shader module and use different entry points to differentiate between their behaviors.
        // Fourth parametr is optional and set shader specialization.
        // It allows you to specify values for shader constants. 
        // You can use a single shader module where its behavior can be configured at pipeline creation
        // by specifying different values for the constants used in it. This is more efficient than 
        // configuring the shader using variables at render time, because the compiler can do optimizations 
        // like eliminating if statements that depend on these values. If you don't have any constants like 
        // that, then you can set the member to nullptr, which our struct initialization does automatically.
        void SetShaderInfo(const std::string& shaderFileName, const VkShaderStageFlagBits& shaderType,
        std::string EntryPointFunctionName = "main", VkSpecializationInfo* SpecializationInfo = nullptr);

        void Create();
    };
} 
