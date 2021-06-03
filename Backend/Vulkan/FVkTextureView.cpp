#include "FVkTextureView.hpp"

#include "FVkDevice.hpp"
#include "FVkSwapChain.hpp"
#include "FVkTexture.hpp"

namespace FlyEngine::Backend
{
void FVkTextureView::Destroy()
{
    FVkDevice *fVkDevice = (FVkDevice *)pFlyDevice;
    VkDevice & device    = fVkDevice->GetVkDevice();

    vkDestroyImageView(device, textureView, nullptr);
}

void FVkTextureView::Initialize(const TextureViewInfo &info)
{
    textureViewInfo = info;
    createImageView();
}

void FVkTextureView::createImageView()
{
    FVkDevice * fVkDevice = (FVkDevice *)pFlyDevice;
    VkDevice &  device    = fVkDevice->GetVkDevice();
    VkFormat    format    = fVkDevice->p_FVkSwapChain->GetVkFormat();
    FVkTexture *texture   = (FVkTexture *)textureViewInfo.texture;

    VkImageViewCreateInfo createInfo{};
    createInfo.sType                           = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    createInfo.image                           = texture->GetVkImage();
    createInfo.viewType                        = VK_IMAGE_VIEW_TYPE_2D;
    createInfo.format                          = format;
    createInfo.components.r                    = VK_COMPONENT_SWIZZLE_IDENTITY;
    createInfo.components.g                    = VK_COMPONENT_SWIZZLE_IDENTITY;
    createInfo.components.b                    = VK_COMPONENT_SWIZZLE_IDENTITY;
    createInfo.components.a                    = VK_COMPONENT_SWIZZLE_IDENTITY;
    createInfo.subresourceRange.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT;
    createInfo.subresourceRange.baseMipLevel   = 0;
    createInfo.subresourceRange.levelCount     = 1;
    createInfo.subresourceRange.baseArrayLayer = 0;
    createInfo.subresourceRange.layerCount     = 1;

    if (vkCreateImageView(device, &createInfo, nullptr, &textureView) != VK_SUCCESS)
    {}
}
}  // namespace FlyEngine::Backend