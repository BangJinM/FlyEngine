#pragma once

#include "FlyObject.hpp"

namespace FlyEngine::Backend
{
class FlyDescriptorSetLayout : public FlyObject
{
public:
    FlyDescriptorSetLayout(FlyDevice *flyDevice) : FlyObject(ObjectType::DESCRIPTOR_SET_LAYOUT, flyDevice) {}
    ~FlyDescriptorSetLayout() {}

    virtual void Initialize(const DescriptorSetLayoutInfo &info) = 0;
};

}  // namespace FlyEngine::Backend