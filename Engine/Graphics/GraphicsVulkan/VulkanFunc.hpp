#pragma once

#include "VulkanDefines.hpp"

FLYENGINE_GRAPHICS_BEGIN_NAMESPACE

VkShaderStageFlagBits MapVkShaderStageFlagBits(ShaderStageFlagBit stage)
{
    switch (stage)
    {
        case ShaderStageFlagBit::VERTEX: return VK_SHADER_STAGE_VERTEX_BIT;
        case ShaderStageFlagBit::CONTROL: return VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT;
        case ShaderStageFlagBit::EVALUATION: return VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT;
        case ShaderStageFlagBit::GEOMETRY: return VK_SHADER_STAGE_GEOMETRY_BIT;
        case ShaderStageFlagBit::FRAGMENT: return VK_SHADER_STAGE_FRAGMENT_BIT;
        case ShaderStageFlagBit::COMPUTE: return VK_SHADER_STAGE_COMPUTE_BIT;
        default:
        {
            return VK_SHADER_STAGE_VERTEX_BIT;
        }
    }
}

FLYENGINE_END_NAMESPACE