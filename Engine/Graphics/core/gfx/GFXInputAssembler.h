#ifndef CC_CORE_GFX_INPUT_ASSEMBLER_H_
#define CC_CORE_GFX_INPUT_ASSEMBLER_H_

#include "GFXDef.h"

namespace cc
{
namespace gfx
{

class InputAssembler : public GFXObject
{
public:
    InputAssembler(Device *device);
    virtual ~InputAssembler();

public:
    virtual bool initialize(const InputAssemblerInfo &info) = 0;
    virtual void destroy()                                  = 0;

    void extractDrawInfo(DrawInfo &drawInfo) const;

    inline Device              *getDevice() const { return _device; }
    inline const AttributeList &getAttributes() const { return _attributes; }
    inline const BufferList    &getVertexBuffers() const { return _vertexBuffers; }
    inline Buffer              *getIndexBuffer() const { return _indexBuffer; }
    inline Buffer              *getIndirectBuffer() const { return _indirectBuffer; }
    inline uint                 getVertexCount() const { return _vertexCount; }
    inline uint                 getFirstVertex() const { return _firstVertex; }
    inline uint                 getIndexCount() const { return _indexCount; }
    inline uint                 getFirstIndex() const { return _firstIndex; }
    inline uint                 getVertexOffset() const { return _vertexOffset; }
    inline uint                 getInstanceCount() const { return _instanceCount; }
    inline uint                 getFirstInstance() const { return _firstInstance; }
    inline uint                 getAttributesHash() const { return _attributesHash; }

    virtual void setVertexCount(uint count) { _vertexCount = count; }
    virtual void setFirstVertex(uint first) { _firstVertex = first; }
    virtual void setIndexCount(uint count) { _indexCount = count; }
    virtual void setFirstIndex(uint first) { _firstIndex = first; }
    virtual void setVertexOffset(uint offset) { _vertexOffset = offset; }
    virtual void setInstanceCount(uint count) { _instanceCount = count; }
    virtual void setFirstInstance(uint first) { _firstInstance = first; }

protected:
    uint computeAttributesHash() const;

    Device       *_device = nullptr;
    AttributeList _attributes;
    BufferList    _vertexBuffers;
    Buffer       *_indexBuffer    = nullptr;
    Buffer       *_indirectBuffer = nullptr;
    uint          _vertexCount    = 0;
    uint          _firstVertex    = 0;
    uint          _indexCount     = 0;
    uint          _firstIndex     = 0;
    uint          _vertexOffset   = 0;
    uint          _instanceCount  = 0;
    uint          _firstInstance  = 0;
    uint          _attributesHash = 0;
};

}  // namespace gfx
}  // namespace cc

#endif  // CC_CORE_GFX_INPUT_ASSEMBLER_H_
