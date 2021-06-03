#include "FVkDevice.hpp"

#include <iostream>
#include <set>
#include <string>

#include "../../FlyApp/WindowBase.hpp"
#include "FVkBuffer.hpp"
#include "FVkCommandBuffer.hpp"
#include "FVkDescriptorSet.hpp"
#include "FVkDescriptorSetLayout.hpp"
#include "FVkFence.hpp"
#include "FVkFramebuffer.hpp"
#include "FVkFunc.hpp"
#include "FVkInputAssembler.hpp"
#include "FVkInstance.hpp"
#include "FVkLogicalDevice.hpp"
#include "FVkPhysicalDevice.hpp"
#include "FVkPipelineLayout.hpp"
#include "FVkQueue.hpp"
#include "FVkRenderPass.hpp"
#include "FVkSampler.hpp"
#include "FVkShader.hpp"
#include "FVkSwapChain.hpp"
#include "FVkTexture.hpp"
#include "File/File.hpp"

namespace FlyEngine::Backend
{

FlyBuffer *FVkDevice::CreateBuffer(const BufferInfo &info)
{
    FVkBuffer *vkBuffer = new FVkBuffer(this);
    vkBuffer->Initialize(info);
    return vkBuffer;
}

FlyCommandBuffer *FVkDevice::CreateCommandBuffer(const CommandBufferInfo &info)
{
    FVkCommandBuffer *vkCommandBuffer = new FVkCommandBuffer(this);
    vkCommandBuffer->Initialize(info);
    return vkCommandBuffer;
}

FlyDescriptorSet *FVkDevice::CreateDescriptorSet(const DescriptorSetInfo &info)
{
    FVkDescriptorSet *vkDescriptorSet = new FVkDescriptorSet(this);
    vkDescriptorSet->Initialize(info);
    return vkDescriptorSet;
}

FlyDescriptorSetLayout *FVkDevice::CreateDescriptorSetLayout(const DescriptorSetLayoutInfo &info)
{
    FVkDescriptorSetLayout *vkDescriptorSetLayout = new FVkDescriptorSetLayout(this);
    vkDescriptorSetLayout->Initialize(info);
    return vkDescriptorSetLayout;
}

FlyFence *FVkDevice::CreateFence(const FenceInfo &info)
{
    FVkFence *vkFence = new FVkFence(this);
    vkFence->Initialize(info);
    return vkFence;
}

FlyFramebuffer *FVkDevice::CreateFramebuffer(const FramebufferInfo &info)
{
    FVkFramebuffer *vkFramebuffer = new FVkFramebuffer(this);
    vkFramebuffer->Initialize(info);
    return vkFramebuffer;
}

FlyInputAssembler *FVkDevice::CreateInputAssembler(const InputAssemblerInfo &info)
{
    FVkInputAssembler *vkInputAssembler = new FVkInputAssembler(this);
    vkInputAssembler->Initialize(info);
    return vkInputAssembler;
}

FlyPipelineLayout *FVkDevice::CreatePipelineLayout(const PipelineLayoutInfo &info)
{
    FVkPipelineLayout *vkPipelineLayout = new FVkPipelineLayout(this);
    vkPipelineLayout->Initialize(info);
    return vkPipelineLayout;
}

FlyQueue *FVkDevice::CreateQueue(const QueueInfo &info)
{
    FVkQueue *vkQueue = new FVkQueue(this);
    vkQueue->Initialize(info);
    return vkQueue;
}

FlyRenderPass *FVkDevice::CreateRenderPass(const RenderPassInfo &info)
{
    FVkRenderPass *vkRenderPass = new FVkRenderPass(this);
    vkRenderPass->Initialize(info);
    return vkRenderPass;
}

FlySampler *FVkDevice::CreateSampler(const SamplerInfo &info)
{
    FVkSampler *vkSampler = new FVkSampler(this);
    vkSampler->Initialize(info);
    return vkSampler;
}

FlyShader *FVkDevice::CreateShader(const ShaderInfo &info)
{
    FVkShader *vkShader = new FVkShader(this);
    vkShader->Initialize(info);
    return vkShader;
}

FlyTexture *FVkDevice::CreateTexture(const TextureInfo &info)
{
    FVkTexture *vkTexture = new FVkTexture(this);
    vkTexture->Initialize(info);
    return vkTexture;
}

void FVkDevice::Initialize(WindowBase *window)
{
    p_Window = window;

    p_FVkInstance = new FVkInstance();
    p_FVkInstance->Initialize();

    p_Window->CreateSurface(p_FVkInstance->GetVkInstance(), &surface);

    p_FVkPhysicalDevice = new FVkPhysicalDevice(p_FVkInstance, this);
    p_FVkPhysicalDevice->Initialize();

    p_FVkLogicalDevice = new FVkLogicalDevice(this, p_FVkPhysicalDevice);
    p_FVkLogicalDevice->Initialize();

    p_FVkSwapChain = new FVkSwapChain(p_FVkLogicalDevice, p_FVkPhysicalDevice, this, p_Window);
    p_FVkSwapChain->Initialize();

    createGlobalRenderPass();
    createGraphicsPipeline();
    createFramebuffers();
    createCommandPool();
    createCommandBuffers();
    createSyncObjects();
}

void FVkDevice::Destroy()
{
    p_FVkLogicalDevice->WaitIdle();
    cleanupSwapChain();

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
    {
        vkDestroySemaphore(GetVkDevice(), renderFinishedSemaphores[i], nullptr);
        vkDestroySemaphore(GetVkDevice(), imageAvailableSemaphores[i], nullptr);
        vkDestroyFence(GetVkDevice(), inFlightFences[i], nullptr);
    }

    vkDestroyCommandPool(GetVkDevice(), commandPool, nullptr);

    vkDestroyDevice(GetVkDevice(), nullptr);

    p_FVkPhysicalDevice->Destroy();

    vkDestroySurfaceKHR(p_FVkInstance->GetVkInstance(), surface, nullptr);

    p_FVkInstance->Destroy();
}

VkDevice &FVkDevice::GetVkDevice()
{
    return p_FVkLogicalDevice->GetLogicalDevice();
}

uint32_t FVkDevice::FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties)
{
    VkPhysicalDeviceMemoryProperties memProperties;
    vkGetPhysicalDeviceMemoryProperties(p_FVkPhysicalDevice->GetVkPhysicalDevice(), &memProperties);

    for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++)
    {
        if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties)
        {
            return i;
        }
    }

    throw std::runtime_error("failed to find suitable memory type!");
}

