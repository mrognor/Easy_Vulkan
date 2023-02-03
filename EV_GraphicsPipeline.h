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

        // Vector with all pipeline dynamic states
        std::vector<VkDynamicState> PipelineDynamicStates;

        // Variable to set pipeline geometry topology
        VkPrimitiveTopology Topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

        // If you set the BreakTopology member to VK_TRUE, then it's possible to break up lines and triangles in the _STRIP 
        // topology modes by using a special index of 0xFFFF or 0xFFFFFFFF.
        VkBool32 BreakTopology = VK_FALSE;

        // If DepthClampEnable is set to VK_TRUE, then fragments that are beyond the near and far planes
        // are clamped to them as opposed to discarding them. This is useful in some special cases like shadow maps.
        // Using this requires enabling a GPU feature.
        VkBool32 DepthClampEnable = VK_FALSE;

        // If RasterizerDiscardEnable is set to VK_TRUE, then geometry never passes through the rasterizer stage. 
        // This basically disables any output to the framebuffer
        VkBool32 RasterizerDisable = VK_FALSE;

        // The polygonMode determines how fragments are generated for geometry. The following modes are available:
        // VK_POLYGON_MODE_FILL: fill the area of the polygon with fragments
        // VK_POLYGON_MODE_LINE: polygon edges are drawn as lines
        // VK_POLYGON_MODE_POINT: polygon vertices are drawn as points
        // Using any mode other than fill requires enabling a GPU feature fillModeNonSolid.
        VkPolygonMode PolygonMode = VK_POLYGON_MODE_FILL;
        
        // It describes the thickness of lines in terms of number of fragments. 
        // The maximum line width that is supported depends on the hardware and any line thicker than 1.0f 
        // requires you to enable the wideLines GPU feature.
        float LineWidth = 1.0f;

        // The variable determines the type of face culling to use. You can disable culling, 
        // cull the front faces, cull the back faces or both
        VkCullModeFlagBits CullMode = VK_CULL_MODE_BACK_BIT;

        // The frontFace variable specifies the vertex order for faces to be 
        // considered front-facing and can be clockwise or counterclockwise.
        // VK_FRONT_FACE_COUNTER_CLOCKWISE specifies that a triangle with positive area is considered front-facing.
        // VK_FRONT_FACE_CLOCKWISE specifies that a triangle with negative area is considered front-facing.
        // Any triangle which is not front-facing is back-facing, including zero-area triangles.
        VkFrontFace FrontFace = VK_FRONT_FACE_CLOCKWISE;

        // todo write comments
        VkBool32 DepthBiasEnable = VK_FALSE;
        float DepthBiasConstantFactor = 0.0f;
        float DepthBiasClamp = 0.0f;
        float DepthBiasSlopeFactor = 0.0f;

        // todo write comments
        VkColorComponentFlags ColorFlags = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
        VkBool32 ColorBlendEnable = VK_FALSE;
        VkBlendFactor SrcColorBlendFactor = VK_BLEND_FACTOR_ONE;
        VkBlendFactor DstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
        VkBlendOp ColorBlendOperation = VK_BLEND_OP_ADD;
        VkBlendFactor SrcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
        VkBlendFactor DstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
        VkBlendOp AlphaBlendOperation = VK_BLEND_OP_ADD;

        // todo write comments
        VkBool32 LogicOperationEnable = VK_FALSE;
        VkLogicOp LogicOperation = VK_LOGIC_OP_COPY;
        float LogicOperationConstants[4] = {0.0f, 0.0f, 0.0f, 0.0f};

        VkPipelineLayout PipelineLayout;
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
        
        // Add one dynamic state into pipeline
        void AddPipelineDynamicState(VkDynamicState pipelineDynamicState) { PipelineDynamicStates.push_back(pipelineDynamicState); }

        // Add dynamic states into pipeline
        void AddPipelineDynamicStates(std::vector<VkDynamicState> pipelineDynamicStates) { PipelineDynamicStates.insert(PipelineDynamicStates.end(), pipelineDynamicStates.begin(), pipelineDynamicStates.end()); }

        // VK_PRIMITIVE_TOPOLOGY_POINT_LIST: points from vertices
        // VK_PRIMITIVE_TOPOLOGY_LINE_LIST: line from every 2 vertices without reuse
        // VK_PRIMITIVE_TOPOLOGY_LINE_STRIP: the end vertex of every line is used as start vertex for the next line
        // VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST: triangle from every 3 vertices without reuse
        // VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP: the second and third vertex of every triangle are used as first two vertices of the next triangle
        // By default setted to VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST
        void SetTopology(VkPrimitiveTopology topology) { Topology = topology; }

        // If you set the BreakTopology member to VK_TRUE, then it's possible to break up lines and triangles in the _STRIP 
        // topology modes by using a special index of 0xFFFF or 0xFFFFFFFF.
        // By default setted to false
        void SetBreakTopology(VkBool32 breakTopology) { BreakTopology = breakTopology; }

        // If set to VK_TRUE, then fragments that are beyond the near and far planes are clamped to them as opposed to 
        // discarding them. This is useful in some special cases like shadow maps. 
        // Using this requires enabling a GPU feature.
        void SetDepthClampEnable(VkBool32 depthClampEnable) { DepthClampEnable = depthClampEnable; }

        // If set to VK_TRUE, then geometry never passes through the rasterizer stage. 
        // This basically disables any output to the framebuffer
        void SetRasterizerDisable(VkBool32 rasterizerDisable) { RasterizerDisable = rasterizerDisable; }

        // VK_POLYGON_MODE_FILL: fill the area of the polygon with fragments
        // VK_POLYGON_MODE_LINE: polygon edges are drawn as lines
        // VK_POLYGON_MODE_POINT: polygon vertices are drawn as points
        // Using any mode other than fill requires enabling the fillModeNonSolid GPU feature 
        void SetPolygonMode(VkPolygonMode polygonMode) { PolygonMode = polygonMode; }

        // It describes the thickness of lines in terms of number of fragments. 
        // The maximum line width that is supported depends on the hardware and any line thicker than 1.0f 
        // requires you to enable the wideLines GPU feature
        void SetLineWidth(float lineWidth) { LineWidth = lineWidth; }

        // The variable determines the type of face culling to use. You can disable culling, 
        // cull the front faces, cull the back faces or both
        void SetCullMode(VkCullModeFlagBits cullMode) { CullMode = cullMode; }

        // The frontFace variable specifies the vertex order for faces to be 
        // considered front-facing and can be clockwise or counterclockwise.
        // VK_FRONT_FACE_COUNTER_CLOCKWISE specifies that a triangle with positive area is considered front-facing.
        // VK_FRONT_FACE_CLOCKWISE specifies that a triangle with negative area is considered front-facing.
        // Any triangle which is not front-facing is back-facing, including zero-area triangles.
        void SetFrontFace(VkFrontFace frontFace) { FrontFace = frontFace; }

        // todo write comments
        void SetDepthBiasEnable(VkBool32 depthBiasEnable) { DepthBiasEnable = depthBiasEnable; };
        void SetDepthBiasConstantFactor(float depthBiasConstantFactor) { DepthBiasConstantFactor = depthBiasConstantFactor; };
        void SetDepthBiasClamp(float depthBiasClamp) { DepthBiasClamp = depthBiasClamp; };
        void SetDepthBiasSlopeFactor(float depthBiasSlopeFactor) { DepthBiasSlopeFactor = depthBiasSlopeFactor; };

        // Enable color blending and set flags with color components
        void SetColorBlendEnable(VkBool32 colorBlendEnable, VkColorComponentFlags colorFlags) 
        { ColorBlendEnable = colorBlendEnable; ColorFlags = colorFlags; }

        // Set color blending. First parametr is source color factor. Second is destination color factor
        // Third parametr is color blending option
        void SetColorBlending(VkBlendFactor srcColorBlendFactor, VkBlendFactor dstColorBlendFactor, VkBlendOp colorBlendOperation)
        { SrcColorBlendFactor = srcColorBlendFactor; DstColorBlendFactor = dstColorBlendFactor; ColorBlendOperation = colorBlendOperation; }
        
        // Set alpha blending. First parametr is source alpha factor. Second is destination alpha factor
        // Third parametr is alpha blending option
        void SetAlphaBlending(VkBlendFactor srcAlphaBlendFactor, VkBlendFactor dstAlphaBlendFactor, VkBlendOp alphaBlendOperation)
        { SrcAlphaBlendFactor = srcAlphaBlendFactor; DstAlphaBlendFactor = dstAlphaBlendFactor; AlphaBlendOperation = alphaBlendOperation; }
        
        // todo write comments
        void SetLogicOperationEnable(VkBool32 logicOperationEnable) { LogicOperationEnable = logicOperationEnable; }
        void SetLogicOperation(VkLogicOp logicOperation) { LogicOperation = logicOperation; }
        void SetLogicOperationConstant(int constNum, float constValue) { LogicOperationConstants[constNum] = constValue; }
        void SetLogicOperationConstants(float constValue0, float constValue1, float constValue2, float constValue3) 
        { LogicOperationConstants[0] = constValue0; LogicOperationConstants[1] = constValue1; LogicOperationConstants[2] = constValue2; LogicOperationConstants[3] = constValue3; }

        void Create();

        void Destroy();
    };
} 
