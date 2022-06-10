#include "SwapChainImpl.hpp"

#include "DeviceManagerImpl.hpp"
#include "Instance.hpp"
#include "VulkanFunc.hpp"

#include <assert.h>
#include <algorithm>
#include <iostream>
#include <limits>
#include <set>
#include <string>
#include <vector>

#define GRAPHICS_max(a, b) (((a) > (b)) ? (a) : (b))
#define GRAPHICS_min(a, b) (((a) < (b)) ? (a) : (b))

FLYENGINE_BEGIN_NAMESPACE

SwapChainImpl::SwapChainImpl()
{
    swapChainExtent.width  = 0;
    swapChainExtent.height = 0;
}

void SwapChainImpl::Initialize()
{
    CreateSwapChain();
    CreateImageViews();
}

void SwapChainImpl::Finalize()
{
    for (auto entry : m_entries)
    {
        vkDestroyImageView(g_pDeviceManager->device->m_device, entry.imageView, nullptr);
        vkDestroySemaphore(g_pDeviceManager->device->m_device, entry.readSemaphore, nullptr);
        vkDestroySemaphore(g_pDeviceManager->device->m_device, entry.writtenSemaphore, nullptr);
    }

    vkDestroySwapchainKHR(g_pDeviceManager->device->m_device, swapChain, nullptr);
    swapChain = VK_NULL_HANDLE;

    m_entries.clear();
}

void SwapChainImpl::CreateSwapChain()
{
    VkPhysicalDevice        device           = g_pDeviceManager->device->m_physicalDevice;
    SwapChainSupportDetails swapChainSupport = g_pDeviceManager->device->QuerySwapChainSupport(device);

    VkSurfaceFormatKHR surfaceFormat = ChooseSwapSurfaceFormat(swapChainSupport.formats);
    VkPresentModeKHR   presentMode   = ChooseSwapPresentMode(swapChainSupport.presentModes);
    VkExtent2D         extent        = ChooseSwapExtent(swapChainSupport.capabilities);

    uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
    if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount)
    {
        imageCount = swapChainSupport.capabilities.maxImageCount;
    }

    auto surface = g_pDeviceManager->surfaceKHR->surfaceKHR;

    VkSwapchainCreateInfoKHR createInfo{};
    createInfo.sType   = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = surface;

    createInfo.minImageCount    = imageCount;
    createInfo.imageFormat      = surfaceFormat.format;
    createInfo.imageColorSpace  = surfaceFormat.colorSpace;
    createInfo.imageExtent      = extent;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage       = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    QueueFamilyIndices indices              = g_pDeviceManager->device->FindQueueFamilies(g_pDeviceManager->device->m_physicalDevice);
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

    CheckVk(vkCreateSwapchainKHR(g_pDeviceManager->device->m_device, &createInfo, nullptr, &swapChain));

    swapChainImageFormat = surfaceFormat.format;
}

void SwapChainImpl::CreateImageViews()
{
    VkResult err;
    CheckVk(vkGetSwapchainImagesKHR(g_pDeviceManager->device->m_device, swapChain, &m_imageCount, nullptr));
    std::vector<VkImage> images(m_imageCount);
    CheckVk(vkGetSwapchainImagesKHR(g_pDeviceManager->device->m_device, swapChain, &m_imageCount, images.data()));

    m_entries.resize(m_imageCount);

    for (size_t i = 0; i < m_imageCount; i++)
    {
        Entry &entry = m_entries[i];
        entry.image  = images[i];

        VkImageViewCreateInfo createInfo{};
        createInfo.sType    = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        createInfo.image    = entry.image;
        createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        createInfo.format   = swapChainImageFormat;

        createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

        createInfo.subresourceRange.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT;
        createInfo.subresourceRange.baseMipLevel   = 0;
        createInfo.subresourceRange.levelCount     = 1;
        createInfo.subresourceRange.baseArrayLayer = 0;
        createInfo.subresourceRange.layerCount     = 1;

        err = CheckVk(vkCreateImageView(g_pDeviceManager->device->m_device, &createInfo, nullptr, &entry.imageView));

        VkSemaphoreCreateInfo semCreateInfo = {VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO};

        err = CheckVk(vkCreateSemaphore(g_pDeviceManager->device->m_device, &semCreateInfo, nullptr, &entry.readSemaphore));

        err = CheckVk(vkCreateSemaphore(g_pDeviceManager->device->m_device, &semCreateInfo, nullptr, &entry.writtenSemaphore));
    }
}

bool SwapChainImpl::Acquire(VkSemaphore argSemaphore, SwapChainAcquireState *pOut)
{
    VkDevice    device    = g_pDeviceManager->device->m_device;
    VkSemaphore semaphore = argSemaphore ? argSemaphore : GetActiveReadSemaphore();
    VkResult    result;
    result = CheckVk(vkAcquireNextImageKHR(device, swapChain, UINT64_MAX, semaphore, (VkFence)VK_NULL_HANDLE, &m_currentImage));

    if (result == VK_SUCCESS)
    {
        if (pOut != nullptr)
        {
            pOut->image     = GetActiveImage();
            pOut->view      = GetActiveImageView();
            pOut->index     = GetActiveImageIndex();
            pOut->waitSem   = GetActiveReadSemaphore();
            pOut->signalSem = GetActiveWrittenSemaphore();
        }
        return true;
    }
    return false;
}

VkResult SwapChainImpl::QueuePresent(VkQueue &presentQueue)
{
    VkSemaphore swapchainWrittenSemaphore = GetActiveWrittenSemaphore();

    VkPresentInfoKHR presentInfo = {};
    presentInfo.sType            = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores    = &swapchainWrittenSemaphore;

    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains    = &swapChain;
    presentInfo.pImageIndices  = &m_currentImage;
    presentInfo.pResults       = nullptr;

    m_currentSemaphore++;

    return CheckVk(vkQueuePresentKHR(presentQueue, &presentInfo));
}

VkSurfaceFormatKHR SwapChainImpl::ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats)
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

VkPresentModeKHR SwapChainImpl::ChooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes)
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

VkExtent2D SwapChainImpl::ChooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities)
{
    VkExtent2D extent = {};
    if (capabilities.currentExtent.width == 0xFFFFFFFF && swapChainExtent.width != 0 && swapChainExtent.height != 0)
    {
        extent.width  = GRAPHICS_min(GRAPHICS_max(swapChainExtent.width, capabilities.minImageExtent.width), capabilities.maxImageExtent.width);
        extent.height = GRAPHICS_min(GRAPHICS_max(swapChainExtent.height, capabilities.minImageExtent.height), capabilities.maxImageExtent.height);
    }
    else
    {
        extent = capabilities.currentExtent;
    }
    swapChainExtent.width  = GRAPHICS_max(extent.width, 1u);
    swapChainExtent.height = GRAPHICS_max(extent.height, 1u);

    return swapChainExtent;
}

VkSemaphore SwapChainImpl::GetActiveWrittenSemaphore() const
{
    return m_entries[(m_currentSemaphore % m_imageCount)].writtenSemaphore;
}

VkSemaphore SwapChainImpl::GetActiveReadSemaphore() const
{
    return m_entries[(m_currentSemaphore % m_imageCount)].readSemaphore;
}

VkImage SwapChainImpl::GetActiveImage() const
{
    return m_entries[m_currentImage].image;
}

VkImageView SwapChainImpl::GetActiveImageView() const
{
    return m_entries[m_currentImage].imageView;
}

FLYENGINE_END_NAMESPACE