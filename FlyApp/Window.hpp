#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "WindowBase.hpp"

namespace FlyEngine
{
class Window : public WindowBase
{
private:
    GLFWwindow *p_window;

public:
    static Window *CreateWindow(AppInfo info);
    virtual void   CreateSurface(void *graphicsInstance, void *surfData) override;
    virtual void   GetFrameSize(int &width, int &height) override;
    virtual void   WaitForNewWindowSize() override;

public:
    virtual bool Init(AppInfo info) override;
    virtual bool IsQuit() override;
    virtual void Tick() override;
    virtual void Destroy() override;
};
}  // namespace FlyEngine