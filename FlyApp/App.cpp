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
    File::IFile *          file          = File::File::GetFileInstance();

    file->AddSearchPath("F:/projects/my/FlyEngine/Asset/");
    auto shader1 = file->SyncOpenAndReadBinary("Private/Shader/sampler.vert.spv");
    auto shader2 = file->SyncOpenAndReadBinary("Private/Shader/sampler.frag.spv");
    auto text1   = file->SyncOpenAndReadText("Private/Shader/sampler.vert");

    AppInfo appInfo(1024, 640, Backend::BackendFlag::Vulkan, "Vulkan");

    p_Window = new Window();
    p_Window->Init(appInfo);
    appInfo.windowHandle = p_Window;
    if (!p_Window)
        throw std::runtime_error("Window Init failed!");
    p_FlyDevice = Backend::CreateDevice(appInfo.backend);

    p_FlyDevice->Initialize(p_Window);

    std::string         str = "11111111111111111111111111";
    Backend::BufferInfo info;
    info.size  = str.size();
    info.usage = Backend::BufferUsage::TRANSFER_DST | Backend::BufferUsage::UNIFORM;

    Backend::BufferInfo stageInfo;
    stageInfo.size            = str.size();
    stageInfo.usage           = Backend::BufferUsage::TRANSFER_SRC;
    stageInfo.isStagingBuffer = true;

    auto stageBuffer = p_FlyDevice->CreateBuffer(stageInfo);
    stageBuffer->CopyBuffer(str.data(), str.size());

    auto buffer = p_FlyDevice->CreateBuffer(info);
    buffer->CopyBuffer(stageBuffer);
    stageBuffer->Destroy();
    buffer->Destroy();

    Backend::ShaderInfo  shaderInfo;
    Backend::ShaderStage vertexStage;
    Backend::ShaderStage fragStage;

    char *c = reinterpret_cast<char *>(shader1.GetData());

    vertexStage.stage  = Backend::ShaderStageFlagBit::VERTEX;
    vertexStage.source = std::string(c, c + shader1.GetDataSize());

    c = reinterpret_cast<char *>(shader2.GetData());

    fragStage.stage  = Backend::ShaderStageFlagBit::FRAGMENT;
    fragStage.source = std::string(c, c + shader2.GetDataSize());

    shaderInfo.shaderStageList = {vertexStage, fragStage};

    auto shader = p_FlyDevice->CreateShader(shaderInfo);
    shader->Destroy();
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
        p_FlyDevice->BeginDraw();
        p_FlyDevice->Draw();
        p_FlyDevice->EndDraw();

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
    Memory::MemoryManager::GetInstance()->Destroy();
}

void App::Run()
{
    mainLoop();
}

}  // namespace FlyEngine