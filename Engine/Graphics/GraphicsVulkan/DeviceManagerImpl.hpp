#pragma once

#include "GraphicsCore/DeviceManager.hpp"
#include "GraphicsVulkan/Device.hpp"
#include "GraphicsVulkan/Instance.hpp"
#include "GraphicsVulkan/ShaderImpl.hpp"
#include "GraphicsVulkan/SurfaceKHR.hpp"

FLYENGINE_BEGIN_NAMESPACE

struct DebugDetails
{
    std::vector<const char *> validationLayers       = {"VK_LAYER_LUNARG_standard_validation"};
    std::vector<const char *> deviceExtensions       = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};
    bool                      enableValidationLayers = true;
};

class DeviceManagerImpl : public DeviceManager
{
public:
    virtual Shader *CreateShader(ShaderInfo info);

private:
    virtual bool Initialize();

public:
    bool Initialize(NativeWindow window);

    virtual bool Finalize();

    virtual void Tick(float deltaTime);

    DeviceManagerImpl();
    ~DeviceManagerImpl();

    Instance *   instanceImpl;
    SurfaceKHR * surfaceKHR;
    DebugDetails debugDetails;
    Device *     device;
};

FLYENGINE_END_NAMESPACE