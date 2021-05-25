#pragma once

namespace FlyEngine::Backend
{
enum class BackendFlag : unsigned short int
{
    Default = 0,
    Vulkan  = 1
};

enum class PlatformFlag : unsigned short int
{
    Default = 0,
    Windows = 1
};
}  // namespace FlyEngine::Backend