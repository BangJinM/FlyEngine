#pragma once

#include <vulkan/vulkan.hpp>

#include "GraphicsCore/Shader.hpp"

FLYENGINE_BEGIN_NAMESPACE

class ShaderImpl : public Shader
{
private:
    VkShaderModule CreateShaderModule(const std::vector<char> &code);

public:
    ShaderImpl(ShaderInfo shaderInfo) : Shader(shaderInfo) {}

    virtual void Initialize();
    virtual void Destroy();
};

FLYENGINE_END_NAMESPACE