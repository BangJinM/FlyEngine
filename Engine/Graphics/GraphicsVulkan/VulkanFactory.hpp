#pragma once
#include "GraphicsCore/GraphicsDefine.hpp"
#include "GraphicsCore/GraphicsFactory.hpp"

#include "Platforms/NativeWindow.hpp"
#include "VulkanDefines.hpp"

FLYENGINE_GRAPHICS_BEGIN_NAMESPACE

class InstanceVk;
class DeviceVk;
class SwapChainVk;
class RenderPassVk;

class VulkanFactory : public GraphicsFactory
{
public:
    virtual Buffer *             CreateBuffer();
    virtual CommandBuffer *      CreateCommandBuffer();
    virtual DescriptorSet *      CreateDescriptorSet();
    virtual DescriptorSetLayout *CreateDescriptorSetLayout();
    virtual Fence *              CreateFence();
    virtual Framebuffer *        CreateFramebuffer();
    virtual InputAssembler *     CreateInputAssembler();
    virtual PipelineLayout *     CreatePipelineLayout();
    virtual Queue *              CreateQueue();
    virtual RenderPass *         CreateRenderPass();
    virtual Sampler *            CreateSampler();
    virtual ShaderStage *        CreateShader(ShaderStageInfo shaderInfo);
    virtual Image *              CreateTexture();
    virtual Context *            CreateContext();

    VulkanFactory(platform::NativeWindow window);

    virtual bool Initialize();
    virtual bool Finalize();
    virtual void Tick(float deltaTime);

    virtual void CreateSurface();

    virtual void prepareFrame();
    virtual void beginCommand();
    virtual void endCommand();
    virtual void submitFrame();

    InstanceVk *           m_pVInstance;
    DeviceVk *             m_pDevice;
    SwapChainVk *          m_pVulkanSwapChain;
    platform::NativeWindow nativeWindow;
    VkSurfaceKHR           m_surfaceKHR;

    VkCommandPool                m_commandPool;
    std::vector<VkCommandBuffer> m_commandBuffers;

    std::vector<VkFramebuffer> swapChainFramebuffers;
    RenderPassVk *             renderPass;

private:
    void createFramebuffers();
    void createCommandPool();
    void createCommandBuffers();
};

FLYENGINE_END_NAMESPACE
