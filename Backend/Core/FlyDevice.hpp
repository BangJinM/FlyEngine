#pragma once

#include "FlyObject.hpp"

#include "FlyBuffer.hpp"
#include "FlyCommandBuffer.hpp"
#include "FlyDescriptorSet.hpp"
#include "FlyDescriptorSetLayout.hpp"
#include "FlyFence.hpp"
#include "FlyFramebuffer.hpp"
#include "FlyInputAssembler.hpp"
#include "FlyPipelineLayout.hpp"
#include "FlyQueue.hpp"
#include "FlyRenderPass.hpp"
#include "FlySampler.hpp"
#include "FlyShader.hpp"
#include "FlyTexture.hpp"

#include "../../FlyApp/AppInfo.hpp"

namespace FlyEngine::Backend
{
class FlyDevice
{
public:
    virtual FlyBuffer *             CreateBuffer(const BufferInfo &info)                           = 0;
    virtual FlyCommandBuffer *      CreateCommandBuffer(const CommandBufferInfo &info)             = 0;
    virtual FlyDescriptorSet *      CreateDescriptorSet(const DescriptorSetInfo &info)             = 0;
    virtual FlyDescriptorSetLayout *CreateDescriptorSetLayout(const DescriptorSetLayoutInfo &info) = 0;
    virtual FlyFence *              CreateFence(const FenceInfo &info)                             = 0;
    virtual FlyFramebuffer *        CreateFramebuffer(const FramebufferInfo &info)                 = 0;
    virtual FlyInputAssembler *     CreateInputAssembler(const InputAssemblerInfo &info)           = 0;
    virtual FlyPipelineLayout *     CreatePipelineLayout(const PipelineLayoutInfo &info)           = 0;
    virtual FlyQueue *              CreateQueue(const QueueInfo &info)                             = 0;
    virtual FlyRenderPass *         CreateRenderPass(const RenderPassInfo &info)                   = 0;
    virtual FlySampler *            CreateSampler(const SamplerInfo &info)                         = 0;
    virtual FlyShader *             CreateShader(const ShaderInfo &info)                           = 0;
    virtual FlyTexture *            CreateTexture(const TextureInfo &info)                         = 0;

    virtual void Initialize(const AppInfo &info) = 0;
    virtual void Tick()                          = 0;
    virtual void Destroy()                       = 0;
};
}  // namespace FlyEngine::Backend