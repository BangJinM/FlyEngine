#pragma once

#include "FlyObject.hpp"

namespace FlyEngine::Backend
{
class FlyBuffer : public FlyObject
{
public:
    FlyBuffer() : FlyObject(ObjectType::BUFFER) {}
    ~FlyBuffer() {}
};

} // namespace FlyEngine::Backend