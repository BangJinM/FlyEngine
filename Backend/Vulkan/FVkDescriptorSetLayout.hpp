#pragma once

#include "../Core/FlyDescriptorSetLayout.hpp"

#include "FVkDefine.hpp"

namespace FlyEngine::Backend
{
class FVkDescriptorSetLayout : public FlyDescriptorSetLayout
{
public:
    FVkDescriptorSetLayout(FlyDevice *fVkDevice) : FlyDescriptorSetLayout(fVkDevice) {}
    ~FVkDescriptorSetLayout() {}
    
    virtual void Destroy() override;
    virtual void Initialize(const DescriptorSetLayoutInfo &info) override;

private:
    VkDescriptorSetLayout descriptorSetLayout;

    DescriptorSetLayoutInfo descriptorSetLayoutInfo;
};

}  // namespace FlyEngine::Backend