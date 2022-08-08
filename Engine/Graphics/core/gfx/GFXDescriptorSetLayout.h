#ifndef CC_CORE_GFX_DESCRIPTOR_SET_LAYOUT_H_
#define CC_CORE_GFX_DESCRIPTOR_SET_LAYOUT_H_

#include "GFXDef.h"

namespace cc
{
namespace gfx
{

class DescriptorSetLayout : public GFXObject
{
public:
    DescriptorSetLayout(Device *device);
    virtual ~DescriptorSetLayout();

public:
    virtual bool initialize(const DescriptorSetLayoutInfo &info) = 0;
    virtual void destroy()                                       = 0;

    inline Device                               *getDevice() const { return _device; }
    inline const DescriptorSetLayoutBindingList &getBindings() const { return _bindings; }
    inline const std::vector<uint>              &getBindingIndices() const { return _bindingIndices; }
    inline const std::vector<uint>              &getDescriptorIndices() const { return _descriptorIndices; }
    inline const uint                            getDescriptorCount() const { return _descriptorCount; }

protected:
    Device                        *_device = nullptr;
    DescriptorSetLayoutBindingList _bindings;
    uint                           _descriptorCount = 0u;
    std::vector<uint>              _bindingIndices;
    std::vector<uint>              _descriptorIndices;
};

}  // namespace gfx
}  // namespace cc

#endif  // CC_CORE_GFX_DESCRIPTOR_SET_LAYOUT_H_
