#pragma once

#include "Common/BaseDefines.h"

FLYENGINE_CORE_BEGIN_NAMESPACE

class IApplication
{
public:
    virtual bool Initialize() = 0;

    virtual bool Finalize() = 0;

    virtual void Tick(float deltaTime) = 0;

    virtual bool IsQuit() = 0;

    virtual bool CreateWindow(const char *Title, int Width, int Height, int GlfwApiHint = 0) = 0;

    virtual bool InitEngine(int DevType) = 0;
};

extern IApplication *g_pApp;

FLYENGINE_END_NAMESPACE