#pragma once

#include "Interface/IRuntimeModule.h"

FLYENGINE_CORE_BEGIN_NAMESPACE

class IGameLogic : public IRuntimeModule
{
public:
    virtual bool Initialize() = 0;

    virtual bool Finalize() = 0;

    virtual void Tick(float deltaTime) = 0;
};

extern IGameLogic *g_pGameLogic;

FLYENGINE_END_NAMESPACE