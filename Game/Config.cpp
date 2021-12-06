
#pragma once

#include "Common/BaseDefines.h"
#include "Game.hpp"
#include "Interface/IGameLogic.hpp"

FLYENGINE_CORE_BEGIN_NAMESPACE

USING_FLYENGINE_NAMESPACE(FlyGame)

IGameLogic *g_pGameLogic = static_cast<IGameLogic *>(new Game);

FLYENGINE_END_NAMESPACE