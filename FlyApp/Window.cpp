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

void Window::CreateSurface(void *graphicsInstance, void *surfData)
{
    if (glfwCreateWindowSurface((VkInstance)graphicsInstance, p_window, nullptr, (VkSurfaceKHR *)surfData) != VK_SUCCESS)
    {}
}

void Window::GetFrameSize(int &width, int &height)
{
    glfwGetFramebufferSize((GLFWwindow *)p_window, &width, &height);
}

void Window::WaitForNewWindowSize()
{
    int width = 0, height = 0;
    while (width == 0 || height == 0)
    {
        glfwGetFramebufferSize(p_window, &width, &height);
        glfwWaitEvents();
    }
}

bool Window::Init(AppInfo info)
{
    _info = info;
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