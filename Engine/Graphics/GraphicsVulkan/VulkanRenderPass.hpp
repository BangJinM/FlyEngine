#pragma once
#include "GraphicsCore/GRenderPass.hpp"

FLYENGINE_GRAPHICS_BEGIN_NAMESPACE

class VulkanRenderPass : public GRenderPass
{
public:
    virtual void Initialize();
    virtual void Finalize();
};

FLYENGINE_END_NAMESPACE