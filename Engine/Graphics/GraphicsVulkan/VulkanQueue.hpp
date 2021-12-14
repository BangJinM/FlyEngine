#pragma once
#include "GraphicsCore/GQueue.hpp"

FLYENGINE_GRAPHICS_BEGIN_NAMESPACE

class VulkanQueue : public GQueue
{
public:
    virtual void Initialize();
    virtual void Finalize();
};

FLYENGINE_END_NAMESPACE