VkCommandBuffer FVkDevice::BeginSingleTimeCommands()
{
    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType              = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.level              = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandPool        = commandPool;
    allocInfo.commandBufferCount = 1;

    VkCommandBuffer commandBuffer;
    vkAllocateCommandBuffers(GetVkDevice(), &allocInfo, &commandBuffer);

    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    vkBeginCommandBuffer(commandBuffer, &beginInfo);

    return commandBuffer;
}

void FVkDevice::EndSingleTimeCommands(VkCommandBuffer commandBuffer)
{
    vkEndCommandBuffer(commandBuffer);

    VkSubmitInfo submitInfo{};
    submitInfo.sType              = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers    = &commandBuffer;

    vkQueueSubmit(p_FVkLogicalDevice->GetGraphicsQueue(), 1, &submitInfo, VK_NULL_HANDLE);
    vkQueueWaitIdle(p_FVkLogicalDevice->GetGraphicsQueue());

    vkFreeCommandBuffers(GetVkDevice(), commandPool, 1, &commandBuffer);
}

FVkInstance *FVkDevice::GetFVkInstance()
{
    return p_FVkInstance;
}

FVkPhysicalDevice *FVkDevice::GetFVkPhysicalDevice()
{
    return p_FVkPhysicalDevice;
}

FVkLogicalDevice *FVkDevice::GetFVkLogicalDevice()
{
    return p_FVkLogicalDevice;
}

FVkSwapChain *FVkDevice::GetFVkSwapChain()
{
    return p_FVkSwapChain;
}

WindowBase *FVkDevice::GetWindowBase()
{
    return p_Window;
}

void FVkDevice::cleanupSwapChain()

