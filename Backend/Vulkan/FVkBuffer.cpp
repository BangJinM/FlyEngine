#include "FVkBuffer.hpp"

#include "FVkDevice.hpp"
#include "FVkFunc.hpp"
#include "FVkInclude.hpp"

namespace FlyEngine::Backend
{

void FVkBuffer::Initialize(const BufferInfo &info)
{
    bufferInfo           = std::move(info);
    FVkDevice *fVkDevice = (FVkDevice *)pFlyDevice;
    VkDevice & device    = fVkDevice->GetVkDevice();

    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType       = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size        = info.size;
    bufferInfo.usage       = MapVkBufferUsageFlagBits(info.usage);
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    if (vkCreateBuffer(device, &bufferInfo, nullptr, &buffer) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to vkCreateBuffer!");
    }

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(device, buffer, &memRequirements);

    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType          = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    if (info.isStagingBuffer)
        allocInfo.memoryTypeIndex = fVkDevice->FindMemoryType(
            memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
    else
        allocInfo.memoryTypeIndex = fVkDevice->FindMemoryType(memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
    if (vkAllocateMemory(device, &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to vkCreateBuffer!");
    }

    vkBindBufferMemory(device, buffer, bufferMemory, 0);
}

void FVkBuffer::Destroy()
{
    FVkDevice *fVkDevice = (FVkDevice *)pFlyDevice;
    VkDevice & device    = fVkDevice->GetVkDevice();

    vkDestroyBuffer(device, buffer, nullptr);
    vkFreeMemory(device, bufferMemory, nullptr);
}

void FVkBuffer::CopyBuffer(char *bufferData, int bufferSize)
{
    FVkDevice *fVkDevice = (FVkDevice *)pFlyDevice;
    VkDevice & device    = fVkDevice->GetVkDevice();

    void *data;
    vkMapMemory(device, bufferMemory, 0, bufferSize, 0, &data);
    memcpy(data, bufferData, bufferSize);
    vkUnmapMemory(device, bufferMemory);
}

void FVkBuffer::CopyBuffer(FlyBuffer *srcBuffer)
{
    auto tempBuffer = (FVkBuffer *)srcBuffer;
    copyBuffer(tempBuffer->buffer, buffer, tempBuffer->bufferInfo.size);
}

void FVkBuffer::copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, int size)
{
    FVkDevice *fVkDevice = (FVkDevice *)pFlyDevice;
    VkDevice & device    = fVkDevice->GetVkDevice();

    VkCommandBuffer commandBuffer = fVkDevice->BeginSingleTimeCommands();

    VkBufferCopy copyRegion{};
    copyRegion.size = size;
    vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

    fVkDevice->EndSingleTimeCommands(commandBuffer);
}

}  // namespace FlyEngine::Backend