#include "Game.hpp"

#include <iostream>

namespace game
{
bool Game::Initialize() { return true; }

bool Game::Finalize() { return true; }

void Game::Tick(float deltaTime) {}
}  // namespace game