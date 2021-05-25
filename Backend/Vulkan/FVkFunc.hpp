#pragma once
#include "FVkBuffer.hpp"
#include "FVkDefine.hpp"
namespace FlyEngine::Backend
{
VkBufferUsageFlagBits MapVkBufferUsageFlagBits(BufferUsage usage);

VkShaderStageFlagBits MapVkShaderStageFlagBits(ShaderStageFlagBit stage);

VkResult CreateDebugUtilsMessengerEXT(VkInstance                                instance,
                                      const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
                                      const VkAllocationCallbacks *             pAllocator,
                                      VkDebugUtilsMessengerEXT *                pDebugMessenger);
void     DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks *pAllocator);

}  // namespace FlyEngine::Backend