{
    for (auto framebuffer : swapChainFramebuffers)
    {
        vkDestroyFramebuffer(p_FVkLogicalDevice->GetLogicalDevice(), framebuffer, nullptr);
    }

    vkFreeCommandBuffers(GetVkDevice(), commandPool, static_cast<uint32_t>(commandBuffers.size()), commandBuffers.data());

    vkDestroyPipeline(GetVkDevice(), graphicsPipeline, nullptr);
    vkDestroyPipelineLayout(GetVkDevice(), pipelineLayout, nullptr);

    renderPass->Destroy();
    p_FVkSwapChain->Destroy();
}

void FVkDevice::recreateSwapChain()
{
    p_Window->WaitForNewWindowSize();
    p_FVkLogicalDevice->WaitIdle();

    cleanupSwapChain();

    p_FVkSwapChain->Initialize();

    createGlobalRenderPass();
    createFramebuffers();
    createGraphicsPipeline();
    createCommandBuffers();

    imagesInFlight.resize(p_FVkSwapChain->GetImageViews().size(), VK_NULL_HANDLE);
}

void FVkDevice::createGlobalRenderPass()
{
    RenderPassInfo info;
    renderPass = (FVkRenderPass *)CreateRenderPass(info);
}

void FVkDevice::createGraphicsPipeline()
{
    File::IFile *file = File::File::GetFileInstance();

    auto vertShaderCode = file->SyncOpenAndReadBinary("Private/Shader/sampler.vert.spv");
    auto fragShaderCode = file->SyncOpenAndReadBinary("Private/Shader/sampler.frag.spv");

    char *vertShaderCodeStr = reinterpret_cast<char *>(vertShaderCode.GetData());
    char *fragShaderCodeStr = reinterpret_cast<char *>(fragShaderCode.GetData());

    ShaderInfo info;
    info.name = "main";
    info.shaderStageList.push_back({ShaderStageFlagBit::VERTEX, std::string(vertShaderCodeStr, vertShaderCodeStr + vertShaderCode.GetDataSize())});
    info.shaderStageList.push_back({ShaderStageFlagBit::FRAGMENT, std::string(fragShaderCodeStr, fragShaderCodeStr + fragShaderCode.GetDataSize())});
    auto shader       = (FVkShader *)CreateShader(info);
    auto shaderStages = shader->GetStages();

    VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
    vertexInputInfo.sType                           = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertexInputInfo.vertexBindingDescriptionCount   = 0;
    vertexInputInfo.vertexAttributeDescriptionCount = 0;

    VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
    inputAssembly.sType                  = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    inputAssembly.topology               = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    inputAssembly.primitiveRestartEnable = VK_FALSE;

    auto swapChainExtent = p_FVkSwapChain->GetSwapChainExtent();

    VkViewport viewport{};
    viewport.x        = 0.0f;
    viewport.y        = 0.0f;
    viewport.width    = (float)swapChainExtent.width;
    viewport.height   = (float)swapChainExtent.height;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;

    VkRect2D scissor{};
    scissor.offset = {0, 0};
    scissor.extent = swapChainExtent;

    VkPipelineViewportStateCreateInfo viewportState{};
    viewportState.sType         = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewportState.viewportCount = 1;
    viewportState.pViewports    = &viewport;
    viewportState.scissorCount  = 1;
    viewportState.pScissors     = &scissor;

    VkPipelineRasterizationStateCreateInfo rasterizer{};
    rasterizer.sType                   = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterizer.depthClampEnable        = VK_FALSE;
    rasterizer.rasterizerDiscardEnable = VK_FALSE;
    rasterizer.polygonMode             = VK_POLYGON_MODE_FILL;
    rasterizer.lineWidth               = 1.0f;
    rasterizer.cullMode                = VK_CULL_MODE_BACK_BIT;
    rasterizer.frontFace               = VK_FRONT_FACE_CLOCKWISE;
    rasterizer.depthBiasEnable         = VK_FALSE;

    VkPipelineMultisampleStateCreateInfo multisampling{};
    multisampling.sType                = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisampling.sampleShadingEnable  = VK_FALSE;
    multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

    VkPipelineColorBlendAttachmentState colorBlendAttachment{};
    colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    colorBlendAttachment.blendEnable    = VK_FALSE;

    VkPipelineColorBlendStateCreateInfo colorBlending{};
    colorBlending.sType             = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    colorBlending.logicOpEnable     = VK_FALSE;
    colorBlending.logicOp           = VK_LOGIC_OP_COPY;
    colorBlending.attachmentCount   = 1;
    colorBlending.pAttachments      = &colorBlendAttachment;
    colorBlending.blendConstants[0] = 0.0f;
    colorBlending.blendConstants[1] = 0.0f;
    colorBlending.blendConstants[2] = 0.0f;
    colorBlending.blendConstants[3] = 0.0f;

    VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
    pipelineLayoutInfo.sType                  = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutInfo.setLayoutCount         = 0;
    pipelineLayoutInfo.pushConstantRangeCount = 0;

    if (vkCreatePipelineLayout(GetVkDevice(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create pipeline layout!");
    }

    VkGraphicsPipelineCreateInfo pipelineInfo{};
    pipelineInfo.sType               = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipelineInfo.stageCount          = shaderStages.size();
    pipelineInfo.pStages             = shaderStages.data();
    pipelineInfo.pVertexInputState   = &vertexInputInfo;
    pipelineInfo.pInputAssemblyState = &inputAssembly;
    pipelineInfo.pViewportState      = &viewportState;
    pipelineInfo.pRasterizationState = &rasterizer;
    pipelineInfo.pMultisampleState   = &multisampling;
    pipelineInfo.pColorBlendState    = &colorBlending;
    pipelineInfo.layout              = pipelineLayout;
    pipelineInfo.renderPass          = renderPass->GetVkRenderPass();
    pipelineInfo.subpass             = 0;
    pipelineInfo.basePipelineHandle  = VK_NULL_HANDLE;

    if (vkCreateGraphicsPipelines(GetVkDevice(), VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &graphicsPipeline) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create graphics pipeline!");
    }
    shader->Destroy();
}

void FVkDevice::createFramebuffers()
{
    auto swapChainImageViews = p_FVkSwapChain->GetImageViews();
    auto swapChainExtent     = p_FVkSwapChain->GetSwapChainExtent();
    swapChainFramebuffers.resize(swapChainImageViews.size());

    for (size_t i = 0; i < swapChainImageViews.size(); i++)
    {
        VkImageView attachments[] = {swapChainImageViews[i]};

        VkFramebufferCreateInfo framebufferInfo{};
        framebufferInfo.sType           = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo.renderPass      = renderPass->GetVkRenderPass();
        framebufferInfo.attachmentCount = 1;
        framebufferInfo.pAttachments    = attachments;
        framebufferInfo.width           = swapChainExtent.width;
        framebufferInfo.height          = swapChainExtent.height;
        framebufferInfo.layers          = 1;

        if (vkCreateFramebuffer(GetVkDevice(), &framebufferInfo, nullptr, &swapChainFramebuffers[i]) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create framebuffer!");
        }
    }
}

void FVkDevice::createCommandPool()

{
    QueueFamilyIndices queueFamilyIndices = p_FVkPhysicalDevice->FindQueueFamilies(p_FVkPhysicalDevice->GetVkPhysicalDevice());

    VkCommandPoolCreateInfo poolInfo{};
    poolInfo.sType            = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();

    if (vkCreateCommandPool(GetVkDevice(), &poolInfo, nullptr, &commandPool) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create command pool!");
    }
}

void FVkDevice::createCommandBuffers()
{
    auto swapChainExtent = p_FVkSwapChain->GetSwapChainExtent();

    commandBuffers.resize(swapChainFramebuffers.size());

    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType              = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool        = commandPool;
    allocInfo.level              = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = (uint32_t)commandBuffers.size();

    if (vkAllocateCommandBuffers(GetVkDevice(), &allocInfo, commandBuffers.data()) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to allocate command buffers!");
    }

    for (size_t i = 0; i < commandBuffers.size(); i++)
    {
        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

        if (vkBeginCommandBuffer(commandBuffers[i], &beginInfo) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to begin recording command buffer!");
        }

        VkRenderPassBeginInfo renderPassInfo{};
        renderPassInfo.sType             = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass        = renderPass->GetVkRenderPass();
        renderPassInfo.framebuffer       = swapChainFramebuffers[i];
        renderPassInfo.renderArea.offset = {0, 0};
        renderPassInfo.renderArea.extent = swapChainExtent;

        VkClearValue clearColor        = {0.0f, 0.0f, 0.0f, 1.0f};
        renderPassInfo.clearValueCount = 1;
        renderPassInfo.pClearValues    = &clearColor;

        vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

        vkCmdBindPipeline(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);

        vkCmdDraw(commandBuffers[i], 3, 1, 0, 0);

        vkCmdEndRenderPass(commandBuffers[i]);

        if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to record command buffer!");
        }
    }
}

void FVkDevice::createSyncObjects()
{
    auto swapChainImages = p_FVkSwapChain->GetImages();

    imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
    renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
    inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);
    imagesInFlight.resize(swapChainImages.size(), VK_NULL_HANDLE);

    VkSemaphoreCreateInfo semaphoreInfo{};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo fenceInfo{};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
    {
        if (vkCreateSemaphore(GetVkDevice(), &semaphoreInfo, nullptr, &imageAvailableSemaphores[i]) != VK_SUCCESS ||
            vkCreateSemaphore(GetVkDevice(), &semaphoreInfo, nullptr, &renderFinishedSemaphores[i]) != VK_SUCCESS ||
            vkCreateFence(GetVkDevice(), &fenceInfo, nullptr, &inFlightFences[i]) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create synchronization objects for a frame!");
        }
    }
}

