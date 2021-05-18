#include "GLFWApplication.hpp"

#include <iostream>
#include <vector>

void GLFWApplication::Run()
{
    init();
    mainLoop();
    clean();
}

void GLFWApplication::init()
{
    initWindow();
}

void GLFWApplication::clean()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

void GLFWApplication::initWindow()
{
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    window = glfwCreateWindow(800, 600, "FlyEngine", nullptr, nullptr);
}

void GLFWApplication::mainLoop()
{
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
    }
}
