#pragma once
#include "GraphicsCore/GPipelineLayout.hpp"

FLYENGINE_GRAPHICS_BEGIN_NAMESPACE

class VulkanPipelineLayout : public GPipelineLayout
{
public:
    virtual void Initialize();
    virtual void Finalize();
};

FLYENGINE_END_NAMESPACE