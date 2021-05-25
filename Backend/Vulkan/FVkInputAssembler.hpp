#pragma once

#include "../Core/FlyInputAssembler.hpp"

namespace FlyEngine::Backend
{
class FVkInputAssembler : public FlyInputAssembler
{
public:
    FVkInputAssembler(FlyDevice *fVkDevice) : FlyInputAssembler(fVkDevice) {}
    ~FVkInputAssembler() {}
    
    virtual void Destroy() override;
    virtual void Initialize(const InputAssemblerInfo &info) override;
};

}  // namespace FlyEngine::Backend