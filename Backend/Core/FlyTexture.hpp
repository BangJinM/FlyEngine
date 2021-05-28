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

    virtual void CopyBufferToImage(FlyBuffer *srcBuffer, uint32_t width, uint32_t height) = 0;
};

}  // namespace FlyEngine::Backend