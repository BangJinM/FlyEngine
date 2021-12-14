#pragma once
#include "GraphicsCore/GCommandBuffer.hpp"

FLYENGINE_GRAPHICS_BEGIN_NAMESPACE

class VulkanCommandBuffer : public GCommandBuffer
{
public:
    virtual void Initialize();
    virtual void Finalize();
};

FLYENGINE_END_NAMESPACE