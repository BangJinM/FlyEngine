#include "FVkPipelineState.hpp"

#include "FVkDevice.hpp"
#include "FVkPipelineLayout.hpp"
#include "FVkShader.hpp"

namespace FlyEngine::Backend
{
void FVkPipelineState::Destroy() {}

void FVkPipelineState::Initialize(const PipelineStateInfo &info)
{
    // FVkDevice *fVkDevice = (FVkDevice *)pFlyDevice;
    // VkDevice & device    = fVkDevice->GetContext()->GetVkDevice();

    // FVkShader *shader = (FVkShader *)info.shader;
    // auto       stages = shader->GetStages();

    // FVkPipelineLayout *fvkPL          = (FVkPipelineLayout *)info.pipelineLayout;
    // VkPipelineLayout & pipelineLayout = fvkPL->GetVkPipelineLayout();

    // VkGraphicsPipelineCreateInfo pipelineInfo{};
    // pipelineInfo.sType               = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    // pipelineInfo.stageCount          = stages.size();
    // pipelineInfo.pStages             = stages.data();
    // pipelineInfo.pVertexInputState   = &vertexInputInfo;
    // pipelineInfo.pInputAssemblyState = &inputAssembly;
    // pipelineInfo.pViewportState      = &viewportState;
    // pipelineInfo.pRasterizationState = &rasterizer;
    // pipelineInfo.pMultisampleState   = &multisampling;
    // pipelineInfo.pDepthStencilState  = nullptr;  // Optional
    // pipelineInfo.pColorBlendState    = &colorBlending;
    // pipelineInfo.pDynamicState       = nullptr;  // Optional
    // pipelineInfo.layout              = pipelineLayout;
    // pipelineInfo.renderPass          = renderPass;
    // pipelineInfo.subpass             = 0;
    // pipelineInfo.basePipelineHandle  = VK_NULL_HANDLE;  // Optional
    // pipelineInfo.basePipelineIndex   = -1;              // Optional
    // if (vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &graphicsPipeline) != VK_SUCCESS)
    // {}
}
}  // namespace FlyEngine::Backend