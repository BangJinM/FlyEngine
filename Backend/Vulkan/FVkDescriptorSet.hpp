#pragma once

#include "../Core/FlyDescriptorSet.hpp"

namespace FlyEngine::Backend
{
class FVkDescriptorSet : public FlyDescriptorSet
{
public:
    FVkDescriptorSet(FlyDevice *fVkDevice) : FlyDescriptorSet(fVkDevice) {}
    ~FVkDescriptorSet() {}

    virtual void Destroy() override;
    virtual void Initialize(const DescriptorSetInfo &info) override;
};

}  // namespace FlyEngine::Backend