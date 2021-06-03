#pragma once

#include "../Core/FlyDevice.hpp"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "../../FlyApp/AppInfo.hpp"

namespace FlyEngine::Backend
{

class FVkInstance;
class FVkPhysicalDevice;
class FVkLogicalDevice;
class FVkSwapChain;
class FVkRenderPass;

class FVkDevice : public FlyDevice
{

public:
    virtual FlyBuffer *             CreateBuffer(const BufferInfo &info) override;
    virtual FlyCommandBuffer *      CreateCommandBuffer(const CommandBufferInfo &info) override;
    virtual FlyDescriptorSet *      CreateDescriptorSet(const DescriptorSetInfo &info) override;
    virtual FlyDescriptorSetLayout *CreateDescriptorSetLayout(const DescriptorSetLayoutInfo &info) override;
    virtual FlyFence *              CreateFence(const FenceInfo &info) override;
    virtual FlyFramebuffer *        CreateFramebuffer(const FramebufferInfo &info) override;
    virtual FlyInputAssembler *     CreateInputAssembler(const InputAssemblerInfo &info) override;
    virtual FlyPipelineLayout *     CreatePipelineLayout(const PipelineLayoutInfo &info) override;
    virtual FlyQueue *              CreateQueue(const QueueInfo &info) override;
    virtual FlyRenderPass *         CreateRenderPass(const RenderPassInfo &info) override;
    virtual FlySampler *            CreateSampler(const SamplerInfo &info) override;
    virtual FlyShader *             CreateShader(const ShaderInfo &info) override;
    virtual FlyTexture *            CreateTexture(const TextureInfo &info) override;

    virtual void Initialize(WindowBase *window) override;
    virtual void Destroy() override;

    virtual void BeginDraw() override;
    virtual void Draw() override;
    virtual void EndDraw() override;

public:
    VkDevice &GetVkDevice();

    uint32_t        FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
    VkCommandBuffer BeginSingleTimeCommands();
    void            EndSingleTimeCommands(VkCommandBuffer commandBuffer);

    VkSurfaceKHR &     GetVkSurfaceKHR() { return surface; }
    FVkInstance *      GetFVkInstance();
    FVkPhysicalDevice *GetFVkPhysicalDevice();
    FVkLogicalDevice * GetFVkLogicalDevice();
    FVkSwapChain *     GetFVkSwapChain();
    WindowBase *       GetWindowBase();

private:
    void initVulkan();
    void cleanupSwapChain();
    void cleanup();
    void recreateSwapChain();
    void createGlobalRenderPass();
    void createGraphicsPipeline();
    void createFramebuffers();
    void createCommandPool();
    void createCommandBuffers();
    void createSyncObjects();

    VkShaderModule createShaderModule(const std::string &code);

private:
    VkSurfaceKHR surface;

    std::vector<VkFramebuffer> swapChainFramebuffers;

    FVkRenderPass *  renderPass;
    VkPipelineLayout pipelineLayout;
    VkPipeline       graphicsPipeline;

    VkCommandPool                commandPool;
    std::vector<VkCommandBuffer> commandBuffers;

    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence>     inFlightFences;
    std::vector<VkFence>     imagesInFlight;
    size_t                   currentFrame = 0;

    bool framebufferResized = false;

public:
    FVkInstance *      p_FVkInstance;
    FVkPhysicalDevice *p_FVkPhysicalDevice;
    FVkLogicalDevice * p_FVkLogicalDevice;
    FVkSwapChain *     p_FVkSwapChain;
    WindowBase *       p_Window;
};

}  // namespace FlyEngine::Backend