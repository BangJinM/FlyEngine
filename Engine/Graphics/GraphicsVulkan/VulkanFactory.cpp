#include "VulkanFactory.hpp"

#include "VulkanBuffer.hpp"
#include "VulkanCommandBuffer.hpp"
#include "VulkanContext.hpp"
#include "VulkanDescriptorSet.hpp"
#include "VulkanDescriptorSetLayout.hpp"
#include "VulkanDevice.hpp"
#include "VulkanFence.hpp"
#include "VulkanFramebuffer.hpp"
#include "VulkanInputAssembler.hpp"
#include "VulkanInstance.hpp"
#include "VulkanPipelineLayout.hpp"
#include "VulkanQueue.hpp"
#include "VulkanRenderPass.hpp"
#include "VulkanSampler.hpp"
#include "VulkanShader.hpp"
#include "VulkanSwapChain.hpp"
#include "VulkanTexture.hpp"

#include "Platforms/NativeWindow.hpp"

FLYENGINE_GRAPHICS_BEGIN_NAMESPACE

GBuffer *VulkanFactory::CreateBuffer()
{
    auto vBuffer = new VulkanBuffer();
    vBuffer->Initialize();
    return vBuffer;
}
GCommandBuffer *VulkanFactory::CreateCommandBuffer()
{
    auto vCommandBuffer = new VulkanCommandBuffer();
    vCommandBuffer->Initialize();
    return vCommandBuffer;
}
GDescriptorSet *VulkanFactory::CreateDescriptorSet()
{
    auto vDescriptorSet = new VulkanDescriptorSet();
    vDescriptorSet->Initialize();
    return vDescriptorSet;
}
GDescriptorSetLayout *VulkanFactory::CreateDescriptorSetLayout()
{
    auto vDescriptorSetLayout = new VulkanDescriptorSetLayout();
    vDescriptorSetLayout->Initialize();
    return vDescriptorSetLayout;
}
GFence *VulkanFactory::CreateFence()
{
    auto vFence = new VulkanFence();
    vFence->Initialize();
    return vFence;
}
GFramebuffer *VulkanFactory::CreateFramebuffer()
{
    auto vFramebuffer = new VulkanFramebuffer();
    vFramebuffer->Initialize();
    return vFramebuffer;
}
GInputAssembler *VulkanFactory::CreateInputAssembler()
{
    auto vInputAssembler = new VulkanInputAssembler();
    vInputAssembler->Initialize();
    return vInputAssembler;
}
GPipelineLayout *VulkanFactory::CreatePipelineLayout()
{
    auto vPipelineLayout = new VulkanPipelineLayout();
    vPipelineLayout->Initialize();
    return vPipelineLayout;
}
GQueue *VulkanFactory::CreateQueue()
{
    auto vQueue = new VulkanQueue();
    vQueue->Initialize();
    return vQueue;
}
GRenderPass *VulkanFactory::CreateRenderPass()
{
    auto vRenderPass = new VulkanRenderPass();
    vRenderPass->Initialize();
    return vRenderPass;
}
GSampler *VulkanFactory::CreateSampler()
{
    auto vSampler = new VulkanSampler();
    vSampler->Initialize();
    return vSampler;
}
GShader *VulkanFactory::CreateShader()
{
    auto vShader = new VulkanShader();
    vShader->Initialize();
    return vShader;
}
GTexture *VulkanFactory::CreateTexture()
{
    auto vTexture = new VulkanTexture();
    vTexture->Initialize();
    return vTexture;
}

GContext *VulkanFactory::CreateContext()
{
    auto vContext = new VulkanContext();
    vContext->Initialize();
    return vContext;
}

VulkanFactory::VulkanFactory(platform::NativeWindow window)
{
    nativeWindow = window;
}

