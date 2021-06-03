#pragma once

#include "FVkDefine.hpp"

namespace FlyEngine::Backend
{
class FVkDevice;
class FVkPhysicalDevice;

class FVkLogicalDevice
{
public:
    FVkLogicalDevice(FVkDevice *context, FVkPhysicalDevice *physicalDevice);
    ~FVkLogicalDevice();

    void Initialize();
    void Destroy();

    void CreateLogicalDevice();

    void WaitIdle() { vkDeviceWaitIdle(device); }

    VkDevice &GetLogicalDevice() { return device; }
    VkQueue & GetGraphicsQueue() { return graphicsQueue; }
    VkQueue & GetPresentQueue() { return presentQueue; }

private:
    FVkDevice *       p_FVkDevice;
    FVkPhysicalDevice *p_FVkPhysicalDevice;

    VkDevice device;
    VkQueue  graphicsQueue;
    VkQueue  presentQueue;
};

}  // namespace FlyEngine::Backend