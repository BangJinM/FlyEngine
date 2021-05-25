#pragma once

#include "FlyObject.hpp"

namespace FlyEngine::Backend
{
class FlyQueue : public FlyObject
{
public:
    FlyQueue(FlyDevice *flyDevice) : FlyObject(ObjectType::QUEUE, flyDevice) {}
    ~FlyQueue() {}

    virtual void Initialize(const QueueInfo &info) = 0;
};

}  // namespace FlyEngine::Backend