#pragma once
#include <string>
#include <unordered_map>
#include <vector>

#include <Common/BaseDefines.hpp>
#include <Scene/Component.hpp>

namespace fly
{

class GameObject
{
public:
    std::unordered_map<std::string, std::vector<Component *>> componentTypeComponetMap;

public:
    GameObject();
    ~GameObject();

    Component *AddComponent(std::string componentTypeName);
    Component *GetComponent(std::string componentTypeName);
};

};  // namespace fly