#pragma once

#include <stddef.h>
#include <stdint.h>

#include "Common/BaseDefines.hpp"

FLYENGINE_BEGIN_NAMESPACE
struct BlockHeader
{
    // union-ed with data
    BlockHeader *pNext;
};

struct PageHeader
{
    PageHeader  *pNext;
    BlockHeader *Blocks() { return reinterpret_cast<BlockHeader *>(this + 1); }
};

class Allocator
{
public:
    // debug patterns
    static const Int8 PATTERN_ALIGN = 0xFC;
    static const Int8 PATTERN_ALLOC = 0xFD;
    static const Int8 PATTERN_FREE  = 0xFE;

    Allocator();
    Allocator(size_t data_size, size_t page_size, size_t alignment);
    ~Allocator();

    // resets the allocator to a new configuration
    void Reset(size_t data_size, size_t page_size, size_t alignment);

    // alloc and free blocks
    void *Allocate();
    void  Free(void *p);
    void  FreeAll();

private:
    // gets the next block
    BlockHeader *NextBlock(BlockHeader *pBlock);

    // the page list
    PageHeader *m_pPageList;

    // the free block list
    BlockHeader *m_pFreeList;

    size_t m_szDataSize;
    size_t m_szPageSize;
    size_t m_szAlignmentSize;
    size_t m_szBlockSize;
    size_t m_nBlocksPerPage;

    // statistics
    size_t m_nPages;
    size_t m_nBlocks;
    size_t m_nFreeBlocks;

    // disable copy & assignment
    Allocator(const Allocator &clone);
    Allocator &operator=(const Allocator &rhs);
};
FLYENGINE_END_NAMESPACE
