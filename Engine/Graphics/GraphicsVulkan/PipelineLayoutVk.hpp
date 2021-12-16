#pragma once
#include "GraphicsCore/PipelineLayout.hpp"

FLYENGINE_GRAPHICS_BEGIN_NAMESPACE

class PipelineLayoutVk : public PipelineLayout
{
public:
    virtual void Initialize();
    virtual void Finalize();
};

FLYENGINE_END_NAMESPACE