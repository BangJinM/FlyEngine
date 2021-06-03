#include "FVkFramebuffer.hpp"

#include <iostream>

#include "FVkDevice.hpp"
#include "FVkRenderPass.hpp"
#include "FVkSwapChain.hpp"
#include "FVkTextureView.hpp"

namespace FlyEngine::Backend
{
void FVkFramebuffer::Destroy()
{
    FVkDevice *fVkDevice = (FVkDevice *)pFlyDevice;
    VkDevice & device    = fVkDevice->GetVkDevice();
    vkDestroyFramebuffer(device, pFramebuffer, nullptr);
}

void FVkFramebuffer::Initialize(const FramebufferInfo &info)
{
    FVkDevice *    fVkDevice  = (FVkDevice *)pFlyDevice;
    VkDevice &     device     = fVkDevice->GetVkDevice();
    FVkRenderPass *renderPass = (FVkRenderPass *)info.renderPass;
    FVkSwapChain * swapChain  = (FVkSwapChain *)fVkDevice->GetFVkSwapChain();

    auto swapChainExtent = swapChain->GetSwapChainExtent();

    std::vector<VkImageView> attachments(info.views.size());
    for (size_t i = 0; i < info.views.size(); i++)
    {
        FVkTextureView *view = (FVkTextureView *)info.views[i];
        attachments[i]       = view->GetVkImageView();
    }

    VkFramebufferCreateInfo framebufferInfo{};
    framebufferInfo.sType           = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    framebufferInfo.renderPass      = renderPass->GetVkRenderPass();
    framebufferInfo.attachmentCount = attachments.size();
    framebufferInfo.pAttachments    = attachments.data();
    framebufferInfo.width           = swapChainExtent.width;
    framebufferInfo.height          = swapChainExtent.height;
    framebufferInfo.layers          = 1;

    if (vkCreateFramebuffer(device, &framebufferInfo, nullptr, &pFramebuffer) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create framebuffer!");
    }
}
}  // namespace FlyEngine::Backend