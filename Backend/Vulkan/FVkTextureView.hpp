#pragma once

#include "../Core/FlyTextureView.hpp"

#include "FVkDefine.hpp"

namespace FlyEngine::Backend
{
class FVkTextureView : public FlyTextureView
{
public:
    FVkTextureView(FlyDevice *fVkDevice) : FlyTextureView(fVkDevice) {}
    ~FVkTextureView() {}

    virtual void Destroy() override;
    virtual void Initialize(const TextureViewInfo &info) override;

    VkImageView& GetVkImageView(){return textureView;}

private:
    void createImageView();

private:
    TextureViewInfo textureViewInfo;

    VkImageView textureView;
};

}  // namespace FlyEngine::Backend
