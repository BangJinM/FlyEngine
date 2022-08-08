#pragma once

#include <map>
#include <string>
#include <vector>

#include "PassNode.hpp"
#include "ResourceNode.hpp"

namespace fly::dag
{
struct DirectedAcyclicGraph
{
    std::string name;

    //资源以及资源名字对应的位置
    std::vector<ResourceNode>  resourceNodes;
    std::map<std::string, int> resourceTableNodes;
    // Pass和Pass名字对应的位置
    std::vector<PassNode>      passNodes;
    std::map<std::string, int> passTableNodes;

    int AddResourceNode(std::string name);

    int AddPassNode(std::string name, std::vector<int> inputs, std::vector<int> outputs);
};

}  // namespace fly::dag