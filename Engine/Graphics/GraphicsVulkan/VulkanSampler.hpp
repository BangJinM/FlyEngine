#pragma once
#include "GraphicsCore/GSampler.hpp"

FLYENGINE_GRAPHICS_BEGIN_NAMESPACE

class VulkanSampler : public GSampler
{
public:
    virtual void Initialize();
    virtual void Finalize();
};

FLYENGINE_END_NAMESPACE