#pragma once

#include "Scene.hpp"

namespace FlyEngine::SCENE
{
int Scene::AddGameObject(std::string name)
{
    if (gameObjectNodeTables.find(name) != gameObjectNodeTables.end())
    {
        return -1;
    }
    int        index = gameObjectNodes.size();
    GameObject node  = GameObject(name);
    gameObjectNodes.push_back(node);
    gameObjectNodeTables.insert(std::pair<std::string, int>(name, index));
    return index;
}

int Scene::AddGameObject(int index, std::string name)
{
    if (index < 0)
        return -1;
    if (gameObjectNodeTables.find(name) != gameObjectNodeTables.end())
    {
        return -1;
    }
    if (gameObjectNodes.size() <= index)
        return -1;

    int childIndex = gameObjectNodes.size();
    gameObjectNodeTables.insert(std::pair<std::string, int>(name, childIndex));

    GameObject node = GameObject(name);
    gameObjectNodes.push_back(node);

    GameObject &parent = gameObjectNodes[index];
    parent.GetGameObjects().insert(childIndex);
    return childIndex;
}
}  // namespace FlyEngine::SCENE