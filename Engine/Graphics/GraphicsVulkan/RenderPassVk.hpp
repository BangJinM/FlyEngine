#pragma once
#include "GraphicsCore/RenderPass.hpp"

#include "vulkan/vulkan.hpp"

FLYENGINE_GRAPHICS_BEGIN_NAMESPACE

class VulkanFactory;
class InstanceVk;
class DeviceVk;

class RenderPassVk : public RenderPass
{
public:
    RenderPassVk(VulkanFactory *);

    virtual void Initialize();
    virtual void Finalize();

    VkRenderPass GetVkRenderPass() const { return renderPass; }

private:
    VulkanFactory *m_pVukanFactory;
    InstanceVk    *m_pVInstance;
    DeviceVk      *m_pVulkanDevice;

    VkRenderPass renderPass;
};

FLYENGINE_END_NAMESPACE