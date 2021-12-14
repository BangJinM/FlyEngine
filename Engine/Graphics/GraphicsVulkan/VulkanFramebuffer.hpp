#pragma once
#include "GraphicsCore/GFramebuffer.hpp"

FLYENGINE_GRAPHICS_BEGIN_NAMESPACE

class VulkanFramebuffer : public GFramebuffer
{
public:
    virtual void Initialize();
    virtual void Finalize();
};

FLYENGINE_END_NAMESPACE