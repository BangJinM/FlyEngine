#include <iostream>
#include <stdexcept>

#include "BaseDefines.hpp"

void RunTimeError(std::string info)
{
    throw std::runtime_error(info);
}