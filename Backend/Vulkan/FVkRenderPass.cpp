#include "FVkRenderPass.hpp"

#include <iostream>

#include "FVkDevice.hpp"

namespace FlyEngine::Backend
{
void FVkRenderPass::Destroy()
{
    FVkDevice *fVkDevice = (FVkDevice *)pFlyDevice;
    VkDevice & device    = fVkDevice->GetVkDevice();

    vkDestroyRenderPass(device, renderPass, nullptr);
}

void FVkRenderPass::Initialize(const RenderPassInfo &info)
{
    FVkDevice *fVkDevice = (FVkDevice *)pFlyDevice;
    VkDevice & device    = fVkDevice->GetVkDevice();

    VkAttachmentDescription colorAttachment{};
    colorAttachment.format         = VK_FORMAT_B8G8R8A8_SRGB;
    colorAttachment.samples        = VK_SAMPLE_COUNT_1_BIT;
    colorAttachment.loadOp         = VK_ATTACHMENT_LOAD_OP_CLEAR;
    colorAttachment.storeOp        = VK_ATTACHMENT_STORE_OP_STORE;
    colorAttachment.stencilLoadOp  = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    colorAttachment.initialLayout  = VK_IMAGE_LAYOUT_UNDEFINED;
    colorAttachment.finalLayout    = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

    VkAttachmentReference colorAttachmentRef{};
    colorAttachmentRef.attachment = 0;
    colorAttachmentRef.layout     = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkSubpassDescription subpass{};
    subpass.pipelineBindPoint    = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass.colorAttachmentCount = 1;
    subpass.pColorAttachments    = &colorAttachmentRef;

    VkRenderPassCreateInfo renderPassInfo{};
    renderPassInfo.sType           = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassInfo.attachmentCount = 1;
    renderPassInfo.pAttachments    = &colorAttachment;
    renderPassInfo.subpassCount    = 1;
    renderPassInfo.pSubpasses      = &subpass;

    if (vkCreateRenderPass(device, &renderPassInfo, nullptr, &renderPass) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create render pass!");
    }
}
}  // namespace FlyEngine::Backend