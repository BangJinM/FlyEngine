#pragma once

#include "BaseDefines.hpp"
#include "NonCopyable.hpp"

FLYENGINE_BEGIN_NAMESPACE

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
        return singleton;
    }
};

FLYENGINE_END_NAMESPACE