#pragma once

#include "GraphicsCore/Base.hpp"
#include "Platforms/NativeWindow.hpp"

#include <vulkan/vulkan.hpp>

FLYENGINE_BEGIN_NAMESPACE

class DeviceManagerImpl;

class SurfaceKHR : Base
{
public:
    SurfaceKHR();
    ~SurfaceKHR();

    virtual void Initialize(NativeWindow window);
    virtual void Finalize();

    void CreateSurface();

    NativeWindow window;
    VkSurfaceKHR surfaceKHR;
};
extern DeviceManagerImpl *g_pDeviceManager;
FLYENGINE_END_NAMESPACE