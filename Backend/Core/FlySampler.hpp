#pragma once

#include "FlyObject.hpp"

namespace FlyEngine::Backend
{
class FlySampler : public FlyObject
{
public:
    FlySampler(FlyDevice *flyDevice) : FlyObject(ObjectType::SAMPLER, flyDevice) {}
    ~FlySampler() {}

    virtual void Initialize(const SamplerInfo &info) = 0;
};

}  // namespace FlyEngine::Backend