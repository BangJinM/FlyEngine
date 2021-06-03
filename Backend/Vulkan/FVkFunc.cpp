#include "FVkFunc.hpp"

#include "FVkBuffer.hpp"
#include "FVkDevice.hpp"

namespace FlyEngine::Backend
{
VkBufferUsageFlagBits MapVkBufferUsageFlagBits(uint usage)
{
    uint flags = 0u;
    if (usage & BufferUsage::TRANSFER_SRC)
        flags |= VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
    if (usage & BufferUsage::TRANSFER_DST)
        flags |= VK_BUFFER_USAGE_TRANSFER_DST_BIT;
    if (usage & BufferUsage::INDEX)
        flags |= VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
    if (usage & BufferUsage::VERTEX)
        flags |= VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
    if (usage & BufferUsage::UNIFORM)
        flags |= VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
    if (usage & BufferUsage::STORAGE)
        flags |= VK_BUFFER_USAGE_STORAGE_BUFFER_BIT;
    if (usage & BufferUsage::INDIRECT)
        flags |= VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT;
    return (VkBufferUsageFlagBits)flags;
}

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

VkDescriptorType MapVkDescriptorType(DescriptorType type)
{
    switch (type)
    {
        case DescriptorType::DYNAMIC_UNIFORM_BUFFER: return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
        case DescriptorType::UNIFORM_BUFFER: return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        case DescriptorType::DYNAMIC_STORAGE_BUFFER: return VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC;
        case DescriptorType::STORAGE_BUFFER: return VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
        case DescriptorType::SAMPLER: return VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        default:
        {
            return VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
        }
    }
}

VkResult CreateDebugUtilsMessengerEXT(VkInstance                                instance,
                                      const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
                                      const VkAllocationCallbacks *             pAllocator,
                                      VkDebugUtilsMessengerEXT *                pDebugMessenger)
{
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
    if (func != nullptr)
    {
        return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
    }
    else
    {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}

void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks *pAllocator)
{
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
    if (func != nullptr)
    {
        func(instance, debugMessenger, pAllocator);
    }
}

std::vector<const char *> getRequiredExtensions()
{
    uint32_t     glfwExtensionCount = 0;
    const char **glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    std::vector<const char *> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

    if (enableValidationLayers)
    {
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    return extensions;
}

bool checkValidationLayerSupport()
{
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    for (const char *layerName : validationLayers)
    {
        bool layerFound = false;

        for (const auto &layerProperties : availableLayers)
        {
            if (strcmp(layerName, layerProperties.layerName) == 0)
            {
                layerFound = true;
                break;
            }
        }

        if (!layerFound)
        {
            return false;
        }
    }
    return true;
}

}  // namespace FlyEngine::Backend