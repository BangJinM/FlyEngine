#include "VulkanFactory.hpp"

#include <iostream>

#include "BufferVk.hpp"
#include "CommandBufferVk.hpp"
#include "ContextVk.hpp"
#include "DescriptorSetLayoutVk.hpp"
#include "DescriptorSetVk.hpp"
#include "DeviceVk.hpp"
#include "FenceVk.hpp"
#include "FramebufferVk.hpp"
#include "ImageVk.hpp"
#include "InputAssemblerVk.hpp"
#include "InstanceVk.hpp"
#include "PipelineLayoutVk.hpp"
#include "QueueVk.hpp"
#include "RenderPassVk.hpp"
#include "SamplerVk.hpp"
#include "ShaderStageVk.hpp"
#include "SwapChainVk.hpp"

#include "Platforms/NativeWindow.hpp"

FLYENGINE_GRAPHICS_BEGIN_NAMESPACE

Buffer *VulkanFactory::CreateBuffer()
{
    auto vBuffer = new BufferVk();
    vBuffer->Initialize();
    return vBuffer;
}
CommandBuffer *VulkanFactory::CreateCommandBuffer()
{
    auto vCommandBuffer = new CommandBufferVk();
    vCommandBuffer->Initialize();
    return vCommandBuffer;
}
DescriptorSet *VulkanFactory::CreateDescriptorSet()
{
    auto vDescriptorSet = new DescriptorSetVk();
    vDescriptorSet->Initialize();
    return vDescriptorSet;
}
DescriptorSetLayout *VulkanFactory::CreateDescriptorSetLayout()
{
    auto vDescriptorSetLayout = new DescriptorSetLayoutVk();
    vDescriptorSetLayout->Initialize();
    return vDescriptorSetLayout;
}
Fence *VulkanFactory::CreateFence()
{
    auto vFence = new FenceVk(this);
    vFence->Initialize();
    return vFence;
}
Framebuffer *VulkanFactory::CreateFramebuffer()
{
    auto vFramebuffer = new FramebufferVk();
    vFramebuffer->Initialize();
    return vFramebuffer;
}
InputAssembler *VulkanFactory::CreateInputAssembler()
{
    auto vInputAssembler = new InputAssemblerVk();
    vInputAssembler->Initialize();
    return vInputAssembler;
}
PipelineLayout *VulkanFactory::CreatePipelineLayout()
{
    auto vPipelineLayout = new PipelineLayoutVk();
    vPipelineLayout->Initialize();
    return vPipelineLayout;
}
Queue *VulkanFactory::CreateQueue()
{
    auto vQueue = new QueueVk();
    vQueue->Initialize();
    return vQueue;
}
RenderPass *VulkanFactory::CreateRenderPass()
{
    auto vRenderPass = new RenderPassVk(this);
    vRenderPass->Initialize();
    return vRenderPass;
}
Sampler *VulkanFactory::CreateSampler()
{
    auto vSampler = new SamplerVk();
    vSampler->Initialize();
    return vSampler;
}
ShaderStage *VulkanFactory::CreateShader(ShaderStageInfo shaderInfo)
{
    auto vShader = new ShaderStageVk(this, shaderInfo);
    vShader->Initialize();
    return vShader;
}
Image *VulkanFactory::CreateTexture()
{
    auto vTexture = new ImageVk();
    vTexture->Initialize();
    return vTexture;
}

Context *VulkanFactory::CreateContext()
{
    auto vContext = new ContextVk();
    vContext->Initialize();
    return vContext;
}

VulkanFactory::VulkanFactory(platform::NativeWindow window)
{
    nativeWindow = window;
}

bool VulkanFactory::Initialize()
{
    m_pVInstance = new InstanceVk();
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

    m_pDevice = new DeviceVk(this);
    m_pDevice->Initialize();

    m_pVulkanSwapChain = new SwapChainVk(this);
    m_pVulkanSwapChain->Initialize();

    renderPass = (RenderPassVk *)this->CreateRenderPass();

    createFramebuffers();
    createCommandPool();
    createCommandBuffers();

    return true;
}
bool VulkanFactory::Finalize()
{
    m_pDevice->Finalize();
    m_pVInstance->Finalize();
    return true;
}
void VulkanFactory::Tick(float deltaTime) {}

void VulkanFactory::createFramebuffers()
{
    auto imageCount      = m_pVulkanSwapChain->GetImageCount();
    auto swapChainExtent = m_pVulkanSwapChain->GetSwapChainExtent();
    swapChainFramebuffers.resize(imageCount);

    for (size_t i = 0; i < imageCount; i++)
    {
        VkImageView attachments[] = {m_pVulkanSwapChain->getImageView(i)};

        VkFramebufferCreateInfo framebufferInfo{};
        framebufferInfo.sType           = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo.renderPass      = renderPass->GetVkRenderPass();
        framebufferInfo.attachmentCount = 1;
        framebufferInfo.pAttachments    = attachments;
        framebufferInfo.width           = swapChainExtent.width;
        framebufferInfo.height          = swapChainExtent.height;
        framebufferInfo.layers          = 1;

        if (vkCreateFramebuffer(m_pDevice->GetLogicalDevice(), &framebufferInfo, nullptr, &swapChainFramebuffers[i]) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create framebuffer!");
        }
    }
}

