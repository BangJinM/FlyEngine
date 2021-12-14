#pragma once
#include "GraphicsDefine.hpp"

FLYENGINE_GRAPHICS_BEGIN_NAMESPACE

class GBase
{
public:
    virtual void Initialize() = 0;
    virtual void Finalize()   = 0;
};

FLYENGINE_END_NAMESPACE