bool VulkanFactory::Initialize()
{
    m_pVInstance = new VulkanInstance();
    m_pVInstance->Initialize();

#if defined(VK_USE_PLATFORM_ANDROID_KHR)
    VkAndroidSurfaceCreateInfoKHR surfaceCreateInfo{VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR};
    surfaceCreateInfo.window = (ANativeWindow *)_windowHandle;
    VK_CHECK(vkCreateAndroidSurfaceKHR(_gpuContext->vkInstance, &surfaceCreateInfo, nullptr, &_gpuContext->vkSurface));

    EventDispatcher::addCustomEventListener(EVENT_DESTROY_WINDOW, [=](const CustomEvent &) -> void {
        if (_gpuContext && _gpuContext->vkSurface != VK_NULL_HANDLE)
        {

            CCVKQueue *queue = (CCVKQueue *)device->getQueue();

            uint fenceCount = device->gpuFencePool()->size();
            if (fenceCount)
            {
                VK_CHECK(vkWaitForFences(device->gpuDevice()->vkDevice, fenceCount, device->gpuFencePool()->data(), VK_TRUE, DEFAULT_TIMEOUT));
            }

            device->destroySwapchain();
            device->_swapchainReady = false;

            vkDestroySurfaceKHR(_gpuContext->vkInstance, _gpuContext->vkSurface, nullptr);
            _gpuContext->vkSurface = VK_NULL_HANDLE;
        }
    });

    EventDispatcher::addCustomEventListener(EVENT_RECREATE_WINDOW, [=](const CustomEvent &event) -> void {
        _windowHandle = (uintptr_t)event.args->ptrVal;

        if (_gpuContext && _gpuContext->vkSurface == VK_NULL_HANDLE)
        {
            VkAndroidSurfaceCreateInfoKHR surfaceCreateInfo{VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR};
            surfaceCreateInfo.window = (ANativeWindow *)_windowHandle;
            VK_CHECK(vkCreateAndroidSurfaceKHR(_gpuContext->vkInstance, &surfaceCreateInfo, nullptr, &_gpuContext->vkSurface));

            device->checkSwapchainStatus();
        }
    });
#elif defined(VK_USE_PLATFORM_WIN32_KHR)
    VkWin32SurfaceCreateInfoKHR surfaceCreateInfo{VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR};
    surfaceCreateInfo.hinstance = (HINSTANCE)GetModuleHandle(0);
    surfaceCreateInfo.hwnd      = (HWND)nativeWindow.hWnd;
    vkCreateWin32SurfaceKHR(m_pVInstance->GetVkInstance(), &surfaceCreateInfo, nullptr, &m_surfaceKHR);
#elif defined(VK_USE_PLATFORM_METAL_EXT)
    VkMetalSurfaceCreateInfoEXT surfaceCreateInfo{VK_STRUCTURE_TYPE_METAL_SURFACE_CREATE_INFO_EXT};
    surfaceCreateInfo.pLayer = (CAMetalLayer *)_windowHandle;
    VK_CHECK(vkCreateMetalSurfaceEXT(_gpuContext->vkInstance, &surfaceCreateInfo, nullptr, &_gpuContext->vkSurface));
#elif defined(VK_USE_PLATFORM_WAYLAND_KHR)
    VkWaylandSurfaceCreateInfoKHR surfaceCreateInfo{VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR};
    surfaceCreateInfo.display = nullptr;  // TODO
    surfaceCreateInfo.surface = (wl_surface *)_windowHandle;
    VK_CHECK(vkCreateWaylandSurfaceKHR(_gpuContext->vkInstance, &surfaceCreateInfo, nullptr, &_gpuContext->vkSurface));
#elif defined(VK_USE_PLATFORM_XCB_KHR)
    VkXcbSurfaceCreateInfoKHR surfaceCreateInfo{VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR};
    surfaceCreateInfo.connection = nullptr;  // TODO
    surfaceCreateInfo.window     = (xcb_window_t)_windowHandle;
    VK_CHECK(vkCreateXcbSurfaceKHR(_gpuContext->vkInstance, &surfaceCreateInfo, nullptr, &_gpuContext->vkSurface));
#else
#    pragma error Platform not supported
#endif

    m_pDevice = new VulkanDevice(this);
    m_pDevice->Initialize();

    m_pVulkanSwapChain = new VulkanSwapChain(this);
    m_pVulkanSwapChain->Initialize();

    return true;
}
bool VulkanFactory::Finalize()
{
    m_pDevice->Finalize();
    m_pVInstance->Finalize();
    return true;
}
void VulkanFactory::Tick(float deltaTime) {}

FLYENGINE_END_NAMESPACE