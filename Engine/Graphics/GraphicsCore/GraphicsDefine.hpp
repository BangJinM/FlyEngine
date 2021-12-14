#pragma once
#include "Core/Common/BaseDefines.hpp"

#define FLYENGINE_GRAPHICS_BEGIN_NAMESPACE FLYENGINE_BEGIN_NAMESPACE(Graphics)
#define USING_FLYENGINE_GRAPHICS_NAMESPACE USING_FLYENGINE_NAMESPACE(Graphics)

struct GraphicsEngineInfo
{
    bool validate = false;  //是否调试
};