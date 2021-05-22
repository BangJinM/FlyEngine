#include "SceneCompiler.hpp"

#include "Scene.hpp"

namespace FlyEngine::SCENE
{
std::tuple<bool, std::vector<size_t>> SceneCompiler::TopologicalSort(std::unordered_map<size_t, std::set<size_t>> toMap)
{
    std::unordered_map<size_t, size_t> needCountList;
    // 构建needCountList
    // key位置ID,value 数量
    for (const auto &[parent, children] : toMap)
        needCountList.emplace(parent, 0);
    for (const auto &[parent, children] : toMap) {
        for (const auto &child : children)
            needCountList[child] += 1;
    }

    std::stack<size_t>  zeroStack;
    std::vector<size_t> sortedList;
    // 将被引用次数为0的压栈
    for (const auto &[v, count] : needCountList) {
        if (count == 0)
            zeroStack.push(v);
    }
    // 排序
    while (!zeroStack.empty()) {
        auto v = zeroStack.top();
        zeroStack.pop();
        sortedList.push_back(v);
        needCountList.erase(v);
        if (toMap.find(v) != toMap.end()) {
            for (auto child : toMap.find(v)->second) {
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

std::tuple<bool, std::vector<size_t>> SceneCompiler::SortScene(Scene &dag)
{
    std::unordered_map<size_t, std::set<size_t>> toMap;

    auto &gameNodeTable = dag.GetGameObjects();

    // 构建toMap
    // key为当前位置ID,values为引用当前位置的ID
    for (size_t index = 0; index < gameNodeTable.size(); index++) {
        std::set<int> &nodes = gameNodeTable[index].GetGameObjects();
        for (auto key : nodes) {
            auto &adj = toMap[key];
            adj.insert(index);
        }
    }

    return TopologicalSort(toMap);
}

void SceneCompiler::Compiler(Scene &dag)
{
    auto [success, sortedPasses] = SortScene(dag);
}
} // namespace FlyEngine::SCENE