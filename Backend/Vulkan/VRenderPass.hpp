#pragma once

#include "FlyObject.hpp"

namespace FlyEngine::Backend
{
class FlyRenderPass : public FlyObject
{
public:
    FlyRenderPass() : FlyObject(ObjectType::RENDER_PASS) {}
    ~FlyRenderPass() {}
};

} // namespace FlyEngine::Backend