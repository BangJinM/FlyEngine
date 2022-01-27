#pragma once

#include "GraphicsCore/Base.hpp"
#include "GraphicsCore/GraphicsDefine.hpp"

#include <vulkan/vulkan.h>
#include <vector>

FLYENGINE_GRAPHICS_BEGIN_NAMESPACE

class InstanceVk : public Base
{
public:
    virtual void Initialize();
    virtual void Finalize();

    virtual VkInstance &GetVkInstance() { return m_Instance; }

    void CreateInstance();
    void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo);

    void SetupDebugMessenger();

    bool                      CheckValidationLayerSupport();
    std::vector<const char *> GetRequiredExtensions();

private:
    VkInstance               m_Instance = VK_NULL_HANDLE;
    VkDebugUtilsMessengerEXT debugMessenger;
};

FLYENGINE_END_NAMESPACE