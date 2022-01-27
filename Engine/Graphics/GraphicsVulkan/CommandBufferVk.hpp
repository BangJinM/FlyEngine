#pragma once
#include "GraphicsCore/CommandBuffer.hpp"

FLYENGINE_GRAPHICS_BEGIN_NAMESPACE

class CommandBufferVk : public CommandBuffer
{
public:
    virtual void Initialize();
    virtual void Finalize();
};

FLYENGINE_END_NAMESPACE