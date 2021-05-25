#pragma once

#include "FlyObject.hpp"

namespace FlyEngine::Backend
{
class FlyFence : public FlyObject
{
public:
    FlyFence(FlyDevice *flyDevice) : FlyObject(ObjectType::FENCE, flyDevice) {}
    ~FlyFence() {}

    virtual void Initialize(const FenceInfo &info) = 0;
};

}  // namespace FlyEngine::Backend