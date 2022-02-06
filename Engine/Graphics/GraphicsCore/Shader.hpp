#pragma once

#include <string>
#include <vector>

#include "Base.hpp"

FLYENGINE_BEGIN_NAMESPACE

enum class ShaderStageFlagBit : uint32_t
{
    NONE       = 0x0,
    VERTEX     = 0x1,
    CONTROL    = 0x2,
    EVALUATION = 0x4,
    GEOMETRY   = 0x8,
    FRAGMENT   = 0x10,
    COMPUTE    = 0x20,
    ALL        = 0x3f,
};

struct ShaderStage
{
    ShaderStageFlagBit stage{ShaderStageFlagBit::NONE};
    std::vector<char>  source;
};

struct ShaderInfo
{
    std::string              name;
    std::vector<ShaderStage> stages;
};

class Shader : public Base
{
public:
    virtual void Initialize(ShaderInfo shaderInfo) = 0;
    virtual void Destroy()                         = 0;

protected:
    ShaderInfo shaderInfo;
};

FLYENGINE_END_NAMESPACE