#pragma once
#include "GraphicsCore/GContext.hpp"

FLYENGINE_GRAPHICS_BEGIN_NAMESPACE

class VulkanContext : public GContext
{
public:
    virtual void Initialize();
    virtual void Finalize();
};

FLYENGINE_END_NAMESPACE