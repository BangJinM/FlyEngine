#pragma once

namespace FlyEngine::Memory
{
#ifndef ALIGN
#    define ALIGN(x, a) (((x) + ((a)-1)) & ~((a)-1))
#endif
}  // namespace FlyEngine::Memory