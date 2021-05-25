#pragma once

#include "FlyObject.hpp"

namespace FlyEngine::Backend
{
class FlyCommandBuffer : public FlyObject
{
public:
    FlyCommandBuffer(FlyDevice *flyDevice) : FlyObject(ObjectType::COMMAND_BUFFER, flyDevice) {}
    ~FlyCommandBuffer() {}

    virtual void Initialize(const CommandBufferInfo &info) = 0;
};

}  // namespace FlyEngine::Backend