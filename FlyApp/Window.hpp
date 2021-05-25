#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "App.hpp"
#include "AppInfo.hpp"

namespace FlyEngine
{
class Window
{
private:
    GLFWwindow *p_window;

public:
    static Window *CreateWindow(AppInfo info);
    void *         GetWindowHandle() { return p_window; }

public:
    bool Init(AppInfo info);
    bool IsQuit();
    void Tick();
    void Destroy();
};
}  // namespace FlyEngine