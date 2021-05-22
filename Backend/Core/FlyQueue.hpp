#pragma once

#include "FlyObject.hpp"

namespace FlyEngine::Backend
{
class FlyQueue : public FlyObject
{
public:
    FlyQueue() : FlyObject(ObjectType::QUEUE) {}
    ~FlyQueue() {}
};

} // namespace FlyEngine::Backend