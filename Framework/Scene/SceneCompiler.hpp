#pragma once
#include "Scene.hpp"

#include <set>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <vector>

namespace FlyEngine::SCENE
{
class SceneCompiler
{
    struct RsrcInfo
    {
        std::vector<size_t> readers;
        size_t              writer{static_cast<size_t>(-1)};
    };

private:
    std::tuple<bool, std::vector<size_t>> TopologicalSort(std::unordered_map<size_t, std::set<size_t>> toMap);

    std::tuple<bool, std::vector<size_t>> SortScene(Scene &dag);

public:
    void Compiler(Scene &dag);
};
}  // namespace FlyEngine::SCENE