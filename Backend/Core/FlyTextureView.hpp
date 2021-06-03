#pragma once

#include "FlyObject.hpp"

namespace FlyEngine::Backend
{
class FlyTextureView : public FlyObject
{
public:
    FlyTextureView(FlyDevice *flyDevice) : FlyObject(ObjectType::TEXTURE_VIEW, flyDevice) {}
    ~FlyTextureView() {}

    virtual void Initialize(const struct TextureViewInfo &info) = 0;
};

}  // namespace FlyEngine::Backend