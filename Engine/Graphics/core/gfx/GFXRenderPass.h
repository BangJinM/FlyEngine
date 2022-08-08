#ifndef CC_CORE_GFX_RENDER_PASS_H_
#define CC_CORE_GFX_RENDER_PASS_H_

#include "GFXDef.h"

namespace cc
{
namespace gfx
{

class RenderPass : public GFXObject
{
public:
    RenderPass(Device *device);
    virtual ~RenderPass();

public:
    virtual bool initialize(const RenderPassInfo &info) = 0;
    virtual void destroy()                              = 0;

    inline Device                       *getDevice() const { return _device; }
    inline const ColorAttachmentList    &getColorAttachments() const { return _colorAttachments; }
    inline const DepthStencilAttachment &getDepthStencilAttachment() const { return _depthStencilAttachment; }
    inline const SubPassInfoList        &getSubPasses() const { return _subPasses; }
    inline uint                          getHash() const { return _hash; }

protected:
    uint computeHash() const;

    Device                *_device = nullptr;
    ColorAttachmentList    _colorAttachments;
    DepthStencilAttachment _depthStencilAttachment;
    SubPassInfoList        _subPasses;
    uint                   _hash = 0;
};

}  // namespace gfx
}  // namespace cc

#endif  // CC_CORE_GFX_RENDER_PASS_H_
