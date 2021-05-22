#include "App.hpp"
#include "AppInfo.hpp"
#include "Backend/Core/FlyDevice.hpp"
#include "Backend/DeviceFactory.hpp"
#include "Window.hpp"
#include <stdexcept>

namespace FlyEngine
{
void App::Init()
{
    AppInfo appInfo(1024, 640, Backend::BackendFlag::Vulkan, "Vulkan");

    p_Window = new Window();
    p_Window->Init(appInfo);
    appInfo.windowHandle = p_Window->GetWindowHandle();
    if (!p_Window)
        throw std::runtime_error("Window Init failed!");
    p_FlyDevice = Backend::CreateDevice(appInfo.backend);

    p_FlyDevice->Initialize(appInfo);
}

void App::mainLoop()
{
    if (!p_FlyDevice) {
        throw std::runtime_error("app Init failed!");
    }
    while (!p_Window->IsQuit()) {
        p_Window->Tick();
    }
}

void App::Destroy()
{
    if (p_FlyDevice) {
        p_FlyDevice->Destroy();
        delete p_FlyDevice;
    }
    if (p_Window) {
        p_Window->Destroy();
        delete p_Window;
    }
}

void App::Run()
{
    mainLoop();
}

} // namespace FlyEngine