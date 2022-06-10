#pragma once
#include "Common/BaseDefines.hpp"

#include <string>
#include <vector>

#define FLYENGINE_GRAPHICS_BEGIN_NAMESPACE FLYENGINE_BEGIN_NAMESPACE(Graphics)
#define USING_FLYENGINE_GRAPHICS_NAMESPACE USING_FLYENGINE_NAMESPACE(Graphics)

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

struct Size
{
    uint32_t width;
    uint32_t height;
};

struct Size3D
{
    uint32_t width;
    uint32_t height;
    uint32_t depth;
};

struct GraphicsEngineInfo
{
    bool validate = false;  //是否调试
};

enum class ShaderStageFlagBit : unsigned int
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

enum class Format
{
    UNKNOWN,

    A8,
    L8,
    LA8,

    R8,
    R8SN,
    R8UI,
    R8I,
    R16F,
    R16UI,
    R16I,
    R32F,
    R32UI,
    R32I,

    RG8,
    RG8SN,
    RG8UI,
    RG8I,
    RG16F,
    RG16UI,
    RG16I,
    RG32F,
    RG32UI,
    RG32I,

    RGB8,
    SRGB8,
    RGB8SN,
    RGB8UI,
    RGB8I,
    RGB16F,
    RGB16UI,
    RGB16I,
    RGB32F,
    RGB32UI,
    RGB32I,

    RGBA8,
    BGRA8,
    SRGB8_A8,
    RGBA8SN,
    RGBA8UI,
    RGBA8I,
    RGBA16F,
    RGBA16UI,
    RGBA16I,
    RGBA32F,
    RGBA32UI,
    RGBA32I,

    // Special Format
    R5G6B5,
    R11G11B10F,
    RGB5A1,
    RGBA4,
    RGB10A2,
    RGB10A2UI,
    RGB9E5,

    // Depth-Stencil Format
    D16,
    D16S8,
    D24,
    D24S8,
    D32F,
    D32F_S8,

    // Compressed Format

    // Block Compression Format, DDS (DirectDraw Surface)
    // DXT1: 3 channels (5:6:5), 1/8 origianl size, with 0 or 1 bit of alpha
    BC1,
    BC1_ALPHA,
    BC1_SRGB,
    BC1_SRGB_ALPHA,
    // DXT3: 4 channels (5:6:5), 1/4 origianl size, with 4 bits of alpha
    BC2,
    BC2_SRGB,
    // DXT5: 4 channels (5:6:5), 1/4 origianl size, with 8 bits of alpha
    BC3,
    BC3_SRGB,
    // 1 channel (8), 1/4 origianl size
    BC4,
    BC4_SNORM,
    // 2 channels (8:8), 1/2 origianl size
    BC5,
    BC5_SNORM,
    // 3 channels (16:16:16), half-floating point, 1/6 origianl size
    // UF16: unsigned float, 5 exponent bits + 11 mantissa bits
    // SF16: signed float, 1 signed bit + 5 exponent bits + 10 mantissa bits
    BC6H_UF16,
    BC6H_SF16,
    // 4 channels (4~7 bits per channel) with 0 to 8 bits of alpha, 1/3 original size
    BC7,
    BC7_SRGB,

    // Ericsson Texture Compression Format
    ETC_RGB8,
    ETC2_RGB8,
    ETC2_SRGB8,
    ETC2_RGB8_A1,
    ETC2_SRGB8_A1,
    ETC2_RGBA8,
    ETC2_SRGB8_A8,
    EAC_R11,
    EAC_R11SN,
    EAC_RG11,
    EAC_RG11SN,

    // PVRTC (PowerVR)
    PVRTC_RGB2,
    PVRTC_RGBA2,
    PVRTC_RGB4,
    PVRTC_RGBA4,
    PVRTC2_2BPP,
    PVRTC2_4BPP,

    // ASTC (Adaptive Scalable Texture Compression)
    ASTC_RGBA_4x4,
    ASTC_RGBA_5x4,
    ASTC_RGBA_5x5,
    ASTC_RGBA_6x5,
    ASTC_RGBA_6x6,
    ASTC_RGBA_8x5,
    ASTC_RGBA_8x6,
    ASTC_RGBA_8x8,
    ASTC_RGBA_10x5,
    ASTC_RGBA_10x6,
    ASTC_RGBA_10x8,
    ASTC_RGBA_10x10,
    ASTC_RGBA_12x10,
    ASTC_RGBA_12x12,

    // ASTC (Adaptive Scalable Texture Compression) SRGB
    ASTC_SRGBA_4x4,
    ASTC_SRGBA_5x4,
    ASTC_SRGBA_5x5,
    ASTC_SRGBA_6x5,
    ASTC_SRGBA_6x6,
    ASTC_SRGBA_8x5,
    ASTC_SRGBA_8x6,
    ASTC_SRGBA_8x8,
    ASTC_SRGBA_10x5,
    ASTC_SRGBA_10x6,
    ASTC_SRGBA_10x8,
    ASTC_SRGBA_10x10,
    ASTC_SRGBA_12x10,
    ASTC_SRGBA_12x12,

    // Total count
    COUNT,
};

struct ShaderStageInfo
{
    ShaderStageFlagBit stage;
    std::string        source;
    // std::string        entryPoint = "main";
};

struct RenderPassInfo
{
    const std::vector<Format> &colorAttachmentFormats;
    Format                     depthAttachmentFormat;
    uint32_t                   subpassCount = 1;
    bool                       clearColor   = true;
    bool                       clearDepth   = true;
    // vk::ImageLayout            initialLayout;
    // vk::ImageLayout            finalLayout;
};

enum class TextureUsageBit : unsigned int
{
    NONE                     = 0,
    TRANSFER_SRC             = 0x1,
    TRANSFER_DST             = 0x2,
    SAMPLED                  = 0x4,
    STORAGE                  = 0x8,
    COLOR_ATTACHMENT         = 0x10,
    DEPTH_STENCIL_ATTACHMENT = 0x20,
    TRANSIENT_ATTACHMENT     = 0x40,
    INPUT_ATTACHMENT         = 0x80,
};

struct Image3D
{
    Size3D          size;
    Format          format  = Format::RGBA8;
    TextureUsageBit usage   = TextureUsageBit::NONE;
    bool            mipmaps = false;
};

struct Image2D
{
    Size            size;
    Format          format  = Format::RGBA8;
    TextureUsageBit usage   = TextureUsageBit::NONE;
    bool            mipmaps = false;
};

FLYENGINE_END_NAMESPACE