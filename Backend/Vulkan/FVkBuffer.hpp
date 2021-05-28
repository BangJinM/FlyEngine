#pragma once

#include "../Core/FlyBuffer.hpp"
#include "FVkDefine.hpp"

namespace FlyEngine::Backend
{
class FVkDevice;
class FVkBuffer : public FlyBuffer
{
public:
    FVkBuffer(FlyDevice *fVkDevice) : FlyBuffer(fVkDevice) {}
    ~FVkBuffer() {}

    virtual void Initialize(const BufferInfo &info) override;
    virtual void Destroy() override;

    virtual void CopyBuffer(char *bufferData, int bufferSize) override;
    virtual void CopyBuffer(FlyBuffer *srcBuffer) override;

    BufferInfo &GetBufferInfo() { return bufferInfo; }
    VkBuffer &  GetBuffer() { return buffer; }

private:
    void createVkBuffer();
    void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, int size);

private:
    BufferInfo     bufferInfo;
    VkBuffer       buffer       = NULL;
    VkDeviceMemory bufferMemory = NULL;
};

}  // namespace FlyEngine::Backend