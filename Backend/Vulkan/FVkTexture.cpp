#include "FVkTexture.hpp"

#include "FVkBuffer.hpp"
#include "FVkDevice.hpp"
#include "FVkSwapChain.hpp"

namespace FlyEngine::Backend
{
void FVkTexture::Destroy()
{
    FVkDevice *fVkDevice = (FVkDevice *)pFlyDevice;
    VkDevice & device    = fVkDevice->GetVkDevice();

    vkDestroyImage(device, textureImage, nullptr);
    vkFreeMemory(device, bufferMemory, nullptr);
}

void FVkTexture::Initialize(const TextureInfo &info)
{
    textureInfo = info;
    createImage();
}

void FVkTexture::CopyBufferToImage(FlyBuffer *srcBuffer, uint32_t width, uint32_t height)
{
    auto tempBuffer = (FVkBuffer *)srcBuffer;

    FVkDevice *     fVkDevice     = (FVkDevice *)pFlyDevice;
    VkDevice &      device        = fVkDevice->GetVkDevice();
    VkCommandBuffer commandBuffer = fVkDevice->BeginSingleTimeCommands();

    VkBufferImageCopy region{};
    region.bufferOffset                    = 0;
    region.bufferRowLength                 = 0;
    region.bufferImageHeight               = 0;
    region.imageSubresource.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT;
    region.imageSubresource.mipLevel       = 0;
    region.imageSubresource.baseArrayLayer = 0;
    region.imageSubresource.layerCount     = 1;
    region.imageOffset                     = {0, 0, 0};
    region.imageExtent                     = {width, height, 1};

    vkCmdCopyBufferToImage(commandBuffer, tempBuffer->GetBuffer(), textureImage, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);

    fVkDevice->EndSingleTimeCommands(commandBuffer);
}

void FVkTexture::createImage()
{
    FVkDevice *fVkDevice = (FVkDevice *)pFlyDevice;
    VkDevice & device    = fVkDevice->GetVkDevice();

    VkImageCreateInfo imageInfo{};
    imageInfo.sType         = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;                           //
    imageInfo.imageType     = VK_IMAGE_TYPE_2D;                                              //
    imageInfo.extent.width  = static_cast<uint32_t>(textureInfo.texWidth);                   //
    imageInfo.extent.height = static_cast<uint32_t>(textureInfo.texHeight);                  //
    imageInfo.extent.depth  = 1;                                                             //
    imageInfo.mipLevels     = 1;                                                             //
    imageInfo.arrayLayers   = 1;                                                             //
    imageInfo.format        = VK_FORMAT_R8G8B8A8_SRGB;                                       //
    imageInfo.format        = VK_FORMAT_R8G8B8A8_SRGB;                                       //
    imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;                                     //
    imageInfo.usage         = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;  //
    imageInfo.sharingMode   = VK_SHARING_MODE_EXCLUSIVE;                                     //
    imageInfo.samples       = VK_SAMPLE_COUNT_1_BIT;                                         //
    imageInfo.flags         = 0;                                                             //

    if (vkCreateImage(device, &imageInfo, nullptr, &textureImage) != VK_SUCCESS)
    {}

    VkMemoryRequirements memRequirements;
    vkGetImageMemoryRequirements(device, textureImage, &memRequirements);

    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType           = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize  = memRequirements.size;
    allocInfo.memoryTypeIndex = fVkDevice->FindMemoryType(
        memRequirements.memoryTypeBits, VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT);

    if (vkAllocateMemory(device, &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS)
    {}

    vkBindImageMemory(device, textureImage, bufferMemory, 0);
}
}  // namespace FlyEngine::Backend