#pragma once
#include "GraphicsCore/GFence.hpp"

FLYENGINE_GRAPHICS_BEGIN_NAMESPACE

class VulkanFence : public GFence
{
public:
    virtual void Initialize();
    virtual void Finalize();
};

FLYENGINE_END_NAMESPACE