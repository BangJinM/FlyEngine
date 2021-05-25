#pragma once

#include "FlyObject.hpp"

namespace FlyEngine::Backend
{
class FlyFramebuffer : public FlyObject
{
public:
    FlyFramebuffer(FlyDevice *flyDevice) : FlyObject(ObjectType::FRAMEBUFFER, flyDevice) {}
    ~FlyFramebuffer() {}

    virtual void Initialize(const FramebufferInfo &info) = 0;
};

}  // namespace FlyEngine::Backend