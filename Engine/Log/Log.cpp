#include "Log.hpp"
FLYENGINE_BEGIN_NAMESPACE

std::mutex    Log::WriteMutex;
std::ofstream Log::FileStream;

FLYENGINE_END_NAMESPACE