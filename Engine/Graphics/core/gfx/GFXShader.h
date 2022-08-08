#ifndef CC_CORE_GFX_SHADER_H_
#define CC_CORE_GFX_SHADER_H_

#include "GFXDef.h"

namespace cc
{
namespace gfx
{

class Shader : public GFXObject
{
public:
    Shader(Device *device);
    virtual ~Shader();

public:
    virtual bool initialize(const ShaderInfo &info) = 0;
    virtual void destroy()                          = 0;

    inline Device                   *getDevice() const { return _device; }
    inline uint                      getID() const { return _shaderID; }
    inline const std::string        &getName() const { return _name; }
    inline const ShaderStageList    &getStages() const { return _stages; }
    inline const AttributeList      &getAttributes() const { return _attributes; }
    inline const UniformBlockList   &getBlocks() const { return _blocks; }
    inline const UniformSamplerList &getSamplers() const { return _samplers; }

protected:
    Device            *_device   = nullptr;
    uint               _shaderID = 0;
    std::string        _name;
    ShaderStageList    _stages;
    AttributeList      _attributes;
    UniformBlockList   _blocks;
    UniformSamplerList _samplers;
};

}  // namespace gfx
}  // namespace cc

#endif  // CC_CORE_GFX_TEXTURE_VIEW_H_
