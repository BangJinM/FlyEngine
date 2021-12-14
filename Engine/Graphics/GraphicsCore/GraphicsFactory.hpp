#pragma once
#include "GraphicsDefine.hpp"

#include "Interface/IRuntimeModule.h"

#include "GBuffer.hpp"
#include "GCommandBuffer.hpp"
#include "GContext.hpp"
#include "GDescriptorSet.hpp"
#include "GDescriptorSetLayout.hpp"
#include "GDevice.hpp"
#include "GFence.hpp"
#include "GFramebuffer.hpp"
#include "GInputAssembler.hpp"
#include "GPipelineLayout.hpp"
#include "GQueue.hpp"
#include "GRenderPass.hpp"
#include "GSampler.hpp"
#include "GShader.hpp"
#include "GTexture.hpp"

FLYENGINE_GRAPHICS_BEGIN_NAMESPACE

class GraphicsFactory : public Core::IRuntimeModule
{
public:
    virtual GBuffer              *CreateBuffer()              = 0;
    virtual GCommandBuffer       *CreateCommandBuffer()       = 0;
    virtual GDescriptorSet       *CreateDescriptorSet()       = 0;
    virtual GDescriptorSetLayout *CreateDescriptorSetLayout() = 0;
    virtual GFence               *CreateFence()               = 0;
    virtual GFramebuffer         *CreateFramebuffer()         = 0;
    virtual GInputAssembler      *CreateInputAssembler()      = 0;
    virtual GPipelineLayout      *CreatePipelineLayout()      = 0;
    virtual GQueue               *CreateQueue()               = 0;
    virtual GRenderPass          *CreateRenderPass()          = 0;
    virtual GSampler             *CreateSampler()             = 0;
    virtual GShader              *CreateShader()              = 0;
    virtual GTexture             *CreateTexture()             = 0;
    virtual GContext             *CreateContext()             = 0;
};

FLYENGINE_END_NAMESPACE