#pragma once

#include "Engine.hpp"

FLYENGINE_BEGIN_NAMESPACE

class DeviceManagerImpl : public DeviceManager
{
public:
    Shader *CreateShader(ShaderInfo info)
    {
        auto shader = new ShaderImpl();
        shader->Initialize(info);
        return shader;
    }

    bool Initialize() { return true; }

    bool Finalize() { return true; }

    void Tick(float deltaTime) {}
};

FLYENGINE_END_NAMESPACE