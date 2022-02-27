// https://github1s.com/nvpro-samples/nvpro_core/blob/HEAD/nvvk/swapchain_vk.cpp
#pragma once

#include "GraphicsCore/Base.hpp"

#include <vulkan/vulkan.h>

#include <optional>
#include <vector>

FLYENGINE_BEGIN_NAMESPACE

class Instance;
class DeviceManagerImpl;

// What SwapChain::acquire produces: a swap chain image plus
// semaphores protecting it.
struct SwapChainAcquireState
{
    // The image and its view and index in the swap chain.
    VkImage     image;
    VkImageView view;
    uint32_t    index;
    // MUST wait on this semaphore before writing to the image. ("The
    // system" signals this semaphore when it's done presenting the
    // image and can safely be reused).
    VkSemaphore waitSem;
    // MUST signal this semaphore when done writing to the image, and
    // before presenting it. (The system waits for this before presenting).
    VkSemaphore signalSem;
};

struct Entry
{
    VkImage     image{};
    VkImageView imageView{};
    // be aware semaphore index may not match active image index
    VkSemaphore readSemaphore{};
    VkSemaphore writtenSemaphore{};

    VkFence fence{};
};

class DeviceManagerImpl;
extern DeviceManagerImpl *p_gDeviceManager;

class SwapChainImpl : public Base
{
public:
    SwapChainImpl();

    void Initialize();
    void Finalize();

    void CreateSwapChain();
    void CreateImageViews();

    bool     Acquire(VkSemaphore argSemaphore = VK_NULL_HANDLE, SwapChainAcquireState *pOut = nullptr);
    VkResult QueuePresent(VkQueue &presentQueue);

    VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);
    VkPresentModeKHR   ChooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);
    VkExtent2D         ChooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);

    VkFormat   GetVkFormat() { return swapChainImageFormat; }
    VkExtent2D GetSwapChainExtent() { return swapChainExtent; }

    VkSemaphore getActiveWrittenSemaphore() const;
    VkSemaphore getActiveReadSemaphore() const;
    VkImage     getActiveImage() const;
    VkImageView getActiveImageView() const;
    uint32_t    getActiveImageIndex() const { return m_currentImage; }
    VkImageView getImageView(int index) const { return m_entries[index].imageView; }
    uint32_t    GetImageCount() { return m_imageCount; }
    VkFence     GetFence() { return m_entries[m_currentImage].fence; }

public:
    uint32_t       m_currentImage{};
    VkSwapchainKHR swapChain;
    VkFormat       swapChainImageFormat;
    VkExtent2D     swapChainExtent;

    uint32_t m_currentSemaphore = 0;
    uint32_t m_imageCount;

    std::vector<Entry> m_entries;
};
FLYENGINE_END_NAMESPACE