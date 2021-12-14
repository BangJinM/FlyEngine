#pragma once

#include "Common/BaseDefines.hpp"

FLYENGINE_CORE_BEGIN_NAMESPACE

class NonCopyable
{
protected:
    NonCopyable() = default;

    virtual ~NonCopyable() = default;

public:
    NonCopyable(const NonCopyable &) = delete;

    NonCopyable(NonCopyable &&) = default;

    NonCopyable &operator=(const NonCopyable &) = delete;

    NonCopyable &operator=(NonCopyable &&) = default;
};

FLYENGINE_END_NAMESPACE