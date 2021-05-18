#pragma once

#include <map>
#include <string>
#include <vector>

#include "GameObject.hpp"

namespace FlyEngine::SCENE
{
    class Scene
    {
    public:
        std::string name;

        std::vector<GameObject> gameObjectNodes;
        std::map<std::string, int> gameObjectNodeTables;

        std::vector<GameObject> &GetGameObjects() { return gameObjectNodes; }

        int AddGameObject(std::string name);
        int AddGameObject(int index, std::string name);
    };

}