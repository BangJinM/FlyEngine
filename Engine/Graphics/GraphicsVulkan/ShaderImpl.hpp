#pragma once

#include "Engine.hpp"
#include "vulkan/vulkan.hpp"

FLYENGINE_BEGIN_NAMESPACE

class ShaderImpl : public Shader
{
private:
    VkShaderModule CreateShaderModule(const std::vector<char> &code);

public:
    virtual void Initialize(ShaderInfo shaderInfo);
    virtual void Destroy();
};

FLYENGINE_END_NAMESPACE