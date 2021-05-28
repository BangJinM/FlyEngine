#pragma once

#include "../Core/FlyTexture.hpp"

#include "FVkDefine.hpp"

namespace FlyEngine::Backend
{
class FVkTexture : public FlyTexture
{
public:
    FVkTexture(FlyDevice *fVkDevice) : FlyTexture(fVkDevice) {}
    ~FVkTexture() {}

    virtual void Destroy() override;
    virtual void Initialize(const TextureInfo &info) override;
    virtual void CopyBufferToImage(FlyBuffer *srcBuffer, uint32_t width, uint32_t height) override;

private:
    void createImageView();

private:
    VkImage        textureImage;
    VkDeviceMemory bufferMemory = NULL;
    VkImageView    textureView;
};

}  // namespace FlyEngine::Backend
