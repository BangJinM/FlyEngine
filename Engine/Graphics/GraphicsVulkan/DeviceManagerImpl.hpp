#pragma once

#include "GraphicsCore/DeviceManager.hpp"

#include "GraphicsVulkan/ShaderImpl.hpp"

FLYENGINE_BEGIN_NAMESPACE

class DeviceManagerImpl : public DeviceManager
{
public:
    virtual Shader *CreateShader(ShaderInfo info);

    virtual bool Initialize();

    virtual bool Finalize();

    virtual void Tick(float deltaTime);
};

FLYENGINE_END_NAMESPACE