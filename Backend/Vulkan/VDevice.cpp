#include "VDevice.hpp"

namespace FlyEngine::Backend
{

FlyBuffer *VDevice::CreateBuffer(const AppInfo &info)
{
    return nullptr;
}

FlyCommandBuffer *VDevice::CreateCommandBuffer(const AppInfo &info)
{
    return nullptr;
}

FlyDescriptorSet *VDevice::CreateDescriptorSet(const AppInfo &info)
{
    return nullptr;
}

FlyDescriptorSetLayout *VDevice::CreateDescriptorSetLayout(const AppInfo &info)
{
    return nullptr;
}

FlyFence *VDevice::CreateFence(const AppInfo &info)
{
    return nullptr;
}

FlyFramebuffer *VDevice::CreateFramebuffer(const AppInfo &info)
{
    return nullptr;
}

FlyInputAssembler *VDevice::CreateInputAssembler(const AppInfo &info)
{
    return nullptr;
}

FlyPipelineLayout *VDevice::CreatePipelineLayout(const AppInfo &info)
{
    return nullptr;
}

FlyQueue *VDevice::CreateQueue(const AppInfo &info)
{
    return nullptr;
}

FlyRenderPass *VDevice::CreateRenderPass(const AppInfo &info)
{
    return nullptr;
}

FlySampler *VDevice::CreateSampler(const AppInfo &info)
{
    return nullptr;
}

FlyShader *VDevice::CreateShader(const AppInfo &info)
{
    return nullptr;
}

FlyTexture *VDevice::CreateTexture(const AppInfo &info)
{
    return nullptr;
}

void VDevice::Initialize(const AppInfo &info)
{
    deviceInfo = info;
    vContext = new VContext();
    vContext->Initialize(info);
}

void VDevice::Destroy()
{
    if (vContext) {
        vContext->Destroy();
        delete vContext;
    }
}

} // namespace FlyEngine::Backend