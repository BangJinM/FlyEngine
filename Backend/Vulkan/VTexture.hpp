#pragma once

#include "FlyObject.hpp"

namespace FlyEngine::Backend
{
class FlyTexture : public FlyObject
{
public:
    FlyTexture() : FlyObject(ObjectType::TEXTURE) {}
    ~FlyTexture() {}
};

} // namespace FlyEngine::Backend