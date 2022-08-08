#include "GLFWApp.hpp"

#include "Common/IApplication.hpp"
#include "Common/IGameLogic.hpp"
#include "Common/IRuntimeModule.hpp"

// #include "GraphicsVulkan/VulkanFactory.hpp"
#include "Graphics/GFXDeviceManager.h"
#include "Graphics/core/CoreStd.h"
#include "Platforms/NativeWindow.hpp"

#define GLFW_EXPOSE_NATIVE_WIN32
#include "GLFW/glfw3native.h"

FLYENGINE_BEGIN_NAMESPACE

extern IApplication *g_pApplication;
extern IGameLogic   *g_pGameLogic;
// extern IRuntimeModule *g_pMemoryManager;

void GLFWApp::resizeCallback(GLFWwindow *wnd, int w, int h)
{
    auto *pSelf = static_cast<GLFWApp *>(glfwGetWindowUserPointer(wnd));
    // if (pSelf->m_pSwapChain != nullptr)
    //     pSelf->m_pSwapChain->Resize(static_cast<Uint32>(w), static_cast<Uint32>(h));
}
void GLFWApp::keyCallback(GLFWwindow *wnd, int key, int, int state, int)
{
    auto *pSelf = static_cast<GLFWApp *>(glfwGetWindowUserPointer(wnd));
    // pSelf->OnKeyEvent(static_cast<Key>(key), static_cast<KeyState>(state));
}
void GLFWApp::mouseButtonCallback(GLFWwindow *wnd, int button, int state, int)
{
    auto *pSelf = static_cast<GLFWApp *>(glfwGetWindowUserPointer(wnd));
    // pSelf->OnKeyEvent(static_cast<Key>(button), static_cast<KeyState>(state));
}
void GLFWApp::cursorPosCallback(GLFWwindow *wnd, double xpos, double ypos)
{
    float xscale = 1;
    float yscale = 1;
    glfwGetWindowContentScale(wnd, &xscale, &yscale);
    auto *pSelf = static_cast<GLFWApp *>(glfwGetWindowUserPointer(wnd));
    // pSelf->MouseEvent(float2(static_cast<float>(xpos * xscale), static_cast<float>(ypos * yscale)));
}
void GLFWApp::mouseWheelCallback(GLFWwindow *wnd, double dx, double dy) {}

bool GLFWApp::CreateEngineWindow(const char *Title, int Width, int Height, int GlfwApiHint)
{
    if (glfwInit() != GLFW_TRUE)
        return false;

    glfwWindowHint(GLFW_CLIENT_API, GlfwApiHint);
    if (GlfwApiHint == GLFW_OPENGL_API)
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    }

    m_pWindow = glfwCreateWindow(Width, Height, Title, nullptr, nullptr);
    if (m_pWindow == nullptr)
    {
        // LOG_ERROR_MESSAGE("Failed to create GLFW window");
        return false;
    }

    glfwSetWindowUserPointer(m_pWindow, this);
    glfwSetFramebufferSizeCallback(m_pWindow, &resizeCallback);
    glfwSetKeyCallback(m_pWindow, &keyCallback);
    glfwSetMouseButtonCallback(m_pWindow, &mouseButtonCallback);
    glfwSetCursorPosCallback(m_pWindow, &cursorPosCallback);
    glfwSetScrollCallback(m_pWindow, &mouseWheelCallback);

    // glfwSetWindowSizeLimits(m_pWindow, 320, 240, GLFW_DONT_CARE, GLFW_DONT_CARE);
    return true;
}

bool GLFWApp::InitEngine(int DevType)
{
    return 1;
}

bool GLFWApp::Initialize()
{
    m_runtimeModules = {g_pGameLogic};
    for (auto module : m_runtimeModules)
    {
        bool flag = true;
        if (module)
            flag = module->Initialize();
        if (!flag)
            return false;
    }

    int pixelWidth  = 1124;
    int pixelHeight = 640;

    cc::gfx::DeviceInfo info;
    info.windowHandle = glfwGetWin32Window(m_pWindow);
    info.width        = pixelWidth;
    info.height       = pixelHeight;

    m_pDevice = cc::gfx::DeviceManager::create(info);
    // // Init Native Window
    // platform::NativeWindow nativeWindow(glfwGetWin32Window(m_pWindow));

    // // Init Graphics Engine
    // m_pGraphicsFactory = new Graphics::VulkanFactory(nativeWindow);
    // m_pGraphicsFactory->Initialize();

    return true;
}

bool GLFWApp::Finalize()
{
    for (auto module : m_runtimeModules)
        if (module)
            module->Finalize();

    // if (m_pGraphicsFactory) m_pGraphicsFactory->Finalize();

    if (m_pWindow)
    {
        glfwDestroyWindow(m_pWindow);
        glfwTerminate();
    }
    return true;
}

void GLFWApp::Tick(float deltaTime)
{
    glfwPollEvents();
    int w, h;
    glfwGetWindowSize(m_pWindow, &w, &h);
    if (w > 0 && h > 0)
    {
        // m_pGraphicsFactory->prepareFrame();
        // m_pGraphicsFactory->beginCommand();
        for (auto module : m_runtimeModules)
            if (module)
                module->Tick(deltaTime);
        // m_pGraphicsFactory->Tick(deltaTime);
        // m_pGraphicsFactory->endCommand();
        // m_pGraphicsFactory->submitFrame();
    }
}

bool GLFWApp::IsQuit()
{
    return glfwWindowShouldClose(m_pWindow);
}

FLYENGINE_END_NAMESPACE