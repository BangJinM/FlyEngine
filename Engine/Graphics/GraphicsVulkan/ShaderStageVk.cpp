#include "ShaderStageVk.hpp"

#include <assert.h>

#include "DeviceVk.hpp"
#include "InstanceVk.hpp"
#include "VulkanDefines.hpp"
#include "VulkanFactory.hpp"
#include "VulkanFunc.hpp"

FLYENGINE_GRAPHICS_BEGIN_NAMESPACE

ShaderStageVk::ShaderStageVk(VulkanFactory *factory, ShaderStageInfo shaderInfo) : ShaderStage(shaderInfo), m_pVulkanFactory(factory)
{
    m_pVulkanDevice = factory->m_pDevice;
}

void ShaderStageVk::Initialize()
{
    VkDevice &device = m_pVulkanDevice->m_device;

    VkShaderModuleCreateInfo createInfo{};
    createInfo.sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = m_shaderInfo.source.size();
    createInfo.pCode    = reinterpret_cast<const uint32_t *>(m_shaderInfo.source.data());

    auto err = vkCreateShaderModule(device, &createInfo, nullptr, &stage);
    assert(!err);
}

void ShaderStageVk::Finalize()
{
    VkDevice &device = m_pVulkanDevice->m_device;

    vkDestroyShaderModule(device, stage, nullptr);
}

FLYENGINE_END_NAMESPACE