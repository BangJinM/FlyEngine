#pragma once

#include "Node.hpp"

#include <set>

namespace FlyEngine::SCENE
{
class GameObject : public Node
{
public:
    GameObject(std::string name) : Node(std::move(name))
    {
        type = NodeType::TypeGameObject;
    }

    std::set<int> &GetGameObjects() { return gameObjects; }

protected:
    std::set<int> gameObjects;
};
} // namespace FlyEngine::SCENE