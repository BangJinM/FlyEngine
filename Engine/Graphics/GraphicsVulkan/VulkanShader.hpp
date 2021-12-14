#pragma once
#include "GraphicsCore/GShader.hpp"

FLYENGINE_GRAPHICS_BEGIN_NAMESPACE

class VulkanShader : public GShader
{
public:
    virtual void Initialize();
    virtual void Finalize();
};

FLYENGINE_END_NAMESPACE