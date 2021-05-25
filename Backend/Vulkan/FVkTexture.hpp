#pragma once

#include "../Core/FlyTexture.hpp"

namespace FlyEngine::Backend
{
class FVkTexture : public FlyTexture
{
public:
    FVkTexture(FlyDevice *fVkDevice) : FlyTexture(fVkDevice) {}
    ~FVkTexture() {}
    
    virtual void Destroy() override;
    virtual void Initialize(const TextureInfo &info) override;
};

}  // namespace FlyEngine::Backend
