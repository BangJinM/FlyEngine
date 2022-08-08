#ifndef CC_CORE_GFX_CONTEXT_H_
#define CC_CORE_GFX_CONTEXT_H_

#include "GFXDef.h"

namespace cc
{
namespace gfx
{

class Context : public Object
{
public:
    Context(Device *device);
    virtual ~Context();

public:
    virtual bool initialize(const ContextInfo &info) = 0;
    virtual void destroy()                           = 0;
    virtual void present()                           = 0;

    inline Device   *getDevice() const { return _device; }
    inline Context  *getSharedContext() const { return _sharedContext; }
    inline VsyncMode getVsyncMode() const { return _vsyncMode; }
    inline Format    getColorFormat() const { return _colorFmt; }
    inline Format    getDepthStencilFormat() const { return _depthStencilFmt; }

protected:
    Device   *_device          = nullptr;
    void     *_windowHandle    = 0;
    Context  *_sharedContext   = nullptr;
    VsyncMode _vsyncMode       = VsyncMode::OFF;
    Format    _colorFmt        = Format::UNKNOWN;
    Format    _depthStencilFmt = Format::UNKNOWN;
};

}  // namespace gfx
}  // namespace cc

#endif  // CC_CORE_GFX_CONTEXT_H_
