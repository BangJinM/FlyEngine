#pragma once
#include "GraphicsCore/Fence.hpp"

FLYENGINE_GRAPHICS_BEGIN_NAMESPACE

class VulkanFactory;
class InstanceVk;
class DeviceVk;

class FenceVk : public Fence
{
public:
    FenceVk(VulkanFactory *);

    virtual void Initialize();
    virtual void Finalize();

private:
    VulkanFactory *m_pVukanFactory;
    InstanceVk    *m_pVInstance;
    DeviceVk      *m_pVulkanDevice;
};

FLYENGINE_END_NAMESPACE