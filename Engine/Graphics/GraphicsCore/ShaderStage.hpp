#pragma once
#include "GraphicsDefine.hpp"

#include "Base.hpp"

FLYENGINE_GRAPHICS_BEGIN_NAMESPACE

class ShaderStage : public Base
{
public:
    ShaderStage(ShaderStageInfo shaderInfo) : m_shaderInfo(shaderInfo) {}

protected:
    ShaderStageInfo m_shaderInfo;
};

FLYENGINE_END_NAMESPACE