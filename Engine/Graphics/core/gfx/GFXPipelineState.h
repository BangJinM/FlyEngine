#ifndef CC_CORE_GFX_PIPELINE_STATE_H_
#define CC_CORE_GFX_PIPELINE_STATE_H_

#include "GFXDef.h"

namespace cc
{
namespace gfx
{

class PipelineState : public GFXObject
{
public:
    PipelineState(Device *device);
    virtual ~PipelineState();

public:
    virtual bool initialize(const PipelineStateInfo &info) = 0;
    virtual void destroy()                                 = 0;

    inline Device                  *getDevice() const { return _device; }
    inline Shader                  *getShader() const { return _shader; }
    inline PrimitiveMode            getPrimitive() const { return _primitive; }
    inline DynamicStateFlags        getDynamicStates() const { return _dynamicStates; }
    inline const InputState        &getInputState() const { return _inputState; }
    inline const RasterizerState   &getRasterizerState() const { return _rasterizerState; }
    inline const DepthStencilState &getDepthStencilState() const { return _depthStencilState; }
    inline const BlendState        &getBlendState() const { return _blendState; }
    inline const RenderPass        *getRenderPass() const { return _renderPass; }
    inline const PipelineLayout    *getPipelineLayout() const { return _pipelineLayout; }

protected:
    Device           *_device        = nullptr;
    Shader           *_shader        = nullptr;
    PrimitiveMode     _primitive     = PrimitiveMode::TRIANGLE_LIST;
    DynamicStateFlags _dynamicStates = DynamicStateFlags::NONE;
    InputState        _inputState;
    RasterizerState   _rasterizerState;
    DepthStencilState _depthStencilState;
    BlendState        _blendState;
    RenderPass       *_renderPass     = nullptr;
    PipelineLayout   *_pipelineLayout = nullptr;
};

}  // namespace gfx
}  // namespace cc

#endif  // CC_CORE_GFX_PIPELINE_STATE_H_
