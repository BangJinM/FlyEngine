#pragma once
#include "GraphicsCore/GInputAssembler.hpp"

FLYENGINE_GRAPHICS_BEGIN_NAMESPACE

class VulkanInputAssembler : public GInputAssembler
{
public:
    virtual void Initialize();
    virtual void Finalize();
};

FLYENGINE_END_NAMESPACE