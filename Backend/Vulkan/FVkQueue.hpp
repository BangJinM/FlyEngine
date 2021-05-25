#pragma once

#include "../Core/FlyQueue.hpp"

namespace FlyEngine::Backend
{
class FVkQueue : public FlyQueue
{
public:
    FVkQueue(FlyDevice *fVkDevice) : FlyQueue(fVkDevice) {}
    ~FVkQueue() {}
    
    virtual void Destroy() override;
    virtual void Initialize(const QueueInfo &info) override;
};

} // namespace FlyEngine::Backend