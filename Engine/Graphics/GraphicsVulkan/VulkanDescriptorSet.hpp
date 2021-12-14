#pragma once
#include "GraphicsCore/GDescriptorSet.hpp"

FLYENGINE_GRAPHICS_BEGIN_NAMESPACE

class VulkanDescriptorSet : public GDescriptorSet
{
public:
    virtual void Initialize();
    virtual void Finalize();
};

FLYENGINE_END_NAMESPACE