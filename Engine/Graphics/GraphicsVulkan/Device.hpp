#pragma once

#include "Common/BaseDefines.hpp"
#include "GraphicsCore/Base.hpp"

#include <vulkan/vulkan.hpp>

#include <optional>
#include <vector>

FLYENGINE_BEGIN_NAMESPACE

class DeviceManagerImpl;

struct SwapChainSupportDetails
{
    VkSurfaceCapabilitiesKHR        capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR>   presentModes;
};

struct QueueFamilyIndices
{
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete() { return graphicsFamily.has_value() && presentFamily.has_value(); }
};

class Device : public Base
{
public:
    Device();

    void Initialize();
    void Finalize();

    void CreateLogicalDevice();
    void PickPhysicalDevice();
    bool IsDeviceSuitable(VkPhysicalDevice device);
    bool CheckDeviceExtensionSupport(VkPhysicalDevice device);

    QueueFamilyIndices      FindQueueFamilies(VkPhysicalDevice device);
    SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);

    VkPhysicalDevice &GetVkPhysicalDevice() { return m_physicalDevice; }
    VkDevice &        GetLogicalDevice() { return m_device; }
    VkQueue &         GetGraphicsQueue() { return m_graphicsQueue; }
    VkQueue &         GetPresentQueue() { return m_presentQueue; }

public:
    VkDevice         m_device;
    VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
    VkQueue          m_graphicsQueue;
    VkQueue          m_presentQueue;
};
extern DeviceManagerImpl *p_gDeviceManager;
FLYENGINE_END_NAMESPACE