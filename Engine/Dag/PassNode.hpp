#pragma once

#include "Node.hpp"

#include <vector>
namespace fly::dag
{
class PassNode : public Node
{
public:
    PassNode(std::string name, std::vector<int> inputs, std::vector<int> outputs)
        : Node(std::move(name)), inputs{std::move(inputs)}, outputs{std::move(outputs)}
    {
        type = NodeType::PASS;
    }

    const std::vector<int> &Inputs() const noexcept { return inputs; }
    const std::vector<int> &Outputs() const noexcept { return outputs; }

protected:
    std::vector<int> inputs;
    std::vector<int> outputs;
};
}  // namespace fly::dag