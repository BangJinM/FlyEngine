#pragma once

#include <GLFW/glfw3.h>
#include <vector>

#include "Interface/IApplication.h"
#include "Interface/IRuntimeModule.h"

FLYENGINE_CORE_BEGIN_NAMESPACE

class GLFWApp : public IApplication
{
private:
    static void resizeCallback(GLFWwindow *wnd, int w, int h);
    static void keyCallback(GLFWwindow *wnd, int key, int, int state, int);
    static void mouseButtonCallback(GLFWwindow *wnd, int button, int state, int);
    static void cursorPosCallback(GLFWwindow *wnd, double xpos, double ypos);
    static void mouseWheelCallback(GLFWwindow *wnd, double dx, double dy);

public:
    virtual bool CreateWindow(const char *Title, int Width, int Height, int GlfwApiHint);
    virtual bool InitEngine(int DevType);

    virtual bool Initialize();
    virtual bool Finalize();
    virtual void Tick(float deltaTime);
    virtual bool IsQuit();

public:
    GLFWwindow *                  m_pWindow = nullptr;
    std::vector<IRuntimeModule *> m_runtimeModules;
};
FLYENGINE_END_NAMESPACE