void VulkanFactory::createCommandPool()
{
    QueueFamilyIndices queueFamilyIndices = m_pDevice->FindQueueFamilies(m_pDevice->GetVkPhysicalDevice());

    VkCommandPoolCreateInfo poolInfo{};
    poolInfo.sType            = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();

    if (vkCreateCommandPool(m_pDevice->GetLogicalDevice(), &poolInfo, nullptr, &m_commandPool) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create command pool!");
    }
}

void VulkanFactory::createCommandBuffers()
{
    auto swapChainExtent = m_pVulkanSwapChain->GetSwapChainExtent();

    m_commandBuffers.resize(swapChainFramebuffers.size());

    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType              = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool        = m_commandPool;
    allocInfo.level              = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = (uint32_t)m_commandBuffers.size();

    if (vkAllocateCommandBuffers(m_pDevice->GetLogicalDevice(), &allocInfo, m_commandBuffers.data()) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to allocate command buffers!");
    }
}

void VulkanFactory::prepareFrame()
{
    if (!m_pVulkanSwapChain->Acquire())
    {
        std::runtime_error("This shouldn't happen");
    }
    VkFence fence = m_pVulkanSwapChain->GetFence();

    VkResult result{VK_SUCCESS};
    do
    {
        result = vkWaitForFences(m_pDevice->GetLogicalDevice(), 1, &fence, VK_TRUE, UINT64_MAX);
    } while (result == VK_TIMEOUT);
    if (result != VK_SUCCESS)
    {  // This allows Aftermath to do things and later assert below
#ifdef _WIN32
        Sleep(1000);
#else
        usleep(1000);
#endif
    }
    assert(result == VK_SUCCESS);
}

void VulkanFactory::beginCommand()
{
    uint32_t imageIndex = m_pVulkanSwapChain->getActiveImageIndex();
    auto     cmdBuf     = m_commandBuffers[imageIndex];

    VkCommandBufferBeginInfo beginInfo{VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO};
    beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    vkBeginCommandBuffer(cmdBuf, &beginInfo);
}
void VulkanFactory::endCommand()
{
    uint32_t imageIndex = m_pVulkanSwapChain->getActiveImageIndex();
    auto     cmdBuf     = m_commandBuffers[imageIndex];
    // Submit for display
    vkEndCommandBuffer(cmdBuf);
}

void VulkanFactory::submitFrame()
{
    uint32_t imageIndex = m_pVulkanSwapChain->getActiveImageIndex();

    VkFence fence = m_pVulkanSwapChain->GetFence();
    vkResetFences(m_pDevice->GetLogicalDevice(), 1, &fence);

    // In case of using NVLINK
    bool                          m_useNvlink = false;
    const uint32_t                deviceMask  = m_useNvlink ? 0b0000'0011 : 0b0000'0001;
    const std::array<uint32_t, 2> deviceIndex = {0, 1};

    VkDeviceGroupSubmitInfo deviceGroupSubmitInfo{VK_STRUCTURE_TYPE_DEVICE_GROUP_SUBMIT_INFO_KHR};
    deviceGroupSubmitInfo.waitSemaphoreCount            = 1;
    deviceGroupSubmitInfo.commandBufferCount            = 1;
    deviceGroupSubmitInfo.pCommandBufferDeviceMasks     = &deviceMask;
    deviceGroupSubmitInfo.signalSemaphoreCount          = m_useNvlink ? 2 : 1;
    deviceGroupSubmitInfo.pSignalSemaphoreDeviceIndices = deviceIndex.data();
    deviceGroupSubmitInfo.pWaitSemaphoreDeviceIndices   = deviceIndex.data();

    VkSemaphore semaphoreRead  = m_pVulkanSwapChain->getActiveReadSemaphore();
    VkSemaphore semaphoreWrite = m_pVulkanSwapChain->getActiveWrittenSemaphore();

    // Pipeline stage at which the queue submission will wait (via pWaitSemaphores)
    const VkPipelineStageFlags waitStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    // The submit info structure specifies a command buffer queue submission batch
    VkSubmitInfo submitInfo{VK_STRUCTURE_TYPE_SUBMIT_INFO};
    submitInfo.pWaitDstStageMask    = &waitStageMask;   // Pointer to the list of pipeline stages that the semaphore waits will occur at
    submitInfo.pWaitSemaphores      = &semaphoreRead;   // Semaphore(s) to wait upon before the submitted command buffer starts executing
    submitInfo.waitSemaphoreCount   = 1;                // One wait semaphore
    submitInfo.pSignalSemaphores    = &semaphoreWrite;  // Semaphore(s) to be signaled when command buffers have completed
    submitInfo.signalSemaphoreCount = 1;                // One signal semaphore
    submitInfo.pCommandBuffers      = &m_commandBuffers[imageIndex];  // Command buffers(s) to execute in this batch (submission)
    submitInfo.commandBufferCount   = 1;                              // One command buffer
    submitInfo.pNext                = &deviceGroupSubmitInfo;

    // Submit to the graphics queue passing a wait fence
    vkQueueSubmit(m_pDevice->m_graphicsQueue, 1, &submitInfo, fence);

    // Presenting frame
    m_pVulkanSwapChain->QueuePresent(m_pDevice->m_presentQueue);
}

FLYENGINE_END_NAMESPACE