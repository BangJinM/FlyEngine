#pragma once

#include "FlyObject.hpp"

namespace FlyEngine::Backend
{
class FlyPipelineLayout : public FlyObject
{
public:
    FlyPipelineLayout() : FlyObject(ObjectType::PIPELINE_LAYOUT) {}
    ~FlyPipelineLayout() {}
};

} // namespace FlyEngine::Backend