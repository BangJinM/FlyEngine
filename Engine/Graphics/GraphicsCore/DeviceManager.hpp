#pragma once

#include "Engine.hpp"

FLYENGINE_BEGIN_NAMESPACE

class Shader;

class DeviceManager : public IRuntimeModule
{
public:
    virtual Shader *CreateShader(ShaderInfo info) = 0;
};

FLYENGINE_END_NAMESPACE