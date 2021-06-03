#include "FVkPipelineLayout.hpp"

#include "FVkDevice.hpp"

namespace FlyEngine::Backend
{
void FVkPipelineLayout::Destroy()
{
    FVkDevice *fVkDevice = (FVkDevice *)pFlyDevice;
    VkDevice & device    = fVkDevice->GetVkDevice();

    vkDestroyPipelineLayout(device, pipelineLayout, nullptr);
}

void FVkPipelineLayout::Initialize(const PipelineLayoutInfo &info)
{
    FVkDevice *fVkDevice = (FVkDevice *)pFlyDevice;
    VkDevice & device    = fVkDevice->GetVkDevice();

    VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
    pipelineLayoutInfo.sType                  = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutInfo.setLayoutCount         = 0;        // Optional
    pipelineLayoutInfo.pSetLayouts            = nullptr;  // Optional
    pipelineLayoutInfo.pushConstantRangeCount = 0;        // Optional
    pipelineLayoutInfo.pPushConstantRanges    = nullptr;  // Optional
    if (vkCreatePipelineLayout(device, &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS)
    {
        printf("error!!!!!!!!!!! vkCreatePipelineLayout");
    }
}
}  // namespace FlyEngine::Backend