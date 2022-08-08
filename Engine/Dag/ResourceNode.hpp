#pragma once

#include "Node.hpp"
namespace fly::dag
{
class ResourceNode : public Node
{
public:
    ResourceNode(std::string name) : Node(std::move(name)) { type = NodeType::RESOURCE; }
};
}  // namespace fly::dag