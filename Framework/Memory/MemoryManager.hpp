#pragma once
#include "Allocator.hpp"

namespace FlyEngine::Memory
{
class MemoryManager
{
public:
    virtual ~MemoryManager() {}

    virtual int  Initialize();
    virtual void Destroy();
    virtual void Tick(float deltaTime);

    void *Allocate(size_t size);
    void *Allocate(size_t size, size_t alignment);
    void  Free(void *p, size_t size, size_t alignment);

private:
    static size_t *       m_pBlockSizeLookup;
    static Allocator *    m_pAllocators;
    static bool           m_bInitialized;
    static MemoryManager *pMemoryManager;

public:
    static MemoryManager *GetInstance();

private:
    static Allocator *LookUpAllocator(size_t size);
};

}  // namespace FlyEngine::Memory
