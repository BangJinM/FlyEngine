#pragma once
#include "GraphicsCore/GDescriptorSetLayout.hpp"

FLYENGINE_GRAPHICS_BEGIN_NAMESPACE

class VulkanDescriptorSetLayout : public GDescriptorSetLayout
{
public:
    virtual void Initialize();
    virtual void Finalize();
};

FLYENGINE_END_NAMESPACE