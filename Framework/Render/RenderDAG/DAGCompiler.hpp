#pragma once
#include "DirectedAcyclicGraph.hpp"

#include <set>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <vector>

namespace FlyEngine::DAG
{
    class DAGCompiler
    {
        struct RsrcInfo
        {
            std::vector<size_t> readers;
            size_t writer{static_cast<size_t>(-1)};
        };

    private:
        std::tuple<bool, std::vector<size_t>> TopologicalSort(std::unordered_map<size_t, std::set<size_t>> toMap);

        std::tuple<bool, std::vector<size_t>> SortPass(DirectedAcyclicGraph &dag);

    public:
        void Compiler(DirectedAcyclicGraph &dag);
    };
}