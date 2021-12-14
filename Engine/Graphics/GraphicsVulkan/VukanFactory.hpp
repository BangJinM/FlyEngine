#pragma once
#include "GraphicsCore/GraphicsDefine.hpp"
#include "GraphicsCore/GraphicsFactory.hpp"

#include "Platforms/NativeWindow.hpp"
#include "VulkanDefines.hpp"

FLYENGINE_GRAPHICS_BEGIN_NAMESPACE

class VulkanInstance;
class VulkanDevice;

class VulkanFactory : public GraphicsFactory
{
public:
    virtual GBuffer              *CreateBuffer();
    virtual GCommandBuffer       *CreateCommandBuffer();
    virtual GDescriptorSet       *CreateDescriptorSet();
    virtual GDescriptorSetLayout *CreateDescriptorSetLayout();
    virtual GFence               *CreateFence();
    virtual GFramebuffer         *CreateFramebuffer();
    virtual GInputAssembler      *CreateInputAssembler();
    virtual GPipelineLayout      *CreatePipelineLayout();
    virtual GQueue               *CreateQueue();
    virtual GRenderPass          *CreateRenderPass();
    virtual GSampler             *CreateSampler();
    virtual GShader              *CreateShader();
    virtual GTexture             *CreateTexture();
    virtual GContext             *CreateContext();

    VulkanFactory(platform::NativeWindow window);

    virtual bool Initialize();
    virtual bool Finalize();
    virtual void Tick(float deltaTime);

    VulkanInstance             *m_pVInstance;
    VulkanDevice          *m_pDevice;
    platform::NativeWindow nativeWindow;
    VkSurfaceKHR           m_surfaceKHR;
};

FLYENGINE_END_NAMESPACE
