#include "Window.hpp"

namespace FlyEngine
{
Window *Window::CreateWindow(AppInfo info)
{
    Window *window = new Window();
    if (window->Init(info))
        return window;
    window->Destroy();
    delete window;
    return nullptr;
}

bool Window::Init(AppInfo info)
{
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    p_window = glfwCreateWindow(info.width, info.height, info.name.c_str(), nullptr, nullptr);
    return true;
}

bool Window::IsQuit()
{
    return glfwWindowShouldClose(p_window);
}

void Window::Tick()
{
    glfwPollEvents();
}

void Window::Destroy()
{
    if (p_window)
    {
        glfwDestroyWindow(p_window);

        glfwTerminate();
    }
}

}  // namespace FlyEngine