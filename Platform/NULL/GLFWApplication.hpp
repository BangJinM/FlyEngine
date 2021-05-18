#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>

class GLFWApplication
{
public:
    void Run();

private:
    void init();
    void initWindow();
    void mainLoop();
    void clean();

    GLFWwindow *window;
};
