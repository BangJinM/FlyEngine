#include "DAGCompiler.hpp"

namespace fly::dag
{
std::tuple<bool, std::vector<size_t>> DAGCompiler::TopologicalSort(std::unordered_map<size_t, std::set<size_t>> toMap)
{
    std::unordered_map<size_t, size_t> needCountList;
    // 构建needCountList
    // key位置ID,value 数量
    for (const auto &[parent, children] : toMap)
        needCountList.emplace(parent, 0);
    for (const auto &[parent, children] : toMap)
    {
        for (const auto &child : children)
            needCountList[child] += 1;
    }

    std::stack<size_t>  zeroStack;
    std::vector<size_t> sortedList;
    // 将被引用次数为0的压栈
    for (const auto &[v, count] : needCountList)
    {
        if (count == 0)
            zeroStack.push(v);
    }
    // 排序
    while (!zeroStack.empty())
    {
        auto v = zeroStack.top();
        zeroStack.pop();
        sortedList.push_back(v);
        needCountList.erase(v);
        if (toMap.find(v) != toMap.end())
        {
            for (auto child : toMap.find(v)->second)
            {
                auto target = needCountList.find(child);
                if (target == needCountList.end())
                    continue;
                target->second--;
                if (target->second == 0)
                    zeroStack.push(child);
            }
        }
    }

    if (!needCountList.empty())
        return {false, std::vector<size_t>{}};

    return {true, sortedList};
}

std::tuple<bool, std::vector<size_t>> DAGCompiler::SortPass(DirectedAcyclicGraph &dag)
{
    std::unordered_map<size_t, std::set<size_t>> toMap;

    const auto &passes   = dag.passNodes;
    const auto &resoures = dag.resourceNodes;

    std::vector<size_t>                pr;
    std::unordered_map<size_t, size_t> prIndex2P;
    std::unordered_map<size_t, size_t> prIndex2R;

    // 将resource塞入list
    // 映射原始位置->新list位置
    for (size_t index = 0; index < resoures.size(); index++)
    {
        size_t cur = pr.size();
        pr.push_back(index);
        prIndex2R[index] = cur;
    }
    // 将pass塞入list
    // 映射原始位置->新list位置
    for (size_t index = 0; index < passes.size(); index++)
    {
        size_t cur = pr.size();
        pr.push_back(index);
        prIndex2P[index] = cur;
    }

    // 构建toMap
    // key为当前位置ID,values为引用当前位置的ID
    for (size_t i = 0; i < passes.size(); i++)
    {
        const auto &pass      = passes[i];
        size_t      passIndex = prIndex2P[i];

        const auto &inputs = pass.Inputs();
        for (const auto &input : inputs)
        {
            size_t inputIndex = prIndex2R[input];
            auto  &adj        = toMap[inputIndex];
            adj.insert(passIndex);
        }
        auto &adj = toMap[passIndex];
        for (const auto &output : pass.Outputs())
        {
            size_t outputIndex = prIndex2R[output];
            adj.insert(outputIndex);
        }
    }

    return TopologicalSort(toMap);
}

void DAGCompiler::Compiler(DirectedAcyclicGraph &dag)
{
    auto [success, sortedPasses] = SortPass(dag);
}
}  // namespace fly::dag