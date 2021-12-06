
#pragma once

#include <vector>

#include "App/GLFWApp.h"
#include "Common/BaseDefines.h"
#include "Memory/MemoryManager.hpp"

FLYENGINE_CORE_BEGIN_NAMESPACE

IApplication *  g_pApp           = static_cast<IApplication *>(new GLFWApp);
IRuntimeModule *g_pMemoryManager = static_cast<IRuntimeModule *>(new MemoryManager);

FLYENGINE_END_NAMESPACE