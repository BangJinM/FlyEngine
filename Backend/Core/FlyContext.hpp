#pragma once

#include "FlyObject.hpp"

#include "../../FlyApp/AppInfo.hpp"

namespace FlyEngine::Backend
{
class FlyContext
{
public:
    virtual void Initialize(WindowBase *window) = 0;
    virtual void Destroy()                      = 0;
};

}  // namespace FlyEngine::Backend