#pragma once

#include "FlyObject.hpp"

namespace FlyEngine::Backend
{
class FlyInputAssembler : public FlyObject
{
public:
    FlyInputAssembler() : FlyObject(ObjectType::INPUT_ASSEMBLER) {}
    ~FlyInputAssembler() {}
};

} // namespace FlyEngine::Backend