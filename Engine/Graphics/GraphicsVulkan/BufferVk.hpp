#pragma once
#include "GraphicsCore/Buffer.hpp"

FLYENGINE_GRAPHICS_BEGIN_NAMESPACE

class BufferVk : public Buffer
{
public:
    virtual void Initialize();
    virtual void Finalize();
};

FLYENGINE_END_NAMESPACE