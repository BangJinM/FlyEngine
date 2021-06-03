#include "FVkLogicalDevice.hpp"

#include "FVkDevice.hpp"
#include "FVkPhysicalDevice.hpp"

#include <iostream>
#include <set>
#include <string>
#include <vector>

namespace FlyEngine::Backend
{
FVkLogicalDevice::FVkLogicalDevice(FVkDevice *context, FVkPhysicalDevice *physicalDevice) : p_FVkDevice(context), p_FVkPhysicalDevice(physicalDevice)
{}

FVkLogicalDevice::~FVkLogicalDevice() {}

void FVkLogicalDevice::Initialize()
{
    CreateLogicalDevice();
}

void FVkLogicalDevice::Destroy()
{
    vkDestroyDevice(device, nullptr);
}

void FVkLogicalDevice::CreateLogicalDevice()
{
    QueueFamilyIndices indices = p_FVkPhysicalDevice->FindQueueFamilies(p_FVkPhysicalDevice->GetVkPhysicalDevice());

    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    std::set<uint32_t>                   uniqueQueueFamilies = {indices.graphicsFamily.value(), indices.presentFamily.value()};

    float queuePriority = 1.0f;
    for (uint32_t queueFamily : uniqueQueueFamilies)
    {
        VkDeviceQueueCreateInfo queueCreateInfo{};
        queueCreateInfo.sType            = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = queueFamily;
        queueCreateInfo.queueCount       = 1;
        queueCreateInfo.pQueuePriorities = &queuePriority;
        queueCreateInfos.push_back(queueCreateInfo);
    }

    VkPhysicalDeviceFeatures deviceFeatures{};

    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

    createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
    createInfo.pQueueCreateInfos    = queueCreateInfos.data();

    createInfo.pEnabledFeatures = &deviceFeatures;

    createInfo.enabledExtensionCount   = static_cast<uint32_t>(deviceExtensions.size());
    createInfo.ppEnabledExtensionNames = deviceExtensions.data();

    if (enableValidationLayers)
    {
        createInfo.enabledLayerCount   = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();
    }
    else
    {
        createInfo.enabledLayerCount = 0;
    }

    if (vkCreateDevice(p_FVkPhysicalDevice->GetVkPhysicalDevice(), &createInfo, nullptr, &device) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create logical device!");
    }

    vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphicsQueue);
    vkGetDeviceQueue(device, indices.presentFamily.value(), 0, &presentQueue);
}
}  // namespace FlyEngine::Backend