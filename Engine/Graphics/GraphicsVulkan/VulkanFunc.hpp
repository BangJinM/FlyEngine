#pragma once

#include "VulkanDefines.hpp"

#include <iostream>

FLYENGINE_GRAPHICS_BEGIN_NAMESPACE

VkShaderStageFlagBits MapVkShaderStageFlagBits(ShaderStageFlagBit stage);

std::string StringifyResultVk(VkResult result);

VkResult CheckVk(VkResult result);

FLYENGINE_END_NAMESPACE