#pragma once
#include "GraphicsCore/Framebuffer.hpp"

FLYENGINE_GRAPHICS_BEGIN_NAMESPACE

class FramebufferVk : public Framebuffer
{
public:
    virtual void Initialize();
    virtual void Finalize();
};

FLYENGINE_END_NAMESPACE