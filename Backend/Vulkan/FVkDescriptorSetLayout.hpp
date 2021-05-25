#pragma once

#include "../Core/FlyDescriptorSetLayout.hpp"

namespace FlyEngine::Backend
{
class FVkDescriptorSetLayout : public FlyDescriptorSetLayout
{
public:
    FVkDescriptorSetLayout(FlyDevice *fVkDevice) : FlyDescriptorSetLayout(fVkDevice) {}
    ~FVkDescriptorSetLayout() {}
    
    virtual void Destroy() override;
    virtual void Initialize(const DescriptorSetLayoutInfo &info) override;
};

}  // namespace FlyEngine::Backend