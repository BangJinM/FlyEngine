#pragma once
#include "GraphicsDefine.hpp"

#include "Interface/IRuntimeModule.h"

#include "GraphicsDefine.hpp"

FLYENGINE_GRAPHICS_BEGIN_NAMESPACE

class Buffer;
class CommandBuffer;
class Context;
class DescriptorSet;
class DescriptorSetLayout;
class Device;
class Fence;
class Framebuffer;
class InputAssembler;
class PipelineLayout;
class Queue;
class RenderPass;
class Sampler;
class ShaderStage;
class Image;

class GraphicsFactory : public Core::IRuntimeModule
{
public:
    virtual Buffer              *CreateBuffer()                           = 0;
    virtual CommandBuffer       *CreateCommandBuffer()                    = 0;
    virtual DescriptorSet       *CreateDescriptorSet()                    = 0;
    virtual DescriptorSetLayout *CreateDescriptorSetLayout()              = 0;
    virtual Fence               *CreateFence()                            = 0;
    virtual Framebuffer         *CreateFramebuffer()                      = 0;
    virtual InputAssembler      *CreateInputAssembler()                   = 0;
    virtual PipelineLayout     *CreatePipelineLayout()                   = 0;
    virtual Queue               *CreateQueue()                            = 0;
    virtual RenderPass          *CreateRenderPass()                       = 0;
    virtual Sampler             *CreateSampler()                          = 0;
    virtual ShaderStage         *CreateShader(ShaderStageInfo shaderInfo) = 0;
    virtual Image               *CreateTexture()                          = 0;
    virtual Context             *CreateContext()                          = 0;

    virtual void prepareFrame() = 0;
    virtual void beginCommand() = 0;
    virtual void endCommand()   = 0;
    virtual void submitFrame()  = 0;
};

FLYENGINE_END_NAMESPACE