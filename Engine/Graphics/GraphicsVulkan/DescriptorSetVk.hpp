#pragma once
#include "GraphicsCore/DescriptorSet.hpp"

FLYENGINE_GRAPHICS_BEGIN_NAMESPACE

class DescriptorSetVk : public DescriptorSet
{
public:
    virtual void Initialize();
    virtual void Finalize();
};

FLYENGINE_END_NAMESPACE