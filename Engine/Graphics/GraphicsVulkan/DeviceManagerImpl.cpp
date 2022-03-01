#include "DeviceManagerImpl.hpp"

#include "VulkanFunc.hpp"

FLYENGINE_BEGIN_NAMESPACE

Shader *DeviceManagerImpl::CreateShader(ShaderInfo info)
{
    Shader *shader = new ShaderImpl(info);
    shader->Initialize();
    return shader;
}

bool DeviceManagerImpl::Initialize()
{
    return true;
}

bool DeviceManagerImpl::Initialize(NativeWindow window)
{
    this->Initialize();
    instanceImpl->Initialize();
    surfaceKHR->Initialize(window);
    device->Initialize();
    swapChainImpl->Initialize();
    return true;
}
bool DeviceManagerImpl::Finalize()
{
    swapChainImpl->Finalize();
    device->Finalize();
    surfaceKHR->Finalize();
    instanceImpl->Finalize();
    return true;
}

void DeviceManagerImpl::Tick(float deltaTime) {}

DeviceManagerImpl::DeviceManagerImpl()
{
    surfaceKHR    = new SurfaceKHR();
    instanceImpl  = new Instance();
    device        = new Device();
    swapChainImpl = new SwapChainImpl();
}
DeviceManagerImpl::~DeviceManagerImpl()
{
    delete instanceImpl;
    delete surfaceKHR;
    delete device;
    delete swapChainImpl;
}

FLYENGINE_END_NAMESPACE