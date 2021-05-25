#pragma once

#include "FlyDefine.hpp"
#include "FlyObject.hpp"
namespace FlyEngine::Backend
{
class FlyDevice;
class FlyBuffer : public FlyObject
{
public:
    FlyBuffer(FlyDevice *flyDevice) : FlyObject(ObjectType::BUFFER, flyDevice) {}
    ~FlyBuffer() {}

    virtual void Initialize(const BufferInfo &info) = 0;

    FlyDevice *GetDevice() { return pFlyDevice; }
};

}  // namespace FlyEngine::Backend