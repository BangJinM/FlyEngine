#ifndef CC_CORE_GFX_BUFFER_H_
#define CC_CORE_GFX_BUFFER_H_

#include "GFXDef.h"

namespace cc
{
namespace gfx
{

class Buffer : public GFXObject
{
public:
    Buffer(Device *device);
    virtual ~Buffer();

public:
    virtual bool initialize(const BufferInfo &info)     = 0;
    virtual bool initialize(const BufferViewInfo &info) = 0;
    virtual void destroy()                              = 0;
    virtual void resize(uint size)                      = 0;
    virtual void update(void *buffer, uint size)        = 0;

    inline Device     *getDevice() const { return _device; }
    inline BufferUsage getUsage() const { return _usage; }
    inline MemoryUsage getMemUsage() const { return _memUsage; }
    inline uint        getStride() const { return _stride; }
    inline uint        getCount() const { return _count; }
    inline uint        getSize() const { return _size; }
    inline BufferFlags getFlags() const { return _flags; }

protected:
    Device     *_device       = nullptr;
    BufferUsage _usage        = BufferUsageBit::NONE;
    MemoryUsage _memUsage     = MemoryUsageBit::NONE;
    uint        _stride       = 0u;
    uint        _count        = 0u;
    uint        _size         = 0u;
    uint        _offset       = 0u;
    BufferFlags _flags        = BufferFlagBit::NONE;
    bool        _isBufferView = false;
};

}  // namespace gfx
}  // namespace cc

#endif  // CC_CORE_GFX_BUFFER_H_
