#pragma once

#include "FlyObject.hpp"

namespace FlyEngine::Backend
{
class FlyShader : public FlyObject
{
public:
    FlyShader() : FlyObject(ObjectType::SHADER) {}
    ~FlyShader() {}
};

} // namespace FlyEngine::Backend