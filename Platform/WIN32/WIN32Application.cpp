#include "WIN32Application.hpp"

#include <iostream>
#include <vector>

void WIN32Application::Run()
{
    init();
    mainLoop();
    clean();
}

void WIN32Application::init()
{
    initWindow();
}

void WIN32Application::clean()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

void WIN32Application::initWindow()
{
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    window = glfwCreateWindow(800, 600, "FlyEngine", nullptr, nullptr);
}

void WIN32Application::mainLoop()
{
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
    }
}
