
#pragma once

#include "Common/BaseDefines.hpp"
#include "Common/IGameLogic.hpp"
#include "Game.hpp"

FLYENGINE_BEGIN_NAMESPACE

IGameLogic *g_pGameLogic = static_cast<IGameLogic *>(new game::Game);

FLYENGINE_END_NAMESPACE