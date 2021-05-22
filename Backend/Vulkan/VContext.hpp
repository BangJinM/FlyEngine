#pragma once

#include "../Core/FlyContext.hpp"
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <optional>
#include <vector>

namespace FlyEngine::Backend
{
const std::vector<const char *> validationLayers = {
    "VK_LAYER_KHRONOS_validation"};

const std::vector<const char *> deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME};

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR        capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR>   presentModes;
};

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete()
    {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};

class VContext : FlyContext
{
public:
    virtual void Initialize(const AppInfo &info) override;
    virtual void Destroy() override;

private:
    void                      createInstance();
    void                      createSurface(const AppInfo &info);
    void                      pickPhysicalDevice();
    void                      createLogicalDevice();
    void                      createSwapChain();
    void                      createImageViews();
    void                      setupDebugMessenger();
    bool                      checkValidationLayerSupport();
    bool                      checkDeviceExtensionSupport(VkPhysicalDevice device);
    SwapChainSupportDetails   querySwapChainSupport(VkPhysicalDevice device);
    bool                      isDeviceSuitable(VkPhysicalDevice device);
    QueueFamilyIndices        findQueueFamilies(VkPhysicalDevice device);
    std::vector<const char *> getRequiredExtensions();

    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);
    VkPresentModeKHR   chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);
    VkExtent2D         chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);

private:
    VkInstance               instance;
    VkDebugUtilsMessengerEXT debugMessenger;
    VkSurfaceKHR             surface;

    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice         device;
    VkQueue          graphicsQueue;
    VkQueue          presentQueue;

    VkSwapchainKHR           swapChain;
    std::vector<VkImage>     swapChainImages;
    VkFormat                 swapChainImageFormat;
    VkExtent2D               swapChainExtent;
    std::vector<VkImageView> swapChainImageViews;

    bool enableValidationLayers = false;

    AppInfo deviceInfo;
};
} // namespace FlyEngine::Backend