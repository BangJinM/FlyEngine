#pragma once

#include "../Core/FlyPipelineState.hpp"
#include "FVkDefine.hpp"

namespace FlyEngine::Backend
{
class FVkPipelineState : public FlyPipelineState
{
public:
    FVkPipelineState(FlyDevice *fVkDevice) : FlyPipelineState(fVkDevice) {}
    ~FVkPipelineState() {}

    virtual void Destroy() override;
    virtual void Initialize(const PipelineStateInfo &info) override;

private:
    VkPipeline graphicsPipeline;
};

}  // namespace FlyEngine::Backend