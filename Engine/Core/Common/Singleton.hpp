#pragma once

#include "Common/BaseDefines.hpp"
#include "Common/NonCopyable.hpp"

FLYENGINE_CORE_BEGIN_NAMESPACE

template <class T>
class Singleton : NonCopyable
{
protected:
    inline static T *singleton = nullptr;

public:
    inline static T GetInstance()
    {
        if (singleton)
            return singleton;
        singleton = new T();
    }
};

FLYENGINE_END_NAMESPACE