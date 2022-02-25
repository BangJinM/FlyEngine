#pragma once

#include <string>

#define FLYENGINE_BEGIN_NAMESPACE \
    namespace fly                 \
    {
#define FLYENGINE_END_NAMESPACE }

#define USING_FLYENGINE_NAMESPACE using namespace fly;

void RunTimeError(std::string info);

#define SHOWERROR(info) RunTimeError(info)