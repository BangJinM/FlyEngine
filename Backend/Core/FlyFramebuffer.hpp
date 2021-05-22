#pragma once

#include "FlyObject.hpp"

namespace FlyEngine::Backend
{
class FlyFramebuffer : public FlyObject
{
public:
    FlyFramebuffer() : FlyObject(ObjectType::FRAMEBUFFER) {}
    ~FlyFramebuffer() {}
};

} // namespace FlyEngine::Backend