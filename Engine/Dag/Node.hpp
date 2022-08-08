#pragma once

#include "Define.hpp"

#include <string>
namespace fly::dag
{
class Node
{
public:
    Node(std::string name) : name{std::move(name)} {}

    const std::string &Name() const noexcept { return name; }

protected:
    std::string name;
    NodeType    type = NodeType::UNDEFINE;
};
}  // namespace fly::dag