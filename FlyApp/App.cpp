#include "App.hpp"
#include <stdexcept>
#include "AppInfo.hpp"
#include "Backend/Core/FlyDevice.hpp"
#include "Backend/DeviceFactory.hpp"
#include "File/File.hpp"
#include "Memory/MemoryManager.hpp"
#include "Window.hpp"
namespace FlyEngine
{
void App::Init()
{
    Memory::MemoryManager *memoryManager = Memory::MemoryManager::GetInstance();
    File::File             file;
    file.AddSearchPath("F:/projects/my/FlyEngine/Asset/");
    auto shader1 = file.SyncOpenAndReadBinary("Private/Shader/sampler.vert.spv");
    auto shader2 = file.SyncOpenAndReadBinary("Private/Shader/sampler.frag.spv");
    auto text1   = file.SyncOpenAndReadText("Private/Shader/sampler.vert");

    AppInfo appInfo(1024, 640, Backend::BackendFlag::Vulkan, "Vulkan");

    p_Window = new Window();
    p_Window->Init(appInfo);
    appInfo.windowHandle = p_Window->GetWindowHandle();
    if (!p_Window)
        throw std::runtime_error("Window Init failed!");
    p_FlyDevice = Backend::CreateDevice(appInfo.backend);

    p_FlyDevice->Initialize(appInfo);

    Backend::BufferInfo info;
    info.size   = 1000;
    info.usage  = Backend::BufferUsage::INDEX;
    auto buffer = p_FlyDevice->CreateBuffer(info);
    buffer->Destroy();

    Backend::ShaderInfo  shaderInfo;
    Backend::ShaderStage vertexStage;
    Backend::ShaderStage fragStage;

    char *c = reinterpret_cast<char *>(shader1.GetData());

    vertexStage.stage  = Backend::ShaderStageFlags::VERTEX;
    vertexStage.source = std::string(c, c + shader1.GetDataSize());

    c = reinterpret_cast<char *>(shader2.GetData());

    fragStage.stage  = Backend::ShaderStageFlags::FRAGMENT;
    fragStage.source = std::string(c, c + shader2.GetDataSize());

    shaderInfo.shaderStageList = {vertexStage, fragStage};

    auto shader = p_FlyDevice->CreateShader(shaderInfo);
    shader->Destroy();

    memoryManager->Destroy();
}

void App::mainLoop()
{
    if (!p_FlyDevice)
    {
        throw std::runtime_error("app Init failed!");
    }
    while (!p_Window->IsQuit())
    {
        p_Window->Tick();
    }
}

void App::Destroy()
{
    if (p_FlyDevice)
    {
        p_FlyDevice->Destroy();
        delete p_FlyDevice;
    }
    if (p_Window)
    {
        p_Window->Destroy();
        delete p_Window;
    }
}

void App::Run()
{
    mainLoop();
}

}  // namespace FlyEngine