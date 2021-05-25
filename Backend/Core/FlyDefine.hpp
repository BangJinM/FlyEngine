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

enum class ObjectType
{
    UNKNOWN,
    BUFFER,
    TEXTURE,
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

enum class BufferUsage : int
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
    BufferUsage usage  = BufferUsage::NONE;
    uint        size   = 0;
    uint        stride = 0;
};

struct CommandBufferInfo
{};

struct DescriptorSetInfo
{};

struct DescriptorSetLayoutInfo
{};

struct FenceInfo
{};

struct FramebufferInfo
{};

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

enum class ShaderStageFlagBit : int
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
typedef ShaderStageFlagBit ShaderStageFlags;

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

struct TextureInfo
{};

}  // namespace FlyEngine::Backend