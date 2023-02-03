#include "EV_GraphicsPipeline.h"

namespace EV
{
    void EV_GraphicsPipeline::SetShaderInfo(const std::string& shaderFileName, const VkShaderStageFlagBits& shaderType,
        std::string EntryPointFunctionName, VkSpecializationInfo* SpecializationInfo)
    {
        ShadersInfos.push_back(ShaderInfo{shaderFileName, shaderType, EntryPointFunctionName, SpecializationInfo});
    }

    void EV_GraphicsPipeline::Create()
    {
        // Check if EV_Device variable was setup
        if (Device == nullptr)
            throw std::runtime_error("From EV_GraphicsPipeline::Create: You forget to setup EV_Device variable!");
        
        // Check if EV_Device variable was created before EV_GraphicsPipeline
        if (!Device->GetIsCreated())
            throw std::runtime_error("From EV_GraphicsPipeline::Create: You forget to create EV_Device variable! EV_GraphicsPipeline must be created after EV_Device!");

        // Set all shaders
        for (ShaderInfo shaderInfo : ShadersInfos)
        {
            std::vector<char> shaderFileVec;

            // Read binary data from file
            if (!EV::ReadFileBinary(shaderInfo.FileName, shaderFileVec))
                throw std::runtime_error("From EV_GraphicsPipeline::Create: Failed to open file! File name: " + shaderInfo.FileName);
        
            // Shader module create info
            VkShaderModuleCreateInfo shaderModuleCreateInfo{};
            shaderModuleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
            shaderModuleCreateInfo.codeSize = shaderFileVec.size();
            shaderModuleCreateInfo.pCode = reinterpret_cast<const uint32_t*>(shaderFileVec.data());

            // Create shader module
            VkShaderModule shaderModule;

            VkResult createShaderModuleResult = vkCreateShaderModule(*Device->GetLogicalDevice(), &shaderModuleCreateInfo, nullptr, &shaderModule);
            
            if (createShaderModuleResult != VK_SUCCESS) 
                throw std::runtime_error("From EV_GraphicsPipeline::Create: Failed to create VkShaderModule! vkCreateShaderModule error code: " + std::to_string(createShaderModuleResult));

            // Shader stage info to create pipeline
            VkPipelineShaderStageCreateInfo shaderStageInfo{};
            shaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
            shaderStageInfo.stage = shaderInfo.ShaderType;
            shaderStageInfo.module = shaderModule;
            shaderStageInfo.pName = shaderInfo.EntryPointFunctionName.c_str();
            shaderStageInfo.pSpecializationInfo = shaderInfo.SpecializationInfo;

            pipelineShaderStageCreateInfos.push_back(shaderStageInfo);

            // todo dont shure what it will be work
            vkDestroyShaderModule(*Device->GetLogicalDevice(), shaderModule, nullptr); 
        }

        // Set all dynamic states to create pipeline 
        VkPipelineDynamicStateCreateInfo pipelineDynamicStateCreateInfo{};
        pipelineDynamicStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
        pipelineDynamicStateCreateInfo.dynamicStateCount = static_cast<uint32_t>(PipelineDynamicStates.size());
        pipelineDynamicStateCreateInfo.pDynamicStates = PipelineDynamicStates.data();

        // todo make later
        VkPipelineVertexInputStateCreateInfo pipelineVertexInputStateCreateInfo{};
        pipelineVertexInputStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
        pipelineVertexInputStateCreateInfo.vertexBindingDescriptionCount = 0;
        pipelineVertexInputStateCreateInfo.pVertexBindingDescriptions = nullptr; // Optional
        pipelineVertexInputStateCreateInfo.vertexAttributeDescriptionCount = 0;
        pipelineVertexInputStateCreateInfo.pVertexAttributeDescriptions = nullptr; // Optional

        // Set input assembly to create pipeline.
        // The VkPipelineInputAssemblyStateCreateInfo struct describes two things: 
        // what kind of geometry will be drawn from the vertices and if primitive restart should be enabled. 
        // The former is specified in the topology member and can have values like:

        // Normally, the vertices are loaded from the vertex buffer by index in sequential order, 
        // but with an element buffer you can specify the indices to use yourself. 
        // This allows you to perform optimizations like reusing vertices. If you set the primitiveRestartEnable 
        // member to VK_TRUE, then it's possible to break up lines and triangles in the _STRIP topology modes 
        // by using a special index of 0xFFFF or 0xFFFFFFFF.
        VkPipelineInputAssemblyStateCreateInfo pipelineInputAssemblyStateCreateInfo{};
        pipelineInputAssemblyStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
        pipelineInputAssemblyStateCreateInfo.topology = Topology;
        pipelineInputAssemblyStateCreateInfo.primitiveRestartEnable = BreakTopology;

        // Pipeline viewport
        VkPipelineViewportStateCreateInfo pipelineViewportStateCreateInfo{};
        pipelineViewportStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        pipelineViewportStateCreateInfo.viewportCount = 1;
        pipelineViewportStateCreateInfo.scissorCount = 1;

        // PipelineRasterizer
        VkPipelineRasterizationStateCreateInfo pipelineRasterizationStateCreateInfo{};
        pipelineRasterizationStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
        pipelineRasterizationStateCreateInfo.depthClampEnable = DepthClampEnable;
        pipelineRasterizationStateCreateInfo.rasterizerDiscardEnable = RasterizerDisable;
        pipelineRasterizationStateCreateInfo.polygonMode = PolygonMode;
        pipelineRasterizationStateCreateInfo.lineWidth = LineWidth;
        pipelineRasterizationStateCreateInfo.cullMode = CullMode;
        pipelineRasterizationStateCreateInfo.frontFace = FrontFace;
        pipelineRasterizationStateCreateInfo.depthBiasEnable = DepthBiasEnable;
        pipelineRasterizationStateCreateInfo.depthBiasConstantFactor = DepthBiasConstantFactor;
        pipelineRasterizationStateCreateInfo.depthBiasClamp = DepthBiasClamp;
        pipelineRasterizationStateCreateInfo.depthBiasSlopeFactor = DepthBiasSlopeFactor;

        // todo make later
        VkPipelineMultisampleStateCreateInfo pipelineMultisampleStateCreateInfo{};
        pipelineMultisampleStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
        pipelineMultisampleStateCreateInfo.sampleShadingEnable = VK_FALSE;
        pipelineMultisampleStateCreateInfo.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
        pipelineMultisampleStateCreateInfo.minSampleShading = 1.0f; // Optional
        pipelineMultisampleStateCreateInfo.pSampleMask = nullptr; // Optional
        pipelineMultisampleStateCreateInfo.alphaToCoverageEnable = VK_FALSE; // Optional
        pipelineMultisampleStateCreateInfo.alphaToOneEnable = VK_FALSE; // Optional


        /* 
        This per-framebuffer struct allows you to configure the first way of color blending. 
        The operations that will be performed are best demonstrated using the following pseudocode:

        if (blendEnable) {
            finalColor.rgb = (srcColorBlendFactor * newColor.rgb) <colorBlendOp> (dstColorBlendFactor * oldColor.rgb);
            finalColor.a = (srcAlphaBlendFactor * newColor.a) <alphaBlendOp> (dstAlphaBlendFactor * oldColor.a);
        } else {
            finalColor = newColor;
        }

        finalColor = finalColor & colorWriteMask;
        */
        VkPipelineColorBlendAttachmentState pipelineColorBlendAttachmentState{};
        pipelineColorBlendAttachmentState.colorWriteMask = ColorFlags;
        pipelineColorBlendAttachmentState.blendEnable = ColorBlendEnable;
        pipelineColorBlendAttachmentState.srcColorBlendFactor = SrcColorBlendFactor;
        pipelineColorBlendAttachmentState.dstColorBlendFactor = DstColorBlendFactor;
        pipelineColorBlendAttachmentState.colorBlendOp = ColorBlendOperation;
        pipelineColorBlendAttachmentState.srcAlphaBlendFactor = SrcAlphaBlendFactor;
        pipelineColorBlendAttachmentState.dstAlphaBlendFactor = DstAlphaBlendFactor;
        pipelineColorBlendAttachmentState.alphaBlendOp = AlphaBlendOperation;

        VkPipelineColorBlendStateCreateInfo pipelineColorBlendStateCreateInfo{};
        pipelineColorBlendStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
        pipelineColorBlendStateCreateInfo.logicOpEnable = LogicOperationEnable;
        pipelineColorBlendStateCreateInfo.logicOp = LogicOperation;
        pipelineColorBlendStateCreateInfo.attachmentCount = 1; // todo дать возможность указывать несколько
        pipelineColorBlendStateCreateInfo.pAttachments = &pipelineColorBlendAttachmentState;
        pipelineColorBlendStateCreateInfo.blendConstants[0] = LogicOperationConstants[0];
        pipelineColorBlendStateCreateInfo.blendConstants[1] = LogicOperationConstants[1];
        pipelineColorBlendStateCreateInfo.blendConstants[2] = LogicOperationConstants[2];
        pipelineColorBlendStateCreateInfo.blendConstants[3] = LogicOperationConstants[3];

        // todo Доделать
        VkPipelineLayoutCreateInfo pipelineLayoutCreteInfo{};
        pipelineLayoutCreteInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutCreteInfo.setLayoutCount = 0; // Optional
        pipelineLayoutCreteInfo.pSetLayouts = nullptr; // Optional
        pipelineLayoutCreteInfo.pushConstantRangeCount = 0; // Optional
        pipelineLayoutCreteInfo.pPushConstantRanges = nullptr; // Optional

        if (vkCreatePipelineLayout(*Device->GetLogicalDevice(), &pipelineLayoutCreteInfo, nullptr, &PipelineLayout) != VK_SUCCESS) {
            throw std::runtime_error("failed to create pipeline layout!");
        }

        // todo
        // Я удаляю модуль шейдеров в цикле, но не факт что оно так работает нормально.
        // vkDestroyShaderModule(*Device->GetLogicalDevice(), vertShaderModule, nullptr);
    }

    void EV_GraphicsPipeline::Destroy()
    {
        vkDestroyPipelineLayout(*Device->GetLogicalDevice(), PipelineLayout, nullptr);
    }
}
    
    
    
