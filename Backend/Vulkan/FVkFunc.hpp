#pragma once
#include "FVkBuffer.hpp"
#include "FVkDefine.hpp"
namespace FlyEngine::Backend
{
VkBufferUsageFlagBits MapVkBufferUsageFlagBits(uint usage);

VkShaderStageFlagBits MapVkShaderStageFlagBits(ShaderStageFlagBit stage);

VkDescriptorType MapVkDescriptorType(DescriptorType type);

VkShaderStageFlagBits MapVkShaderStageFlagBits(ShaderStageFlagBit stage);

VkResult CreateDebugUtilsMessengerEXT(VkInstance                                instance,
                                      const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
                                      const VkAllocationCallbacks *             pAllocator,
                                      VkDebugUtilsMessengerEXT *                pDebugMessenger);
void     DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks *pAllocator);

std::vector<const char *> getRequiredExtensions();
bool                      checkValidationLayerSupport();

}  // namespace FlyEngine::Backend