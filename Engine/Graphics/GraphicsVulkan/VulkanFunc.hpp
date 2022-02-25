#pragma once

#include <vulkan/vulkan.hpp>

#include "Common/BaseDefines.hpp"

#include <iostream>

FLYENGINE_BEGIN_NAMESPACE

std::string StringifyResultVk(VkResult result);

VkResult CheckVk(VkResult result);

FLYENGINE_END_NAMESPACE