#pragma once

#include "IRuntimeModule.h"

FLYENGINE_BEGIN_NAMESPACE

class IGameLogic : public IRuntimeModule
{
public:
    virtual bool Initialize() = 0;

    virtual bool Finalize() = 0;

    virtual void Tick(float deltaTime) = 0;
};

FLYENGINE_END_NAMESPACE