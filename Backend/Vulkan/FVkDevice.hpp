#pragma once

#include "../Core/FlyDevice.hpp"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "../../FlyApp/AppInfo.hpp"
#include "FVkContext.hpp"

namespace FlyEngine::Backend
{

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

    virtual void Initialize(const AppInfo &info) override;
    virtual void Tick() override;
    virtual void Destroy() override;

    FVkContext *GetContext() { return pFVkContext; }

private:
    FVkContext *pFVkContext;
    AppInfo     deviceInfo;
};

}  // namespace FlyEngine::Backend