/****************************************************************************
Copyright (c) 2020 Xiamen Yaji Software Co., Ltd.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#ifndef CC_GFXVULKAN_COMMANDS_H_
#define CC_GFXVULKAN_COMMANDS_H_

#include "VKGPUObjects.h"

namespace cc {
namespace gfx {

class CCVKDevice;

struct CCVKDepthBias {
    float constant = 0.0f;
    float clamp = 0.0f;
    float slope = 0.0f;
};

struct CCVKDepthBounds {
    float minBounds = 0.0f;
    float maxBounds = 0.0f;
};

struct CCVKStencilWriteMask {
    StencilFace face = StencilFace::FRONT;
    uint32_t write_mask = 0;
};

struct CCVKStencilCompareMask {
    StencilFace face = StencilFace::FRONT;
    int reference = 0;
    uint32_t compareMask = 0;
};

 void CCVKCmdFuncGetDeviceQueue(CCVKDevice *device, CCVKGPUQueue *gpuQueue);

 void CCVKCmdFuncCreateTexture(CCVKDevice *device, CCVKGPUTexture *gpuTexture);
 void CCVKCmdFuncCreateTextureView(CCVKDevice *device, CCVKGPUTextureView *gpuTextureView);
 void CCVKCmdFuncCreateSampler(CCVKDevice *device, CCVKGPUSampler *gpuSampler);
 void CCVKCmdFuncCreateBuffer(CCVKDevice *device, CCVKGPUBuffer *gpuBuffer);
 void CCVKCmdFuncCreateRenderPass(CCVKDevice *device, CCVKGPURenderPass *gpuRenderPass);
 void CCVKCmdFuncCreateFramebuffer(CCVKDevice *device, CCVKGPUFramebuffer *gpuFramebuffer);
 void CCVKCmdFuncCreateShader(CCVKDevice *device, CCVKGPUShader *gpuShader);
 void CCVKCmdFuncCreateDescriptorSetLayout(CCVKDevice *device, CCVKGPUDescriptorSetLayout *gpuDescriptorSetLayout);
 void CCVKCmdFuncCreatePipelineLayout(CCVKDevice *device, CCVKGPUPipelineLayout *gpuPipelineLayout);
 void CCVKCmdFuncCreatePipelineState(CCVKDevice *device, CCVKGPUPipelineState *gpuPipelineState);
 void CCVKCmdFuncCreateFence(CCVKDevice *device, CCVKGPUFence *gpuFence);

 void CCVKCmdFuncUpdateBuffer(CCVKDevice *device, CCVKGPUBuffer *gpuBuffer, const void *buffer, uint size, const CCVKGPUCommandBuffer *cmdBuffer = nullptr);
 void CCVKCmdFuncCopyBuffersToTexture(CCVKDevice *device, const uint8_t *const *buffers, CCVKGPUTexture *gpuTexture, const BufferTextureCopy *regions, uint count, const CCVKGPUCommandBuffer *cmdBuff);

 void CCVKCmdFuncDestroyRenderPass(CCVKGPUDevice *device, CCVKGPURenderPass *gpuRenderPass);
 void CCVKCmdFuncDestroySampler(CCVKGPUDevice *device, CCVKGPUSampler *gpuSampler);
 void CCVKCmdFuncDestroyShader(CCVKGPUDevice *device, CCVKGPUShader *gpuShader);
 void CCVKCmdFuncDestroyFramebuffer(CCVKGPUDevice *device, CCVKGPUFramebuffer *gpuFramebuffer);
 void CCVKCmdFuncDestroyDescriptorSetLayout(CCVKGPUDevice *device, CCVKGPUDescriptorSetLayout *gpuDescriptorSetLayout);
 void CCVKCmdFuncDestroyPipelineLayout(CCVKGPUDevice *device, CCVKGPUPipelineLayout *gpuPipelineLayout);
 void CCVKCmdFuncDestroyPipelineState(CCVKGPUDevice *device, CCVKGPUPipelineState *gpuPipelineState);
 void CCVKCmdFuncDestroyFence(CCVKGPUDevice *device, CCVKGPUFence *gpuFence);

} // namespace gfx
} // namespace cc

#endif
