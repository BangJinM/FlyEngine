#pragma once

#include "FlyObject.hpp"

namespace FlyEngine::Backend
{
class FlyInputAssembler : public FlyObject
{
public:
    FlyInputAssembler(FlyDevice *flyDevice) : FlyObject(ObjectType::INPUT_ASSEMBLER, flyDevice) {}
    ~FlyInputAssembler() {}

    virtual void Initialize(const InputAssemblerInfo &info) = 0;
};

}  // namespace FlyEngine::Backend