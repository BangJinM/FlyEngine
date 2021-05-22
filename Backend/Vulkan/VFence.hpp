#pragma once

#include "FlyObject.hpp"

namespace FlyEngine::Backend
{
class FlyFence : public FlyObject
{
public:
    FlyFence() : FlyObject(ObjectType::FENCE) {}
    ~FlyFence() {}
};

} // namespace FlyEngine::Backend