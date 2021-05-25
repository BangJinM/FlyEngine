#pragma once

#include "FlyObject.hpp"

namespace FlyEngine::Backend
{

class FlyShader : public FlyObject
{
public:
    FlyShader(FlyDevice *flyDevice) : FlyObject(ObjectType::SHADER, flyDevice) {}
    ~FlyShader() {}

    virtual void Initialize(const ShaderInfo &info) = 0;
};

}  // namespace FlyEngine::Backend