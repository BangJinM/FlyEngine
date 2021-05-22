#pragma once

#include "Node.hpp"
namespace FlyEngine::DAG
{
class ResourceNode : public Node
{
public:
    ResourceNode(std::string name) : Node(std::move(name))
    {
        type = NodeType::RESOURCE;
    }
};
} // namespace FlyEngine::DAG