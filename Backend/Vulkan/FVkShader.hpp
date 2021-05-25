#pragma once

#include <string>
#include "../Core/FlyShader.hpp"
#include "FVkDefine.hpp"

namespace FlyEngine::Backend
{
class FVkShader : public FlyShader
{
public:
    FVkShader(FlyDevice *flyDevice) : FlyShader(flyDevice) {}
    ~FVkShader() {}

    virtual void Destroy() override;
    virtual void Initialize(const ShaderInfo &info) override;

public:
    std::vector<VkPipelineShaderStageCreateInfo> &GetStages() { return stages; }

private:
    VkShaderModule createShaderModule(const std::string source);

private:
    std::vector<VkPipelineShaderStageCreateInfo> stages;
};

}  // namespace FlyEngine::Backend