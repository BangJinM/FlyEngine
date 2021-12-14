#include "VulkanSwapChain.hpp"

#include "VulkanDefines.hpp"
#include "VulkanDevice.hpp"
#include "VulkanFactory.hpp"
#include "VulkanInstance.hpp"

#include <assert.h>
#include <algorithm>
#include <iostream>
#include <limits>
#include <set>
#include <string>
#include <vector>

#define GRAPHICS_max(a, b) (((a) > (b)) ? (a) : (b))
#define GRAPHICS_min(a, b) (((a) < (b)) ? (a) : (b))

FLYENGINE_GRAPHICS_BEGIN_NAMESPACE

VulkanSwapChain::VulkanSwapChain(VulkanFactory *factory) : m_pVukanFactory(factory)
{
    m_pVInstance    = factory->m_pVInstance;
    m_pVulkanDevice = factory->m_pDevice;
}

void VulkanSwapChain::Initialize()
{
    CreateSwapChain();
    CreateImageViews();
}

void VulkanSwapChain::Finalize()
{
    for (auto imageView : swapChainImageViews)
    {
        vkDestroyImageView(m_pVulkanDevice->m_device, imageView, nullptr);
    }

    vkDestroySwapchainKHR(m_pVulkanDevice->m_device, swapChain, nullptr);
}

void VulkanSwapChain::CreateSwapChain()
{
    VkPhysicalDevice        device           = m_pVulkanDevice->m_physicalDevice;
    SwapChainSupportDetails swapChainSupport = m_pVulkanDevice->QuerySwapChainSupport(device);

    VkSurfaceFormatKHR surfaceFormat = ChooseSwapSurfaceFormat(swapChainSupport.formats);
    VkPresentModeKHR   presentMode   = ChooseSwapPresentMode(swapChainSupport.presentModes);
    VkExtent2D         extent        = ChooseSwapExtent(swapChainSupport.capabilities);

    uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
    if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount)
    {
        imageCount = swapChainSupport.capabilities.maxImageCount;
    }

    auto surface = m_pVulkanDevice->m_surfaceKHR;

    VkSwapchainCreateInfoKHR createInfo{};
    createInfo.sType   = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = surface;

    createInfo.minImageCount    = imageCount;
    createInfo.imageFormat      = surfaceFormat.format;
    createInfo.imageColorSpace  = surfaceFormat.colorSpace;
    createInfo.imageExtent      = extent;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage       = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    QueueFamilyIndices indices              = m_pVulkanDevice->FindQueueFamilies(m_pVulkanDevice->m_physicalDevice);
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

    if (vkCreateSwapchainKHR(m_pVulkanDevice->m_device, &createInfo, nullptr, &swapChain) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create swap chain!");
    }

    vkGetSwapchainImagesKHR(m_pVulkanDevice->m_device, swapChain, &imageCount, nullptr);
    swapChainImages.resize(imageCount);
    vkGetSwapchainImagesKHR(m_pVulkanDevice->m_device, swapChain, &imageCount, swapChainImages.data());

    swapChainImageFormat = surfaceFormat.format;
    swapChainExtent      = extent;
}

void VulkanSwapChain::CreateImageViews()
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

        if (vkCreateImageView(m_pVulkanDevice->m_device, &createInfo, nullptr, &swapChainImageViews[i]) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create image views!");
        }
    }
}

VkResult VulkanSwapChain::AquireNextImage(VkSemaphore &completedSemaphore, uint32_t &index)
{
    VkDevice device = m_pVulkanDevice->m_device;
    VkResult iRes   = vkAcquireNextImageKHR(device, swapChain, 0xFFFFFFFF, completedSemaphore, VK_NULL_HANDLE, &activeImageIndex);
    index           = activeImageIndex;
    return iRes;
}

VkResult VulkanSwapChain::QueuePresent(VkQueue &presentQueue, VkSemaphore *waitSemaphore)
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

VkSurfaceFormatKHR VulkanSwapChain::ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats)
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

VkPresentModeKHR VulkanSwapChain::ChooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes)
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

VkExtent2D VulkanSwapChain::ChooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities)
{
    VkExtent2D swapchainExtent = {};
    // width and height are either both 0xFFFFFFFF, or both not 0xFFFFFFFF.
    if (capabilities.currentExtent.width == 0xFFFFFFFF && width != 0 && height != 0)
    {
        // If the surface size is undefined, the size is set to
        // the size of the images requested.
        swapchainExtent.width  = GRAPHICS_min(GRAPHICS_max(width, capabilities.minImageExtent.width), capabilities.maxImageExtent.width);
        swapchainExtent.height = GRAPHICS_min(GRAPHICS_max(height, capabilities.minImageExtent.height), capabilities.maxImageExtent.height);
    }
    else
    {
        // If the surface size is defined, the swap chain size must match
        swapchainExtent = capabilities.currentExtent;
    }
    swapchainExtent.width  = GRAPHICS_max(swapchainExtent.width, 1u);
    swapchainExtent.height = GRAPHICS_max(swapchainExtent.height, 1u);

    width  = swapchainExtent.width;
    height = swapchainExtent.height;
    return swapchainExtent;
}

FLYENGINE_END_NAMESPACE