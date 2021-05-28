#include "FVkShader.hpp"

#include "FVkDevice.hpp"
#include "FVkFunc.hpp"

namespace FlyEngine::Backend
{
void FVkShader::Destroy()
{
    FVkDevice *fVkDevice = (FVkDevice *)pFlyDevice;
    VkDevice & device    = fVkDevice->GetContext()->GetVkDevice();

    for (size_t i = 0; i < stages.size(); i++)
    {
        vkDestroyShaderModule(device, stages[i].module, nullptr);
    }
}

void FVkShader::Initialize(const ShaderInfo &info)
{
    FVkDevice *fVkDevice = (FVkDevice *)pFlyDevice;
    VkDevice & device    = fVkDevice->GetContext()->GetVkDevice();

    for (size_t i = 0; i < info.shaderStageList.size(); i++)
    {
        auto stageInfo = info.shaderStageList[i];

        auto module = createShaderModule(stageInfo.source);

        VkPipelineShaderStageCreateInfo vertShaderStageInfo{};
        vertShaderStageInfo.sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        vertShaderStageInfo.stage  = MapVkShaderStageFlagBits(stageInfo.stage);
        vertShaderStageInfo.module = module;
        vertShaderStageInfo.pName  = info.name.c_str();

        stages.push_back(vertShaderStageInfo);
    }
}

VkShaderModule FVkShader::createShaderModule(const std::string source)
{
    FVkDevice *fVkDevice = (FVkDevice *)pFlyDevice;
    VkDevice & device    = fVkDevice->GetContext()->GetVkDevice();

    VkShaderModuleCreateInfo createInfo{};
    createInfo.sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = source.size();
    createInfo.pCode    = reinterpret_cast<const uint32_t *>(source.data());

    VkShaderModule shaderModule;
    if (vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS)
    {
        printf("dadadada");
    }

    return shaderModule;
}
}  // namespace FlyEngine::Backend