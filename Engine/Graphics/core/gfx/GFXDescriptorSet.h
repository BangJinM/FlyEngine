#ifndef CC_CORE_GFX_DESCRIPTOR_SET_H_
#define CC_CORE_GFX_DESCRIPTOR_SET_H_

#include "GFXDef.h"

namespace cc
{
namespace gfx
{

class DescriptorSet : public GFXObject
{
public:
    DescriptorSet(Device *device);
    virtual ~DescriptorSet();

public:
    virtual bool initialize(const DescriptorSetInfo &info) = 0;
    virtual void destroy()                                 = 0;
    virtual void update()                                  = 0;

    virtual void bindBuffer(uint binding, Buffer *buffer, uint index);
    virtual void bindTexture(uint binding, Texture *texture, uint index);
    virtual void bindSampler(uint binding, Sampler *sampler, uint index);

    // Functions invoked by JSB adapter
    bool bindBufferJSB(uint binding, Buffer *buffer, uint index);
    bool bindTextureJSB(uint binding, Texture *texture, uint index);
    bool bindSamplerJSB(uint binding, Sampler *sampler, uint index);

    Buffer  *getBuffer(uint binding, uint index) const;
    Texture *getTexture(uint binding, uint index) const;
    Sampler *getSampler(uint binding, uint index) const;

    inline Device  *getDevice() const { return _device; }
    inline void     bindBuffer(uint binding, Buffer *buffer) { bindBuffer(binding, buffer, 0u); }
    inline void     bindTexture(uint binding, Texture *texture) { bindTexture(binding, texture, 0u); }
    inline void     bindSampler(uint binding, Sampler *sampler) { bindSampler(binding, sampler, 0u); }
    inline Buffer  *getBuffer(uint binding) const { return getBuffer(binding, 0u); }
    inline Texture *getTexture(uint binding) const { return getTexture(binding, 0u); }
    inline Sampler *getSampler(uint binding) const { return getSampler(binding, 0u); }

protected:
    Device *_device = nullptr;

    DescriptorSetLayout *_layout;
    BufferList           _buffers;
    TextureList          _textures;
    SamplerList          _samplers;

    bool _isDirty = false;
};

}  // namespace gfx
}  // namespace cc

#endif  // CC_CORE_GFX_DESCRIPTOR_SET_H_
