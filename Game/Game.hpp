#pragma once

#include "Common/BaseDefines.hpp"
#include "Interface/IGameLogic.hpp"

FLYENGINE_BEGIN_NAMESPACE(FlyGame)

USING_FLYENGINE_NAMESPACE(Core)

class Game : public IGameLogic
{
public:
    virtual bool Initialize();

    virtual bool Finalize();

    virtual void Tick(float deltaTime);
};

extern IGameLogic *g_pGameLogic;

FLYENGINE_END_NAMESPACE