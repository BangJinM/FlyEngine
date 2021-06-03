#pragma once

#include "FVkDefine.hpp"
namespace FlyEngine::Backend
{
class FVkInstance;
class FVkDevice;
class FVkPhysicalDevice
{
public:
    FVkPhysicalDevice(FVkInstance *instance, FVkDevice *context);
    ~FVkPhysicalDevice();

    void Initialize();
    void Destroy();

    void PickPhysicalDevice();
    bool IsDeviceSuitable(VkPhysicalDevice device);
    bool CheckDeviceExtensionSupport(VkPhysicalDevice device);

    QueueFamilyIndices        FindQueueFamilies(VkPhysicalDevice device);
    SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);

    VkPhysicalDevice& GetVkPhysicalDevice() { return physicalDevice; }

private:
    FVkInstance * p_FVkInstance;
    FVkDevice *p_FVkDevice;

    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
};
}  // namespace FlyEngine::Backend