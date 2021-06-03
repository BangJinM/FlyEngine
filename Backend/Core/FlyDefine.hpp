#pragma once

#include <string>
#include <vector>
#include "FlyType.hpp"

namespace FlyEngine::Backend
{

class FlyBuffer;
class FlyCommandBuffer;
class FlyDescriptorSet;
class FlyDescriptorSetLayout;
class FlyFence;
class FlyFramebuffer;
class FlyInputAssembler;
class FlyPipelineLayout;
class FlyPipelineState;
class FlyQueue;
class FlyRenderPass;
class FlySampler;
class FlyShader;
class FlyTexture;
class FlyTextureView;

enum class ShaderStageFlagBit : uint
{
    NONE       = 0x0,
    VERTEX     = 0x1,
    CONTROL    = 0x2,
    EVALUATION = 0x4,
    GEOMETRY   = 0x8,
    FRAGMENT   = 0x10,
    COMPUTE    = 0x20,
    ALL        = 0x3f,
};

enum class DescriptorType : uint
{
    UNKNOWN                = 0,
    UNIFORM_BUFFER         = 0x1,
    DYNAMIC_UNIFORM_BUFFER = 0x2,
    STORAGE_BUFFER         = 0x4,
    DYNAMIC_STORAGE_BUFFER = 0x8,
    SAMPLER                = 0x10,
};

enum class ObjectType
{
    UNKNOWN,
    BUFFER,
    TEXTURE,
    TEXTURE_VIEW,
    RENDER_PASS,
    FRAMEBUFFER,
    SAMPLER,
    SHADER,
    DESCRIPTOR_SET_LAYOUT,
    PIPELINE_LAYOUT,
    PIPELINE_STATE,
    DESCRIPTOR_SET,
    INPUT_ASSEMBLER,
    COMMAND_BUFFER,
    FENCE,
    QUEUE,
};

struct ColorAttachment
{};
typedef std::vector<ColorAttachment> ColorAttachmentList;

struct DepthStencilAttachment
{};

enum BufferUsage : int
{
    NONE = 0,
    TRANSFER_SRC,
    TRANSFER_DST,
    INDEX,
    VERTEX,
    UNIFORM,
    STORAGE,
    INDIRECT,
};

struct BufferInfo
{
    uint usage           = BufferUsage::NONE;
    uint size            = 0;
    uint stride          = 0;
    bool isStagingBuffer = false;
};

struct CommandBufferInfo
{};

struct DescriptorSetInfo
{};

struct DescriptorSetLayoutBindingInfo
{
    int                binding         = 0;
    int                descriptorCount = 1;
    DescriptorType     descriptorType  = DescriptorType::DYNAMIC_UNIFORM_BUFFER;
    ShaderStageFlagBit stageFlags      = ShaderStageFlagBit::VERTEX;
};

struct DescriptorSetLayoutInfo
{
    std::vector<DescriptorSetLayoutBindingInfo> descriptorSetLayoutBindingInfoList;
};

struct FenceInfo
{};

struct FramebufferInfo
{
    FlyRenderPass *               renderPass;
    std::vector<FlyTextureView *> views;
};

struct InputAssemblerInfo
{};

struct PipelineLayoutInfo
{};

struct PipelineStateInfo
{
    FlyShader *        shader;
    FlyPipelineLayout *pipelineLayout;
};

struct QueueInfo
{};

struct RenderPassInfo
{};

struct SamplerInfo
{};

struct ShaderStage
{
    ShaderStageFlagBit stage;
    std::string        source;
};

typedef std::vector<ShaderStage> ShaderStageList;

struct ShaderInfo
{
    ShaderStageList shaderStageList;
    std::string     name = "";
};

struct TextureViewInfo
{
    FlyTexture *texture;
};

struct TextureInfo
{
    int texWidth;
    int texHeight;
};

enum InputRate
{
    VERTEX_INPUT_RATE_VERTEX   = 0,
    VERTEX_INPUT_RATE_INSTANCE = 1,
    VERTEX_INPUT_RATE_MAX_ENUM = 0x7FFFFFFF
};

struct VertexInputBindingDescription
{
    int       binding   = 0;
    int       stride    = 0;
    InputRate inputRate = InputRate::VERTEX_INPUT_RATE_MAX_ENUM;
};

struct VertexInputAttributeDescription
{
    int binding  = 0;
    int location = 0;
    int format   = 0;
    int offset   = 0;
};

}  // namespace FlyEngine::Backend