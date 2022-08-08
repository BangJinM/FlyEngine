#ifndef CC_CORE_GFX_FRAME_BUFFER_H_
#define CC_CORE_GFX_FRAME_BUFFER_H_

#include "GFXDef.h"

namespace cc
{
namespace gfx
{

class Framebuffer : public GFXObject
{
public:
    Framebuffer(Device *device);
    virtual ~Framebuffer();

public:
    virtual bool initialize(const FramebufferInfo &info) = 0;
    virtual void destroy()                               = 0;

    inline Device            *getDevice() const { return _device; }
    inline RenderPass        *getRenderPass() const { return _renderPass; }
    inline const TextureList &getColorTextures() const { return _colorTextures; }
    inline Texture           *getDepthStencilTexture() const { return _depthStencilTexture; }

protected:
    Device     *_device     = nullptr;
    RenderPass *_renderPass = nullptr;
    TextureList _colorTextures;
    Texture    *_depthStencilTexture = nullptr;
};

}  // namespace gfx
}  // namespace cc

#endif  // CC_CORE_GFX_FRAME_BUFFER_H_
