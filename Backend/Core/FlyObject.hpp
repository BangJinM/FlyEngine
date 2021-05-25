#pragma once

#include "FlyDefine.hpp"

namespace FlyEngine::Backend
{
class FlyDevice;
class FlyObject
{
protected:
    ObjectType objectType = ObjectType::UNKNOWN;

public:
    ObjectType GetType() { return objectType; }

    FlyObject(ObjectType type, FlyDevice *flyDevice) : objectType(type), pFlyDevice(flyDevice) {}

    virtual void Destroy() = 0;

protected:
    FlyDevice *pFlyDevice;
};

}  // namespace FlyEngine::Backend