void FVkDevice::BeginDraw() {}

void FVkDevice::Draw()
{
    vkWaitForFences(GetVkDevice(), 1, &inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);

    uint32_t imageIndex;
    VkResult result = p_FVkSwapChain->AquireNextImage(imageAvailableSemaphores[currentFrame], imageIndex);

    if (result == VK_ERROR_OUT_OF_DATE_KHR)
    {
        recreateSwapChain();
        return;
    }
    else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
    {
        throw std::runtime_error("failed to acquire swap chain image!");
    }

    if (imagesInFlight[imageIndex] != VK_NULL_HANDLE)
    {
        vkWaitForFences(GetVkDevice(), 1, &imagesInFlight[imageIndex], VK_TRUE, UINT64_MAX);
    }
    imagesInFlight[imageIndex] = inFlightFences[currentFrame];

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    VkSemaphore          waitSemaphores[] = {imageAvailableSemaphores[currentFrame]};
    VkPipelineStageFlags waitStages[]     = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
    submitInfo.waitSemaphoreCount         = 1;
    submitInfo.pWaitSemaphores            = waitSemaphores;
    submitInfo.pWaitDstStageMask          = waitStages;

    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers    = &commandBuffers[imageIndex];

    VkSemaphore signalSemaphores[]  = {renderFinishedSemaphores[currentFrame]};
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores    = signalSemaphores;

    vkResetFences(GetVkDevice(), 1, &inFlightFences[currentFrame]);

    if (vkQueueSubmit(p_FVkLogicalDevice->GetGraphicsQueue(), 1, &submitInfo, inFlightFences[currentFrame]) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to submit draw command buffer!");
    }

    result = p_FVkSwapChain->QueuePresent(p_FVkLogicalDevice->GetPresentQueue(), signalSemaphores);

    if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || framebufferResized)
    {
        framebufferResized = false;
        recreateSwapChain();
    }
    else if (result != VK_SUCCESS)
    {
        throw std::runtime_error("failed to present swap chain image!");
    }

    currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
}

void FVkDevice::EndDraw() {}

VkShaderModule FVkDevice::createShaderModule(const std::string &code)
{
    VkShaderModuleCreateInfo createInfo{};
    createInfo.sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = code.size();
    createInfo.pCode    = reinterpret_cast<const uint32_t *>(code.data());

    VkShaderModule shaderModule;
    if (vkCreateShaderModule(p_FVkLogicalDevice->GetLogicalDevice(), &createInfo, nullptr, &shaderModule) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create shader module!");
    }

    return shaderModule;
}

}  // namespace FlyEngine::Backend