#pragma once

#include "FlyDefine.hpp"

namespace FlyEngine::Backend
{
class FlyObject
{
protected:
    ObjectType objectType = ObjectType::UNKNOWN;

public:
    ObjectType GetType() { return objectType; }

    FlyObject(ObjectType type) : objectType(type) {}
};
} // namespace FlyEngine::Backend