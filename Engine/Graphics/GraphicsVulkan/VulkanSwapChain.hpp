#pragma once
#include "GraphicsCore/GBase.hpp"
#include "GraphicsCore/GraphicsDefine.hpp"

#include <vulkan/vulkan.h>

#include <optional>
#include <vector>

FLYENGINE_GRAPHICS_BEGIN_NAMESPACE

class VulkanInstance;
class VulkanFactory;
class VulkanDevice;

class VulkanSwapChain : public GBase
{
public:
    VulkanSwapChain(VulkanFactory *);

    void Initialize();
    void Finalize();

    void CreateSwapChain();
    void CreateImageViews();

    VkResult AquireNextImage(VkSemaphore &completedSemaphore, uint32_t &index);
    VkResult QueuePresent(VkQueue &presentQueue, VkSemaphore *waitSemaphore);

    VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);
    VkPresentModeKHR   ChooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);
    VkExtent2D         ChooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);

    VkFormat                  GetVkFormat() { return swapChainImageFormat; }
    std::vector<VkImage>     &GetImages() { return swapChainImages; }
    std::vector<VkImageView> &GetImageViews() { return swapChainImageViews; }
    VkExtent2D                GetSwapChainExtent() { return swapChainExtent; }

public:
    VulkanFactory  *m_pVukanFactory;
    VulkanInstance *m_pVInstance;
    VulkanDevice   *m_pVulkanDevice;

    uint32_t                 activeImageIndex{};
    VkSwapchainKHR           swapChain;
    std::vector<VkImage>     swapChainImages;
    VkFormat                 swapChainImageFormat;
    VkExtent2D               swapChainExtent;
    std::vector<VkImageView> swapChainImageViews;
    uint32_t                 width  = 0;
    uint32_t                 height = 0;
};
FLYENGINE_END_NAMESPACE