#pragma once

#include "FlyObject.hpp"

namespace FlyEngine::Backend
{
class FlyCommandBuffer : public FlyObject
{
public:
    FlyCommandBuffer() : FlyObject(ObjectType::COMMAND_BUFFER) {}
    ~FlyCommandBuffer() {}
};

} // namespace FlyEngine::Backend