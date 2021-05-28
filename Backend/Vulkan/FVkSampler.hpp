#include "../Core/FlySampler.hpp"

#include "FVkDefine.hpp"

namespace FlyEngine::Backend
{
class FVkSampler : public FlySampler
{
public:
    FVkSampler(FlyDevice *fVkDevice) : FlySampler(fVkDevice) {}
    ~FVkSampler() {}

    virtual void Destroy() override;
    virtual void Initialize(const SamplerInfo &info) override;

private:
    VkSampler textureSampler;
};

}  // namespace FlyEngine::Backend