#include "FVkQueue.hpp"

namespace FlyEngine::Backend
{
void FVkQueue::Destroy() {}

void FVkQueue::Initialize(const QueueInfo &info)
{
    // uint     queueType       = 0u;
    // VkBool32 needPresentable = VK_FALSE;
    // switch (info->type)
    // {
    //     case QueueType::GRAPHICS:
    //         queueType       = VK_QUEUE_GRAPHICS_BIT;
    //         needPresentable = VK_TRUE;
    //         break;
    //     case QueueType::COMPUTE: queueType = VK_QUEUE_COMPUTE_BIT; break;
    //     case QueueType::TRANSFER: queueType = VK_QUEUE_TRANSFER_BIT; break;
    // }

    // const CCVKGPUContext *context = ((CCVKContext *)device)->gpuContext();

    // size_t queueCount = context->queueFamilyProperties.size();
    // for (size_t i = 0u; i < queueCount; ++i)
    // {
    //     const VkQueueFamilyProperties &properties    = context->queueFamilyProperties[i];
    //     const VkBool32                 isPresentable = context->queueFamilyPresentables[i];
    //     if (properties.queueCount > 0 && (properties.queueFlags & queueType) && (!needPresentable || isPresentable))
    //     {
    //         vkGetDeviceQueue(device->gpuDevice()->vkDevice, i, 0, &gpuQueue->vkQueue);
    //         gpuQueue->queueFamilyIndex = i;
    //         break;
    //     }
    // }
}
}  // namespace FlyEngine::Backend