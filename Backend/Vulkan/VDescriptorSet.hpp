#pragma once

#include "FlyObject.hpp"

namespace FlyEngine::Backend
{
class FlyDescriptorSet : public FlyObject
{
public:
    FlyDescriptorSet() : FlyObject(ObjectType::DESCRIPTOR_SET) {}
    ~FlyDescriptorSet() {}
};

} // namespace FlyEngine::Backend