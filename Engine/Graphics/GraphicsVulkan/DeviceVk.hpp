#pragma once
#include "GraphicsCore/Base.hpp"
#include "GraphicsCore/GraphicsDefine.hpp"

#include <vulkan/vulkan.h>

#include <optional>
#include <vector>

FLYENGINE_GRAPHICS_BEGIN_NAMESPACE

class InstanceVk;
class VulkanFactory;

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

class DeviceVk : public Base
{
public:
    DeviceVk(VulkanFactory *);

    void Initialize();
    void Finalize();

    void CreateLogicalDevice();
    void PickPhysicalDevice();
    bool IsDeviceSuitable(VkPhysicalDevice device);
    bool CheckDeviceExtensionSupport(VkPhysicalDevice device);

    QueueFamilyIndices      FindQueueFamilies(VkPhysicalDevice device);
    SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);

    VkPhysicalDevice &GetVkPhysicalDevice() { return m_physicalDevice; }
    VkDevice         &GetLogicalDevice() { return m_device; }
    VkQueue          &GetGraphicsQueue() { return m_graphicsQueue; }
    VkQueue          &GetPresentQueue() { return m_presentQueue; }

public:
    VulkanFactory *m_pVukanFactory;
    InstanceVk    *m_pVInstance;

    VkDevice         m_device;
    VkSurfaceKHR     m_surfaceKHR;
    VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
    VkQueue          m_graphicsQueue;
    VkQueue          m_presentQueue;
};
FLYENGINE_END_NAMESPACE