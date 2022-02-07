#include "DeviceManagerImpl.hpp"

FLYENGINE_BEGIN_NAMESPACE

Shader *DeviceManagerImpl::CreateShader(ShaderInfo info)
{
    Shader *shader = new ShaderImpl();
    shader->Initialize(info);
    return shader;
}

bool DeviceManagerImpl::Initialize()
{
    return true;
}

bool DeviceManagerImpl::Finalize()
{
    return true;
}

void DeviceManagerImpl::Tick(float deltaTime) {}

FLYENGINE_END_NAMESPACE