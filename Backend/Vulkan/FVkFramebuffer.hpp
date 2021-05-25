#pragma once

#include "../Core/FlyFramebuffer.hpp"

namespace FlyEngine::Backend
{
class FVkFramebuffer : public FlyFramebuffer
{
public:
    FVkFramebuffer(FlyDevice *fVkDevice) : FlyFramebuffer(fVkDevice) {}
    ~FVkFramebuffer() {}

    virtual void Destroy() override;
    virtual void Initialize(const FramebufferInfo &info) override;
};

}  // namespace FlyEngine::Backend