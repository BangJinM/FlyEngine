#pragma once
#include "GraphicsCore/ShaderStage.hpp"

#include "vulkan/vulkan.h"

#include <string>

FLYENGINE_GRAPHICS_BEGIN_NAMESPACE

class VulkanFactory;
class DeviceVk;

class ShaderStageVk : public ShaderStage
{
public:
    ShaderStageVk(VulkanFactory *, ShaderStageInfo shaderInfo);

    virtual void Initialize();
    virtual void Finalize();

private:
    VkShaderModule createShaderModule(const std::string source);

public:
private:
    DeviceVk      *m_pVulkanDevice;
    VulkanFactory *m_pVulkanFactory;

    VkShaderModule stage;
};

FLYENGINE_END_NAMESPACE