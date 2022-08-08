#ifndef CC_CORE_GFX_QUEUE_H_
#define CC_CORE_GFX_QUEUE_H_

#include "GFXDef.h"

namespace cc
{
namespace gfx
{

class Queue : public GFXObject
{
public:
    Queue(Device *device);
    virtual ~Queue();

public:
    virtual bool initialize(const QueueInfo &info)                                      = 0;
    virtual void destroy()                                                              = 0;
    virtual void submit(const CommandBuffer *const *cmdBuffs, uint count, Fence *fence) = 0;

    inline void submit(const std::vector<CommandBuffer *> &cmdBuffs) { submit(cmdBuffs, nullptr); }
    inline void submit(const std::vector<CommandBuffer *> &cmdBuffs, Fence *fence)
    {
        submit(cmdBuffs.data(), static_cast<uint>(cmdBuffs.size()), fence);
    }
    inline Device   *getDevice() const { return _device; }
    inline QueueType getType() const { return _type; }
    inline bool      isAsync() const { return _isAsync; }

protected:
    Device   *_device  = nullptr;
    QueueType _type    = QueueType::GRAPHICS;
    bool      _isAsync = false;
};

}  // namespace gfx
}  // namespace cc

#endif  // CC_CORE_GFX_QUEUE_H_
