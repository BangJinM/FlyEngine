#pragma once

#include "../Core/FlyContext.hpp"
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <optional>
#include <vector>

namespace FlyEngine::Backend
{
const std::vector<const char *> validationLayers = {"VK_LAYER_KHRONOS_validation"};

const std::vector<const char *> deviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};

const int MAX_FRAMES_IN_FLIGHT = 2;

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

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

class FVkContext : FlyContext
{
public:
    virtual void Initialize(const AppInfo &info) override;
    virtual void Destroy() override;

public:
    VkDevice &GetVkDevice() { return device; }

    uint32_t        FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
    VkCommandBuffer BeginSingleTimeCommands();
    void            EndSingleTimeCommands(VkCommandBuffer commandBuffer);
    void            Draw();
    VkFormat        GetVkFormat() { return swapChainImageFormat; }

private:
    void initVulkan();
    void cleanupSwapChain();
    void cleanup();
    void recreateSwapChain();
    void createInstance();
    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo);
    void setupDebugMessenger();
    void createSurface();
    void pickPhysicalDevice();
    void createLogicalDevice();
    void createSwapChain();
    void createImageViews();
    void createRenderPass();
    void createGraphicsPipeline();
    void createFramebuffers();
    void createCommandPool();
    void createCommandBuffers();
    void createSyncObjects();
    void drawFrame();

    VkSurfaceFormatKHR        chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);
    VkShaderModule            createShaderModule(const std::string &code);
    VkPresentModeKHR          chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);
    VkExtent2D                chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);
    SwapChainSupportDetails   querySwapChainSupport(VkPhysicalDevice device);
    bool                      isDeviceSuitable(VkPhysicalDevice device);
    bool                      checkDeviceExtensionSupport(VkPhysicalDevice device);
    QueueFamilyIndices        findQueueFamilies(VkPhysicalDevice device);
    std::vector<const char *> getRequiredExtensions();
    bool                      checkValidationLayerSupport();

private:
    VkInstance               instance;
    VkDebugUtilsMessengerEXT debugMessenger;
    VkSurfaceKHR             surface;

    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice         device;

    VkQueue graphicsQueue;
    VkQueue presentQueue;

    VkSwapchainKHR             swapChain;
    std::vector<VkImage>       swapChainImages;
    VkFormat                   swapChainImageFormat;
    VkExtent2D                 swapChainExtent;
    std::vector<VkImageView>   swapChainImageViews;
    std::vector<VkFramebuffer> swapChainFramebuffers;

    VkRenderPass     renderPass;
    VkPipelineLayout pipelineLayout;
    VkPipeline       graphicsPipeline;

    VkCommandPool                commandPool;
    std::vector<VkCommandBuffer> commandBuffers;

    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence>     inFlightFences;
    std::vector<VkFence>     imagesInFlight;
    size_t                   currentFrame = 0;

    AppInfo appInfo;

    bool framebufferResized = false;
};
}  // namespace FlyEngine::Backend