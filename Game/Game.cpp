#include "Game.hpp"

#include <iostream>

FLYENGINE_BEGIN_NAMESPACE(FlyGame)

bool Game::Initialize()
{
    return true;
}

bool Game::Finalize()
{
    return true;
}

void Game::Tick(float deltaTime)
{
}

FLYENGINE_END_NAMESPACE