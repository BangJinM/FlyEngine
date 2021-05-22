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
    virtual FlyBuffer *             CreateBuffer(const AppInfo &info) = 0;
    virtual FlyCommandBuffer *      CreateCommandBuffer(const AppInfo &info) = 0;
    virtual FlyDescriptorSet *      CreateDescriptorSet(const AppInfo &info) = 0;
    virtual FlyDescriptorSetLayout *CreateDescriptorSetLayout(const AppInfo &info) = 0;
    virtual FlyFence *              CreateFence(const AppInfo &info) = 0;
    virtual FlyFramebuffer *        CreateFramebuffer(const AppInfo &info) = 0;
    virtual FlyInputAssembler *     CreateInputAssembler(const AppInfo &info) = 0;
    virtual FlyPipelineLayout *     CreatePipelineLayout(const AppInfo &info) = 0;
    virtual FlyQueue *              CreateQueue(const AppInfo &info) = 0;
    virtual FlyRenderPass *         CreateRenderPass(const AppInfo &info) = 0;
    virtual FlySampler *            CreateSampler(const AppInfo &info) = 0;
    virtual FlyShader *             CreateShader(const AppInfo &info) = 0;
    virtual FlyTexture *            CreateTexture(const AppInfo &info) = 0;

    virtual void Initialize(const AppInfo &info) = 0;
    virtual void Destroy() = 0;
};
} // namespace FlyEngine::Backend