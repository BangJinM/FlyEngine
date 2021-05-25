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

    BufferInfo &GetBufferInfo() { return bufferInfo; }
    VkBuffer &  GetBuffer() { return buffer; }

private:
    BufferInfo bufferInfo;
    VkBuffer   buffer;
};

}  // namespace FlyEngine::Backend