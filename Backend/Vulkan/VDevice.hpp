#pragma once

#include "../Core/FlyDevice.hpp"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "../../FlyApp/AppInfo.hpp"
#include "VContext.hpp"

namespace FlyEngine::Backend
{

class VDevice : public FlyDevice
{

public:
    virtual FlyBuffer *             CreateBuffer(const AppInfo &info) override;
    virtual FlyCommandBuffer *      CreateCommandBuffer(const AppInfo &info) override;
    virtual FlyDescriptorSet *      CreateDescriptorSet(const AppInfo &info) override;
    virtual FlyDescriptorSetLayout *CreateDescriptorSetLayout(const AppInfo &info) override;
    virtual FlyFence *              CreateFence(const AppInfo &info) override;
    virtual FlyFramebuffer *        CreateFramebuffer(const AppInfo &info) override;
    virtual FlyInputAssembler *     CreateInputAssembler(const AppInfo &info) override;
    virtual FlyPipelineLayout *     CreatePipelineLayout(const AppInfo &info) override;
    virtual FlyQueue *              CreateQueue(const AppInfo &info) override;
    virtual FlyRenderPass *         CreateRenderPass(const AppInfo &info) override;
    virtual FlySampler *            CreateSampler(const AppInfo &info) override;
    virtual FlyShader *             CreateShader(const AppInfo &info) override;
    virtual FlyTexture *            CreateTexture(const AppInfo &info) override;

    virtual void Initialize(const AppInfo &info) override;
    virtual void Destroy() override;

private:
    VContext *vContext;
    AppInfo   deviceInfo;
};

} // namespace FlyEngine::Backend