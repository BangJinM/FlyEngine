#pragma once

#include <string>
#include "Backend/BackendEnum.hpp"
namespace FlyEngine
{
class WindowBase;
struct AppInfo
{
    WindowBase *         windowHandle = 0;
    std::string          name;
    int                  width        = 0;
    int                  height       = 0;
    int                  nativeWidth  = 0;
    int                  nativeHeight = 0;
    Backend::BackendFlag backend      = Backend::BackendFlag::Vulkan;

    AppInfo() {}

    AppInfo(int w, int h, Backend::BackendFlag b, std::string n) : width(w), height(h), backend(b), name(n) {}
};
}  // namespace FlyEngine