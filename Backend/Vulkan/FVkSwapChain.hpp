#pragma once

#include "FVkDefine.hpp"

namespace FlyEngine
{
class WindowBase;
}
namespace FlyEngine::Backend
{
class FVkLogicalDevice;
class FVkPhysicalDevice;
class FVkDevice;
class FVkSwapChain
{
public:
    FVkSwapChain(FVkLogicalDevice *logicalDevice, FVkPhysicalDevice *physicalDevice, FVkDevice *context, WindowBase *window);
    ~FVkSwapChain();

    void Initialize();
    void Destroy();

    void CreateSwapChain();
    void CreateImageViews();

    VkResult AquireNextImage(VkSemaphore &completedSemaphore, uint32_t& index);
    VkResult QueuePresent(VkQueue &presentQueue, VkSemaphore *waitSemaphore);

    VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);
    VkPresentModeKHR   ChooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);
    VkExtent2D         ChooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);

    VkFormat                  GetVkFormat() { return swapChainImageFormat; }
    std::vector<VkImage> &    GetImages() { return swapChainImages; }
    std::vector<VkImageView> &GetImageViews() { return swapChainImageViews; }
    VkExtent2D                GetSwapChainExtent() { return swapChainExtent; }

private:
    FVkLogicalDevice * p_FVkLogicalDevice;
    FVkPhysicalDevice *p_FVkPhysicalDevice;
    FVkDevice *       p_FVkDevice;
    WindowBase *       p_Window;

    uint32_t activeImageIndex{};

    VkSwapchainKHR           swapChain;
    std::vector<VkImage>     swapChainImages;
    VkFormat                 swapChainImageFormat;
    VkExtent2D               swapChainExtent;
    std::vector<VkImageView> swapChainImageViews;
};

}  // namespace FlyEngine::Backend