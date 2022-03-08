#include "SurfaceKHR.hpp"

#include "GraphicsVulkan/DeviceManagerImpl.hpp"
#include "GraphicsVulkan/VulkanFunc.hpp"

FLYENGINE_BEGIN_NAMESPACE

SurfaceKHR::SurfaceKHR(){}
SurfaceKHR::~SurfaceKHR() {}
void SurfaceKHR::Initialize(NativeWindow window)
{
    this->window = window;
    CreateSurface();
}
void SurfaceKHR::Finalize()
{
    vkDestroySurfaceKHR(g_pDeviceManager->instanceImpl->GetVkInstance(), surfaceKHR, nullptr);
}

void SurfaceKHR::CreateSurface()
{
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
    surfaceCreateInfo.hwnd      = (HWND)window.hWnd;
    CheckVk(vkCreateWin32SurfaceKHR(g_pDeviceManager->instanceImpl->GetVkInstance(), &surfaceCreateInfo, nullptr, &surfaceKHR));
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
}
FLYENGINE_END_NAMESPACE