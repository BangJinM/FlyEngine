#include "FVkDevice.hpp"

#include "FVkBuffer.hpp"
#include "FVkCommandBuffer.hpp"
#include "FVkDescriptorSet.hpp"
#include "FVkDescriptorSetLayout.hpp"
#include "FVkFence.hpp"
#include "FVkFramebuffer.hpp"
#include "FVkInputAssembler.hpp"
#include "FVkPipelineLayout.hpp"
#include "FVkQueue.hpp"
#include "FVkRenderPass.hpp"
#include "FVkSampler.hpp"
#include "FVkShader.hpp"
#include "FVkTexture.hpp"

namespace FlyEngine::Backend
{

FlyBuffer *FVkDevice::CreateBuffer(const BufferInfo &info)
{
    FVkBuffer *vkBuffer = new FVkBuffer(this);
    vkBuffer->Initialize(info);
    return vkBuffer;
}

FlyCommandBuffer *FVkDevice::CreateCommandBuffer(const CommandBufferInfo &info)
{
    FVkCommandBuffer *vkCommandBuffer = new FVkCommandBuffer(this);
    vkCommandBuffer->Initialize(info);
    return vkCommandBuffer;
}

FlyDescriptorSet *FVkDevice::CreateDescriptorSet(const DescriptorSetInfo &info)
{
    FVkDescriptorSet *vkDescriptorSet = new FVkDescriptorSet(this);
    vkDescriptorSet->Initialize(info);
    return vkDescriptorSet;
}

FlyDescriptorSetLayout *FVkDevice::CreateDescriptorSetLayout(const DescriptorSetLayoutInfo &info)
{
    FVkDescriptorSetLayout *vkDescriptorSetLayout = new FVkDescriptorSetLayout(this);
    vkDescriptorSetLayout->Initialize(info);
    return vkDescriptorSetLayout;
}

FlyFence *FVkDevice::CreateFence(const FenceInfo &info)
{
    FVkFence *vkFence = new FVkFence(this);
    vkFence->Initialize(info);
    return vkFence;
}

FlyFramebuffer *FVkDevice::CreateFramebuffer(const FramebufferInfo &info)
{
    FVkFramebuffer *vkFramebuffer = new FVkFramebuffer(this);
    vkFramebuffer->Initialize(info);
    return vkFramebuffer;
}

FlyInputAssembler *FVkDevice::CreateInputAssembler(const InputAssemblerInfo &info)
{
    FVkInputAssembler *vkInputAssembler = new FVkInputAssembler(this);
    vkInputAssembler->Initialize(info);
    return vkInputAssembler;
}

FlyPipelineLayout *FVkDevice::CreatePipelineLayout(const PipelineLayoutInfo &info)
{
    FVkPipelineLayout *vkPipelineLayout = new FVkPipelineLayout(this);
    vkPipelineLayout->Initialize(info);
    return vkPipelineLayout;
}

FlyQueue *FVkDevice::CreateQueue(const QueueInfo &info)
{
    FVkQueue *vkQueue = new FVkQueue(this);
    vkQueue->Initialize(info);
    return vkQueue;
}

FlyRenderPass *FVkDevice::CreateRenderPass(const RenderPassInfo &info)
{
    FVkRenderPass *vkRenderPass = new FVkRenderPass(this);
    vkRenderPass->Initialize(info);
    return vkRenderPass;
}

FlySampler *FVkDevice::CreateSampler(const SamplerInfo &info)
{
    FVkSampler *vkSampler = new FVkSampler(this);
    vkSampler->Initialize(info);
    return vkSampler;
}

FlyShader *FVkDevice::CreateShader(const ShaderInfo &info)
{
    FVkShader *vkShader = new FVkShader(this);
    vkShader->Initialize(info);
    return vkShader;
}

FlyTexture *FVkDevice::CreateTexture(const TextureInfo &info)
{
    FVkTexture *vkTexture = new FVkTexture(this);
    vkTexture->Initialize(info);
    return vkTexture;
}

void FVkDevice::Initialize(const AppInfo &info)
{
    deviceInfo  = info;
    pFVkContext = new FVkContext();
    pFVkContext->Initialize(info);
}

void FVkDevice::Destroy()
{
    if (pFVkContext)
    {
        pFVkContext->Destroy();
        delete pFVkContext;
    }
}

}  // namespace FlyEngine::Backend