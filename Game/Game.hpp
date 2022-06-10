#pragma once

#include "Common/BaseDefines.hpp"
#include "Common/IGameLogic.hpp"

using namespace fly;

namespace game
{

class Game : public IGameLogic
{
public:
    virtual bool Initialize();

    virtual bool Finalize();

    virtual void Tick(float deltaTime);
};

extern IGameLogic *g_pGameLogic;

}  // namespace game