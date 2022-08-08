#ifndef CC_CORE_GFX_DEVICE_H_
#define CC_CORE_GFX_DEVICE_H_

#include "GFXBuffer.h"
#include "GFXCommandBuffer.h"
#include "GFXDef.h"
#include "GFXDescriptorSet.h"
#include "GFXDescriptorSetLayout.h"
#include "GFXFence.h"
#include "GFXFramebuffer.h"
#include "GFXInputAssembler.h"
#include "GFXPipelineLayout.h"
#include "GFXPipelineState.h"
#include "GFXQueue.h"
#include "GFXRenderPass.h"
#include "GFXSampler.h"
#include "GFXShader.h"
#include "GFXTexture.h"

namespace cc
{
namespace gfx
{

class Device : public Object
{
public:
    static Device *getInstance();

    Device();
    virtual ~Device();

    virtual bool initialize(const DeviceInfo &info) = 0;
    virtual void destroy()                          = 0;
    virtual void resize(uint width, uint height)    = 0;
    virtual void acquire()                          = 0;
    virtual void present()                          = 0;

    inline CommandBuffer *createCommandBuffer(const CommandBufferInfo &info)
    {
        CommandBuffer *res = doCreateCommandBuffer(info, false);
        res->initialize(info);
        return res;
    }
    inline Fence *createFence(const FenceInfo &info)
    {
        Fence *res = createFence();
        res->initialize(info);
        return res;
    }
    inline Queue *createQueue(const QueueInfo &info)
    {
        Queue *res = createQueue();
        res->initialize(info);
        return res;
    }
    inline Buffer *createBuffer(const BufferInfo &info)
    {
        Buffer *res = createBuffer();
        res->initialize(info);
        return res;
    }
    inline Buffer *createBuffer(const BufferViewInfo &info)
    {
        Buffer *res = createBuffer();
        res->initialize(info);
        return res;
    }
    inline Texture *createTexture(const TextureInfo &info)
    {
        Texture *res = createTexture();
        res->initialize(info);
        return res;
    }
    inline Texture *createTexture(const TextureViewInfo &info)
    {
        Texture *res = createTexture();
        res->initialize(info);
        return res;
    }
    inline Sampler *createSampler(const SamplerInfo &info)
    {
        Sampler *res = createSampler();
        res->initialize(info);
        return res;
    }
    inline Shader *createShader(const ShaderInfo &info)
    {
        Shader *res = createShader();
        res->initialize(info);
        return res;
    }
    inline InputAssembler *createInputAssembler(const InputAssemblerInfo &info)
    {
        InputAssembler *res = createInputAssembler();
        res->initialize(info);
        return res;
    }
    inline RenderPass *createRenderPass(const RenderPassInfo &info)
    {
        RenderPass *res = createRenderPass();
        res->initialize(info);
        return res;
    }
    inline Framebuffer *createFramebuffer(const FramebufferInfo &info)
    {
        Framebuffer *res = createFramebuffer();
        res->initialize(info);
        return res;
    }
    inline DescriptorSet *createDescriptorSet(const DescriptorSetInfo &info)
    {
        DescriptorSet *res = createDescriptorSet();
        res->initialize(info);
        return res;
    }
    inline DescriptorSetLayout *createDescriptorSetLayout(const DescriptorSetLayoutInfo &info)
    {
        DescriptorSetLayout *res = createDescriptorSetLayout();
        res->initialize(info);
        return res;
    }
    inline PipelineLayout *createPipelineLayout(const PipelineLayoutInfo &info)
    {
        PipelineLayout *res = createPipelineLayout();
        res->initialize(info);
        return res;
    }
    inline PipelineState *createPipelineState(const PipelineStateInfo &info)
    {
        PipelineState *res = createPipelineState();
        res->initialize(info);
        return res;
    }
    inline void copyBuffersToTexture(const BufferDataList &buffers, Texture *dst, const BufferTextureCopyList &regions)
    {
        copyBuffersToTexture(buffers.data(), dst, regions.data(), static_cast<uint>(regions.size()));
    }

    virtual void             setMultithreaded(bool multithreaded) {}
    virtual SurfaceTransform getSurfaceTransform() const { return _transform; }
    virtual uint             getWidth() const { return _width; }
    virtual uint             getHeight() const { return _height; }
    virtual uint             getNativeWidth() const { return _nativeWidth; }
    virtual uint             getNativeHeight() const { return _nativeHeight; }
    virtual MemoryStatus    &getMemoryStatus() { return _memoryStatus; }
    virtual uint             getNumDrawCalls() const { return _numDrawCalls; }
    virtual uint             getNumInstances() const { return _numInstances; }
    virtual uint             getNumTris() const { return _numTriangles; }

