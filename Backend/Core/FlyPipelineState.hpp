#pragma once

#include "FlyObject.hpp"

namespace FlyEngine::Backend
{
class FlyPipelineState : public FlyObject
{
public:
    FlyPipelineState(FlyDevice *flyDevice) : FlyObject(ObjectType::PIPELINE_STATE, flyDevice) {}
    ~FlyPipelineState() {}

    virtual void Initialize(const PipelineStateInfo &info) = 0;
};

}  // namespace FlyEngine::Backend