#pragma once

#include "../Core/FlyPipelineLayout.hpp"
#include "FVkDefine.hpp"
namespace FlyEngine::Backend
{
class FVkPipelineLayout : public FlyPipelineLayout
{
public:
    FVkPipelineLayout(FlyDevice *fVkDevice) : FlyPipelineLayout(fVkDevice) {}
    ~FVkPipelineLayout() {}

    virtual void Destroy() override;
    virtual void Initialize(const PipelineLayoutInfo &info) override;

public:
    VkPipelineLayout &GetVkPipelineLayout() { return pipelineLayout; }

private:
    VkPipelineLayout pipelineLayout;
};

}  // namespace FlyEngine::Backend