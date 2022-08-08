#pragma once

#include "DirectedAcyclicGraph.hpp"

namespace fly::dag
{
int DirectedAcyclicGraph::AddResourceNode(std::string name)
{
    if (resourceTableNodes.find(name) != resourceTableNodes.end())
    {
        return -1;
    }
    int          index = resourceNodes.size();
    ResourceNode node  = ResourceNode(name);
    resourceNodes.push_back(node);
    resourceTableNodes.insert(std::pair<std::string, int>(name, index));
    return index;
}

int DirectedAcyclicGraph::AddPassNode(std::string name, std::vector<int> inputs, std::vector<int> outputs)
{
    if (passTableNodes.find(name) != passTableNodes.end())
    {
        return -1;
    }
    int      index = passNodes.size();
    PassNode node  = PassNode(name, inputs, outputs);
    passNodes.push_back(node);
    passTableNodes.insert(std::pair<std::string, int>(name, index));
    return index;
}

}  // namespace fly::dag