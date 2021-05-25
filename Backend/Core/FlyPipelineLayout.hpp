#pragma once

#include "FlyObject.hpp"

namespace FlyEngine::Backend
{
class FlyPipelineLayout : public FlyObject
{
public:
    FlyPipelineLayout(FlyDevice *flyDevice) : FlyObject(ObjectType::PIPELINE_LAYOUT, flyDevice) {}
    ~FlyPipelineLayout() {}

    virtual void Initialize(const PipelineLayoutInfo &info) = 0;
};

}  // namespace FlyEngine::Backend