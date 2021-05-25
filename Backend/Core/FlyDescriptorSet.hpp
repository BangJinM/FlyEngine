#pragma once

#include "FlyObject.hpp"

namespace FlyEngine::Backend
{
class FlyDescriptorSet : public FlyObject
{
public:
    FlyDescriptorSet(FlyDevice *flyDevice) : FlyObject(ObjectType::DESCRIPTOR_SET, flyDevice) {}
    ~FlyDescriptorSet() {}

    virtual void Initialize(const DescriptorSetInfo &info) = 0;
};

}  // namespace FlyEngine::Backend