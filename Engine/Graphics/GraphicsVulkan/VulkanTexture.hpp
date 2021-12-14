#pragma once
#include "GraphicsCore/GTexture.hpp"

FLYENGINE_GRAPHICS_BEGIN_NAMESPACE

class VulkanTexture : public GTexture
{
public:
    virtual void Initialize();
    virtual void Finalize();
};

FLYENGINE_END_NAMESPACE