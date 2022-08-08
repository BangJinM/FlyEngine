#pragma once

#include <string>
#include <vector>

#include "TypeDef.h"

namespace cc
{

class StringUtil
{
public:
    static int                      VPrintf(char *buf, char *last, const char *fmt, char *args);
    static int                      Printf(char *buf, char *last, const char *fmt, ...);
    static std::string              Format(const char *fmt, ...);
    static std::vector<std::string> Split(const std::string &str, const std::string &delims, uint max_splits = 0);
};

}  // namespace cc
