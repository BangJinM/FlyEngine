#pragma once
#include "GraphicsCore/Sampler.hpp"

FLYENGINE_GRAPHICS_BEGIN_NAMESPACE

class SamplerVk : public Sampler
{
public:
    virtual void Initialize();
    virtual void Finalize();
};

FLYENGINE_END_NAMESPACE