#pragma once
#include "GraphicsCore/InputAssembler.hpp"

FLYENGINE_GRAPHICS_BEGIN_NAMESPACE

class InputAssemblerVk : public InputAssembler
{
public:
    virtual void Initialize();
    virtual void Finalize();
};

FLYENGINE_END_NAMESPACE