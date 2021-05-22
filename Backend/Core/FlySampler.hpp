#pragma once

#include "FlyObject.hpp"

namespace FlyEngine::Backend
{
class FlySampler : public FlyObject
{
public:
    FlySampler() : FlyObject(ObjectType::SAMPLER) {}
    ~FlySampler() {}
};

} // namespace FlyEngine::Backend