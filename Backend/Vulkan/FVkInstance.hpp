#pragma once

#include "../Core/NonCopyable.hpp"

#include "FVkDefine.hpp"
namespace FlyEngine::Backend
{

class FVkInstance : public NonCopyable
{
public:
    explicit FVkInstance();
    ~FVkInstance();

    void Initialize();
    void Destroy();

    VkInstance &GetVkInstance() { return m_Instance; }

    void CreateInstance();
    void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo);

    void SetupDebugMessenger();

private:
    VkInstance               m_Instance = VK_NULL_HANDLE;
    VkDebugUtilsMessengerEXT debugMessenger;
};
}  // namespace FlyEngine::Backend