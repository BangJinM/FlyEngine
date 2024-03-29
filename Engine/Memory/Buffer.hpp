﻿#pragma once

#include <memory.h>
#include <stddef.h>

#include "Common/BaseDefines.hpp"
#include "Memory/MemoryManager.hpp"

FLYENGINE_BEGIN_NAMESPACE

extern IRuntimeModule *g_pMemoryManager;

class Buffer
{
public:
    Buffer() : m_pData(nullptr), m_szSize(0), m_szAlignment(alignof(uint32_t)) {}

    Buffer(size_t size, size_t alignment = 4) : m_szSize(size), m_szAlignment(alignment)
    {
        auto memory = static_cast<MemoryManager *>(g_pMemoryManager);
        m_pData     = reinterpret_cast<Int8 *>(memory->Allocate(size, alignment));
    }

    Buffer(const Buffer &rhs)
    {
        auto memory = static_cast<MemoryManager *>(g_pMemoryManager);
        m_pData     = reinterpret_cast<Int8 *>(memory->Allocate(rhs.m_szSize, rhs.m_szAlignment));
        memcpy(m_pData, rhs.m_pData, rhs.m_szSize);
        m_szSize      = rhs.m_szSize;
        m_szAlignment = rhs.m_szAlignment;
    }

    Buffer(Buffer &&rhs)
    {
        m_pData           = rhs.m_pData;
        m_szSize          = rhs.m_szSize;
        m_szAlignment     = rhs.m_szAlignment;
        rhs.m_pData       = nullptr;
        rhs.m_szSize      = 0;
        rhs.m_szAlignment = 4;
    }

    Buffer &operator=(const Buffer &rhs)
    {
        if (m_szSize >= rhs.m_szSize && m_szAlignment == rhs.m_szAlignment)
        {
            memcpy(m_pData, rhs.m_pData, rhs.m_szSize);
        }
        else
        {
            auto memory = static_cast<MemoryManager *>(g_pMemoryManager);
            if (m_pData)
                memory->Free(m_pData, m_szSize, m_szAlignment);
            m_pData = reinterpret_cast<Int8 *>(memory->Allocate(rhs.m_szSize, rhs.m_szAlignment));
            memcpy(m_pData, rhs.m_pData, rhs.m_szSize);
            m_szSize      = rhs.m_szSize;
            m_szAlignment = rhs.m_szAlignment;
        }
        return *this;
    }

    Buffer &operator=(Buffer &&rhs)
    {
        auto memory = static_cast<MemoryManager *>(g_pMemoryManager);
        if (m_pData)
            memory->Free(m_pData, m_szSize, m_szAlignment);
        m_pData           = rhs.m_pData;
        m_szSize          = rhs.m_szSize;
        m_szAlignment     = rhs.m_szAlignment;
        rhs.m_pData       = nullptr;
        rhs.m_szSize      = 0;
        rhs.m_szAlignment = 4;
        return *this;
    }

    ~Buffer()
    {
        auto memory = static_cast<MemoryManager *>(g_pMemoryManager);
        if (m_pData)
            memory->Free(m_pData, m_szSize, m_szAlignment);
        m_pData = nullptr;
    }

    Int8       *GetData(void) { return m_pData; };
    const Int8 *GetData(void) const { return m_pData; };
    size_t         GetDataSize(void) const { return m_szSize; };

public:
    Int8 *m_pData;

protected:
    size_t m_szSize;
    size_t m_szAlignment;
};
FLYENGINE_END_NAMESPACE
