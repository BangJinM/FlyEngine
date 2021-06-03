#include "FVkDescriptorSetLayout.hpp"
#include "FVkDevice.hpp"
#include "FVkFunc.hpp"
namespace FlyEngine::Backend
{
void FVkDescriptorSetLayout::Destroy()
{
    FVkDevice *fVkDevice = (FVkDevice *)pFlyDevice;
    VkDevice & device    = fVkDevice->GetVkDevice();

    vkDestroyDescriptorSetLayout(device, descriptorSetLayout, nullptr);
}

void FVkDescriptorSetLayout::Initialize(const DescriptorSetLayoutInfo &info)
{
    descriptorSetLayoutInfo = info;

    FVkDevice *fVkDevice = (FVkDevice *)pFlyDevice;
    VkDevice & device    = fVkDevice->GetVkDevice();

    std::vector<VkDescriptorSetLayoutBinding> bindings;

    for (size_t i = 0; i < info.descriptorSetLayoutBindingInfoList.size(); i++)
    {
        DescriptorSetLayoutBindingInfo layoutBindingInfo = info.descriptorSetLayoutBindingInfoList[i];

        VkDescriptorSetLayoutBinding layoutBinding{};
        layoutBinding.binding         = layoutBindingInfo.binding;
        layoutBinding.descriptorCount = layoutBindingInfo.descriptorCount;
        layoutBinding.descriptorType  = MapVkDescriptorType(layoutBindingInfo.descriptorType);
        layoutBinding.stageFlags      = MapVkShaderStageFlagBits(layoutBindingInfo.stageFlags);
        bindings.push_back(layoutBinding);
    }

    VkDescriptorSetLayoutCreateInfo layoutInfo{};
    layoutInfo.sType        = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    layoutInfo.bindingCount = static_cast<uint32_t>(bindings.size());
    layoutInfo.pBindings    = bindings.data();

    if (vkCreateDescriptorSetLayout(device, &layoutInfo, nullptr, &descriptorSetLayout) != VK_SUCCESS)
    {}
}
}  // namespace FlyEngine::Backend