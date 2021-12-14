#pragma once
#include "GraphicsCore/GBuffer.hpp"

FLYENGINE_GRAPHICS_BEGIN_NAMESPACE

class VulkanBuffer : public GBuffer
{
public:
    virtual void Initialize();
    virtual void Finalize();
};

FLYENGINE_END_NAMESPACE