    Format                           getColorFormat() const;
    Format                           getDepthStencilFormat() const;
    inline API                       getGfxAPI() const { return _API; }
    inline const std::string        &getDeviceName() const { return _deviceName; }
    inline Context                  *getContext() const { return _context; }
    inline Queue                    *getQueue() const { return _queue; }
    inline CommandBuffer            *getCommandBuffer() const { return _cmdBuff; }
    inline const std::string        &getRenderer() const { return _renderer; }
    inline const std::string        &getVendor() const { return _vendor; }
    inline int                       getMaxVertexAttributes() const { return _maxVertexAttributes; }
    inline int                       getMaxVertexUniformVectors() const { return _maxVertexUniformVectors; }
    inline int                       getMaxFragmentUniformVectors() const { return _maxFragmentUniformVectors; }
    inline int                       getMaxTextureUnits() const { return _maxTextureUnits; }
    inline int                       getMaxVertexTextureUnits() const { return _maxVertexTextureUnits; }
    inline int                       getMaxUniformBufferBindings() const { return _maxUniformBufferBindings; }
    inline int                       getMaxUniformBlockSize() const { return _maxUniformBlockSize; }
    inline int                       getMaxTextureSize() const { return _maxTextureSize; }
    inline int                       getMaxCubeMapTextureSize() const { return _maxCubeMapTextureSize; }
    inline int                       getUboOffsetAlignment() const { return _uboOffsetAlignment; }
    inline int                       getDepthBits() const { return _depthBits; }
    inline int                       getStencilBits() const { return _stencilBits; }
    inline bool                      hasFeature(Feature feature) const { return _features[static_cast<uint8_t>(feature)]; }
    inline float                     getClipSpaceMinZ() const { return _clipSpaceMinZ; }
    inline float                     getScreenSpaceSignY() const { return _screenSpaceSignY; }
    inline float                     getUVSpaceSignY() const { return _UVSpaceSignY; }
    inline const BindingMappingInfo &bindingMappingInfo() const { return _bindingMappingInfo; }
    inline uint                      genShaderId() { return _shaderIdGen++; }

protected:
    friend class DeviceAgent;

    virtual CommandBuffer       *doCreateCommandBuffer(const CommandBufferInfo &info, bool hasAgent)                                             = 0;
    virtual Fence               *createFence()                                                                                                   = 0;
    virtual Queue               *createQueue()                                                                                                   = 0;
    virtual Buffer              *createBuffer()                                                                                                  = 0;
    virtual Texture             *createTexture()                                                                                                 = 0;
    virtual Sampler             *createSampler()                                                                                                 = 0;
    virtual Shader              *createShader()                                                                                                  = 0;
    virtual InputAssembler      *createInputAssembler()                                                                                          = 0;
    virtual RenderPass          *createRenderPass()                                                                                              = 0;
    virtual Framebuffer         *createFramebuffer()                                                                                             = 0;
    virtual DescriptorSet       *createDescriptorSet()                                                                                           = 0;
    virtual DescriptorSetLayout *createDescriptorSetLayout()                                                                                     = 0;
    virtual PipelineLayout      *createPipelineLayout()                                                                                          = 0;
    virtual PipelineState       *createPipelineState()                                                                                           = 0;
    virtual void                 copyBuffersToTexture(const uint8_t *const *buffers, Texture *dst, const BufferTextureCopy *regions, uint count) = 0;

    virtual void bindRenderContext(bool bound) {}
    virtual void bindDeviceContext(bool bound) {}

    API                                          _API       = API::UNKNOWN;
    SurfaceTransform                             _transform = SurfaceTransform::IDENTITY;
    std::string                                  _deviceName;
    std::string                                  _renderer;
    std::string                                  _vendor;
    std::string                                  _version;
    bool                                         _features[static_cast<uint8_t>(Feature::COUNT)];
    uint                                         _width        = 0;
    uint                                         _height       = 0;
    uint                                         _nativeWidth  = 0;
    uint                                         _nativeHeight = 0;
    MemoryStatus                                 _memoryStatus;
    void                                        *_windowHandle              = 0;
    Context                                     *_context                   = nullptr;
    Queue                                       *_queue                     = nullptr;
    CommandBuffer                               *_cmdBuff                   = nullptr;
    uint                                         _numDrawCalls              = 0u;
    uint                                         _numInstances              = 0u;
    uint                                         _numTriangles              = 0u;
    uint                                         _maxVertexAttributes       = 0u;
    uint                                         _maxVertexUniformVectors   = 0u;
    uint                                         _maxFragmentUniformVectors = 0u;
    uint                                         _maxTextureUnits           = 0u;
    uint                                         _maxVertexTextureUnits     = 0u;
    uint                                         _maxUniformBufferBindings  = 0u;
    uint                                         _maxUniformBlockSize       = 0u;
    uint                                         _maxTextureSize            = 0u;
    uint                                         _maxCubeMapTextureSize     = 0u;
    uint                                         _uboOffsetAlignment        = 0u;
    uint                                         _depthBits                 = 0u;
    uint                                         _stencilBits               = 0u;
    uint                                         _shaderIdGen               = 0u;
    std::unordered_map<std::string, std::string> _macros;
    float                                        _clipSpaceMinZ    = -1.0f;
    float                                        _screenSpaceSignY = 1.0f;
    float                                        _UVSpaceSignY     = -1.0f;
    BindingMappingInfo                           _bindingMappingInfo;

private:
    static Device *_instance;
};

}  // namespace gfx
}  // namespace cc

#endif  // CC_CORE_GFX_DEVICE_H_
