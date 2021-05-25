#pragma once

#include "../Core/FlyCommandBuffer.hpp"

namespace FlyEngine::Backend
{
class FVkCommandBuffer : public FlyCommandBuffer
{
public:
    FVkCommandBuffer(FlyDevice *fVkDevice) : FlyCommandBuffer(fVkDevice) {}
    ~FVkCommandBuffer() {}

    virtual void Destroy() override;
    virtual void Initialize(const CommandBufferInfo &info) override;

private:
};

}  // namespace FlyEngine::Backend