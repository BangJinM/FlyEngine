#pragma once

#include "Common/BaseDefines.hpp"
#include "Common/IRuntimeModule.h"
#include "GraphicsCore/Shader.hpp"
#include "Platforms/NativeWindow.hpp"

FLYENGINE_BEGIN_NAMESPACE

class DeviceManager : public IRuntimeModule
{
public:
    virtual Shader *CreateShader(ShaderInfo info) = 0;
};

FLYENGINE_END_NAMESPACE