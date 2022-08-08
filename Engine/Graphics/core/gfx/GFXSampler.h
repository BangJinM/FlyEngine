#ifndef CC_CORE_GFX_SAMPLER_H_
#define CC_CORE_GFX_SAMPLER_H_

#include "GFXDef.h"

namespace cc
{
namespace gfx
{

class Sampler : public GFXObject
{
public:
    Sampler(Device *device);
    virtual ~Sampler();

public:
    virtual bool initialize(const SamplerInfo &info) = 0;
    virtual void destroy()                           = 0;

    inline Device        *getDevice() const { return _device; }
    inline Filter         getMinFilter() const { return _minFilter; }
    inline Filter         getMagFilter() const { return _magFilter; }
    inline Filter         getMipFilter() const { return _mipFilter; }
    inline Address        getAddressU() const { return _addressU; }
    inline Address        getAddressV() const { return _addressV; }
    inline Address        getAddressW() const { return _addressW; }
    inline uint           getMaxAnisotropy() const { return _maxAnisotropy; }
    inline ComparisonFunc getCmpFunc() const { return _cmpFunc; }
    inline const Color   &getBorderColor() const { return _borderColor; }
    inline uint           getMinLOD() const { return _minLOD; }
    inline uint           getMaxLOD() const { return _maxLOD; }
    inline float          getMipLODBias() const { return _mipLODBias; }

protected:
    Device        *_device        = nullptr;
    Filter         _minFilter     = Filter::NONE;
    Filter         _magFilter     = Filter::NONE;
    Filter         _mipFilter     = Filter::NONE;
    Address        _addressU      = Address::WRAP;
    Address        _addressV      = Address::WRAP;
    Address        _addressW      = Address::WRAP;
    uint           _maxAnisotropy = 0;
    ComparisonFunc _cmpFunc       = ComparisonFunc::ALWAYS;
    Color          _borderColor;
    uint           _minLOD     = 0;
    uint           _maxLOD     = 0;
    float          _mipLODBias = 0.0f;
};

}  // namespace gfx
}  // namespace cc

#endif  // CC_CORE_GFX_SAMPLER_H_
