#include "FVkBuffer.hpp"

#include "FVkDevice.hpp"
#include "FVkFunc.hpp"

namespace FlyEngine::Backend
{

void FVkBuffer::Initialize(const BufferInfo &info)
{
    bufferInfo           = std::move(info);
    FVkDevice *fVkDevice = (FVkDevice *)pFlyDevice;
    VkDevice & device    = fVkDevice->GetContext()->GetVkDevice();

    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType       = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size        = info.size;
    bufferInfo.usage       = MapVkBufferUsageFlagBits(info.usage);
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    if (vkCreateBuffer(device, &bufferInfo, nullptr, &buffer) != VK_SUCCESS)
    {
        buffer = VK_NULL_HANDLE;
    }
}

void FVkBuffer::Destroy()
{
    FVkDevice *fVkDevice = (FVkDevice *)pFlyDevice;
    VkDevice & device    = fVkDevice->GetContext()->GetVkDevice();

    vkDestroyBuffer(device, buffer, nullptr);
}

}  // namespace FlyEngine::Backend