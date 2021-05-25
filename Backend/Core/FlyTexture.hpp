#pragma once

#include "FlyObject.hpp"

namespace FlyEngine::Backend
{
class FlyTexture : public FlyObject
{
public:
    FlyTexture(FlyDevice *flyDevice) : FlyObject(ObjectType::TEXTURE, flyDevice) {}
    ~FlyTexture() {}

    virtual void Initialize(const TextureInfo &info) = 0;
};

}  // namespace FlyEngine::Backend