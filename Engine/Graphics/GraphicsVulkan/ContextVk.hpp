#pragma once
#include "GraphicsCore/Context.hpp"

FLYENGINE_GRAPHICS_BEGIN_NAMESPACE

class ContextVk : public Context
{
public:
    virtual void Initialize();
    virtual void Finalize();
};

FLYENGINE_END_NAMESPACE