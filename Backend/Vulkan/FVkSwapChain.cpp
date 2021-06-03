#include "FVkSwapChain.hpp"

#include <iostream>
#include "../../FlyApp/WindowBase.hpp"
#include "FVkDevice.hpp"
#include "FVkLogicalDevice.hpp"
#include "FVkPhysicalDevice.hpp"

namespace FlyEngine::Backend
{
FVkSwapChain::FVkSwapChain(FVkLogicalDevice *logicalDevice, FVkPhysicalDevice *physicalDevice, FVkDevice *context, WindowBase *window)
    : p_FVkLogicalDevice(logicalDevice), p_FVkPhysicalDevice(physicalDevice), p_FVkDevice(context), p_Window(window)
{}

FVkSwapChain::~FVkSwapChain() {}

void FVkSwapChain::Initialize()
{
    CreateSwapChain();
    CreateImageViews();
}

void FVkSwapChain::Destroy()
{
    for (auto imageView : swapChainImageViews)
    {
        vkDestroyImageView(p_FVkLogicalDevice->GetLogicalDevice(), imageView, nullptr);
    }

    vkDestroySwapchainKHR(p_FVkLogicalDevice->GetLogicalDevice(), swapChain, nullptr);
}

void FVkSwapChain::CreateSwapChain()
{
    VkPhysicalDevice        device           = p_FVkPhysicalDevice->GetVkPhysicalDevice();
    SwapChainSupportDetails swapChainSupport = p_FVkPhysicalDevice->QuerySwapChainSupport(device);

    VkSurfaceFormatKHR surfaceFormat = ChooseSwapSurfaceFormat(swapChainSupport.formats);
    VkPresentModeKHR   presentMode   = ChooseSwapPresentMode(swapChainSupport.presentModes);
    VkExtent2D         extent        = ChooseSwapExtent(swapChainSupport.capabilities);

    uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
    if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount)
    {
        imageCount = swapChainSupport.capabilities.maxImageCount;
    }

    auto surface = p_FVkDevice->GetVkSurfaceKHR();

    VkSwapchainCreateInfoKHR createInfo{};
    createInfo.sType   = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = surface;

    createInfo.minImageCount    = imageCount;
    createInfo.imageFormat      = surfaceFormat.format;
    createInfo.imageColorSpace  = surfaceFormat.colorSpace;
    createInfo.imageExtent      = extent;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage       = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    QueueFamilyIndices indices              = p_FVkPhysicalDevice->FindQueueFamilies(p_FVkPhysicalDevice->GetVkPhysicalDevice());
    uint32_t           queueFamilyIndices[] = {indices.graphicsFamily.value(), indices.presentFamily.value()};

    if (indices.graphicsFamily != indices.presentFamily)
    {
        createInfo.imageSharingMode      = VK_SHARING_MODE_CONCURRENT;
        createInfo.queueFamilyIndexCount = 2;
        createInfo.pQueueFamilyIndices   = queueFamilyIndices;
    }
    else
    {
        createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    }

    createInfo.preTransform   = swapChainSupport.capabilities.currentTransform;
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    createInfo.presentMode    = presentMode;
    createInfo.clipped        = VK_TRUE;

    if (vkCreateSwapchainKHR(p_FVkLogicalDevice->GetLogicalDevice(), &createInfo, nullptr, &swapChain) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create swap chain!");
    }

    vkGetSwapchainImagesKHR(p_FVkLogicalDevice->GetLogicalDevice(), swapChain, &imageCount, nullptr);
    swapChainImages.resize(imageCount);
    vkGetSwapchainImagesKHR(p_FVkLogicalDevice->GetLogicalDevice(), swapChain, &imageCount, swapChainImages.data());

    swapChainImageFormat = surfaceFormat.format;
    swapChainExtent      = extent;
}

void FVkSwapChain::CreateImageViews()
{
    swapChainImageViews.resize(swapChainImages.size());

    for (size_t i = 0; i < swapChainImages.size(); i++)
    {
        VkImageViewCreateInfo createInfo{};
        createInfo.sType                           = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        createInfo.image                           = swapChainImages[i];
        createInfo.viewType                        = VK_IMAGE_VIEW_TYPE_2D;
        createInfo.format                          = swapChainImageFormat;
        createInfo.components.r                    = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.g                    = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.b                    = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.a                    = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.subresourceRange.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT;
        createInfo.subresourceRange.baseMipLevel   = 0;
        createInfo.subresourceRange.levelCount     = 1;
        createInfo.subresourceRange.baseArrayLayer = 0;
        createInfo.subresourceRange.layerCount     = 1;

        if (vkCreateImageView(p_FVkLogicalDevice->GetLogicalDevice(), &createInfo, nullptr, &swapChainImageViews[i]) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create image views!");
        }
    }
}

VkResult FVkSwapChain::AquireNextImage(VkSemaphore &completedSemaphore, uint32_t &index)
{
    VkDevice device = p_FVkLogicalDevice->GetLogicalDevice();
    VkResult iRes =
        vkAcquireNextImageKHR(device, swapChain, std::numeric_limits<uint64_t>::max(), completedSemaphore, VK_NULL_HANDLE, &activeImageIndex);
    index = activeImageIndex;
    return iRes;
}

VkResult FVkSwapChain::QueuePresent(VkQueue &presentQueue, VkSemaphore *waitSemaphore)
{
    VkPresentInfoKHR presentInfo = {};
    presentInfo.sType            = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores    = waitSemaphore;

    VkSwapchainKHR swapChains[] = {swapChain};

    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains    = swapChains;
    presentInfo.pImageIndices  = &activeImageIndex;
    presentInfo.pResults       = nullptr;

    return vkQueuePresentKHR(presentQueue, &presentInfo);
}

VkSurfaceFormatKHR FVkSwapChain::ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats)
{
    for (const auto &availableFormat : availableFormats)
    {
        if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
        {
            return availableFormat;
        }
    }

    return availableFormats[0];
}

VkPresentModeKHR FVkSwapChain::ChooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes)
{
    for (const auto &availablePresentMode : availablePresentModes)
    {
        if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
        {
            return availablePresentMode;
        }
    }

    return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D FVkSwapChain::ChooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities)
{
    if (capabilities.currentExtent.width != UINT32_MAX)
    {
        return capabilities.currentExtent;
    }
    else
    {
        int width, height;
        p_Window->GetFrameSize(width, height);
        VkExtent2D actualExtent = {static_cast<uint32_t>(width), static_cast<uint32_t>(height)};

        actualExtent.width  = std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width, actualExtent.width));
        actualExtent.height = std::max(capabilities.minImageExtent.height, std::min(capabilities.maxImageExtent.height, actualExtent.height));

        return actualExtent;
    }
}

}  // namespace FlyEngine::Backend