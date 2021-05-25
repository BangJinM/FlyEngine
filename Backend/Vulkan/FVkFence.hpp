#pragma once

#include "../Core/FlyFence.hpp"
namespace FlyEngine::Backend
{
class FVkFence : public FlyFence
{
public:
    FVkFence(FlyDevice *fVkDevice) : FlyFence(fVkDevice) {}
    ~FVkFence() {}
    
    virtual void Destroy() override;
    virtual void Initialize(const FenceInfo &info) override;
};

}  // namespace FlyEngine::Backend