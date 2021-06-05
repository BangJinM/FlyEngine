#pragma once

#include "AppInfo.hpp"

namespace FlyEngine
{
class WindowBase
{
public:
    static WindowBase *CreateFlyEngineWindow(AppInfo info);
    virtual void       CreateSurface(void *graphicsInstance, void *surfData) = 0;
    virtual void       GetFrameSize(int &width, int &height)                 = 0;
    virtual void       WaitForNewWindowSize()                                = 0;

public:
    virtual bool Init(AppInfo info) = 0;
    virtual bool IsQuit()           = 0;
    virtual void Tick()             = 0;
    virtual void Destroy()          = 0;

protected:
    AppInfo _info;
};
}  // namespace FlyEngine