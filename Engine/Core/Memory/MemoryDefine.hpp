#pragma once

#include "Common/BaseDefines.h"

FLYENGINE_CORE_BEGIN_NAMESPACE

#ifndef ALIGN
#    define ALIGN(x, a) (((x) + ((a)-1)) & ~((a)-1))
#endif

FLYENGINE_END_NAMESPACE