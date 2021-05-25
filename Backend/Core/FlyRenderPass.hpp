#pragma once

#include "FlyObject.hpp"

namespace FlyEngine::Backend
{
class FlyRenderPass : public FlyObject
{
public:
    FlyRenderPass(FlyDevice *flyDevice) : FlyObject(ObjectType::RENDER_PASS, flyDevice) {}
    ~FlyRenderPass() {}

    virtual void Initialize(const RenderPassInfo &info) = 0;
};

}  // namespace FlyEngine::Backend