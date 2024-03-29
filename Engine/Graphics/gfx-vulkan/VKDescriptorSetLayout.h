/****************************************************************************
Copyright (c) 2020 Xiamen Yaji Software Co., Ltd.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#ifndef CC_GFXVULKAN_DESCRIPTOR_SET_LAYOUT_H_
#define CC_GFXVULKAN_DESCRIPTOR_SET_LAYOUT_H_

namespace cc
{
namespace gfx
{

class CCVKGPUDescriptorSetLayout;

class CCVKDescriptorSetLayout final : public DescriptorSetLayout
{
public:
    CCVKDescriptorSetLayout(Device *device);
    ~CCVKDescriptorSetLayout();

public:
    virtual bool initialize(const DescriptorSetLayoutInfo &info) override;
    virtual void destroy() override;

    inline CCVKGPUDescriptorSetLayout *gpuDescriptorSetLayout() const { return _gpuDescriptorSetLayout; }

private:
    CCVKGPUDescriptorSetLayout *_gpuDescriptorSetLayout = nullptr;
};

}  // namespace gfx
}  // namespace cc

#endif  // CC_GFXVULKAN_DESCRIPTOR_SET_LAYOUT_H_
