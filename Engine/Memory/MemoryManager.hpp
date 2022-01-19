#pragma once
#include "Allocator.hpp"
#include "Common/BaseDefines.hpp"
#include "Common/IRuntimeModule.h"

FLYENGINE_BEGIN_NAMESPACE

class MemoryManager : public IRuntimeModule
{
public:
    virtual ~MemoryManager() {}

    virtual bool Initialize();
    virtual bool Finalize();
    virtual void Tick(float deltaTime);

    void *Allocate(size_t size);
    void *Allocate(size_t size, size_t alignment);
    void  Free(void *p, size_t size, size_t alignment);

private:
    static size_t    *m_pBlockSizeLookup;
    static Allocator *m_pAllocators;
    static bool       m_bInitialized;

private:
    static Allocator *LookUpAllocator(size_t size);
};

extern IRuntimeModule *g_pMemoryManager;

FLYENGINE_END_NAMESPACE
