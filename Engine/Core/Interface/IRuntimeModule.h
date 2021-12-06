#pragma once

#include "Common/BaseDefines.h"

FLYENGINE_CORE_BEGIN_NAMESPACE
class IRuntimeModule
{
public:
    virtual ~IRuntimeModule(){};

    virtual bool Initialize() = 0;

    virtual bool Finalize() = 0;

    virtual void Tick(float deltaTime) = 0;
};
FLYENGINE_END_NAMESPACE
