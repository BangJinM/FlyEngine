#pragma once

#include "BackendEnum.hpp"
#include "Core/FlyDevice.hpp"

#ifdef BACKEND_VULKAN
#    include "Vulkan/FVkDevice.hpp"
#endif

namespace FlyEngine::Backend
{

static FlyDevice *CreateDevice(BackendFlag backend = BackendFlag::Vulkan)
{
    switch (backend)
    {
        case BackendFlag::Vulkan:
#ifdef BACKEND_VULKAN
            return new FVkDevice();
#else
            return nullptr;
#endif
            break;
        default: break;
    }
    return nullptr;
}

}  // namespace FlyEngine::Backend