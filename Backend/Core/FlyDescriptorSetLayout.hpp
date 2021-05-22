#pragma once

#include "FlyObject.hpp"

namespace FlyEngine::Backend
{
class FlyDescriptorSetLayout : public FlyObject
{
public:
    FlyDescriptorSetLayout() : FlyObject(ObjectType::DESCRIPTOR_SET_LAYOUT) {}
    ~FlyDescriptorSetLayout() {}
};

} // namespace FlyEngine::Backend