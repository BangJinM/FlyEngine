#include "FenceVk.hpp"

#include "DeviceVk.hpp"
#include "InstanceVk.hpp"
#include "VulkanDefines.hpp"
#include "VulkanFactory.hpp"

FLYENGINE_GRAPHICS_BEGIN_NAMESPACE

FenceVk::FenceVk(VulkanFactory *factory) : m_pVukanFactory(factory)
{
    m_pVInstance    = factory->m_pVInstance;
    m_pVulkanDevice = factory->m_pDevice;
}

void FenceVk::Initialize() {}
void FenceVk::Finalize() {}

FLYENGINE_END_NAMESPACE