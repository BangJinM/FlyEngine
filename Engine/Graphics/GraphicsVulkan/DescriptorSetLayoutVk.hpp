#pragma once
#include "GraphicsCore/DescriptorSetLayout.hpp"

FLYENGINE_GRAPHICS_BEGIN_NAMESPACE

class DescriptorSetLayoutVk : public DescriptorSetLayout
{
public:
    virtual void Initialize();
    virtual void Finalize();
};

FLYENGINE_END_NAMESPACE