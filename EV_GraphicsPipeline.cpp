#include "EV_GraphicsPipeline.h"

namespace EV
{
    void EV_GraphicsPipeline::SetShaderInfo(const std::string& shaderFileName, const VkShaderStageFlagBits& shaderType,
        std::string EntryPointFunctionName, VkSpecializationInfo* SpecializationInfo)
    {
        ShadersInfos.push_back(ShaderInfo{shaderFileName, shaderType});
    }

    void EV_GraphicsPipeline::Create()
    {
        // Check if EV_Device variable was setup
        if (Device == nullptr)
            throw std::runtime_error("From EV_GraphicsPipeline::Create: You forget to setup EV_Device variable!");
        
        // Check if EV_Device variable was created before EV_GraphicsPipeline
        if (!Device->IsCreated())
            throw std::runtime_error("From EV_GraphicsPipeline::Create: You forget to create EV_Device variable! EV_GraphicsPipeline must be created after EV_Device!");

        // For_each to all setted shaders
        for (ShaderInfo shaderInfo : ShadersInfos)
        {
            std::vector<char> shaderFileVec;

            if (!EV::ReadFileBinary(shaderInfo.FileName, shaderFileVec))
                throw std::runtime_error("From EV_GraphicsPipeline::Create: Failed to open file! File name: " + shaderInfo.FileName);
        
            VkShaderModuleCreateInfo shaderModuleCreateInfo{};
            shaderModuleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
            shaderModuleCreateInfo.codeSize = shaderFileVec.size();
            shaderModuleCreateInfo.pCode = reinterpret_cast<const uint32_t*>(shaderFileVec.data());

            VkShaderModule shaderModule;

            VkResult createShaderModuleResult = vkCreateShaderModule(*Device->GetLogicalDevice(), &shaderModuleCreateInfo, nullptr, &shaderModule);
            
            if (createShaderModuleResult != VK_SUCCESS) 
                throw std::runtime_error("From EV_GraphicsPipeline::Create: Failed to create VkShaderModule! vkCreateShaderModule error code: " + std::to_string(createShaderModuleResult));

            VkPipelineShaderStageCreateInfo shaderStageInfo{};
            shaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
            shaderStageInfo.stage = shaderInfo.ShaderType;
            shaderStageInfo.module = shaderModule;
            shaderStageInfo.pName = shaderInfo.EntryPointFunctionName.c_str();
            shaderStageInfo.pSpecializationInfo = shaderInfo.SpecializationInfo;

            std::cout << shaderInfo.FileName << " " << shaderInfo.ShaderType << std::endl;

            pipelineShaderStageCreateInfos.push_back(shaderStageInfo);

            vkDestroyShaderModule(*Device->GetLogicalDevice(), shaderModule, nullptr); // ВОТТУТ
        }

        // Я удаляю модуль шейдеров в цикле, но не факт что оно так работает нормально. Искать по ВОТТУТ
        // vkDestroyShaderModule(*Device->GetLogicalDevice(), vertShaderModule, nullptr);
    }
}
    
    
    
