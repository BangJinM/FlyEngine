
#pragma once

#include <vector>

#include "Common/BaseDefines.hpp"
#include "GLFWApp.hpp"
// #include "Memory/MemoryManager.hpp"

FLYENGINE_BEGIN_NAMESPACE

IApplication *g_pApplication = static_cast<IApplication *>(new GLFWApp);
// IRuntimeModule *g_pMemoryManager = static_cast<IRuntimeModule *>(new MemoryManager);

FLYENGINE_END_NAMESPACE