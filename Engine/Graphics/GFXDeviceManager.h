/****************************************************************************
 Copyright (c) 2019-2022 Xiamen Yaji Software Co., Ltd.

 http://www.cocos.com

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated engine source code (the "Software"), a limited,
 worldwide, royalty-free, non-assignable, revocable and non-exclusive license
 to use Cocos Creator solely to develop games on your target platforms. You shall
 not use Cocos Creator software for developing other software or tools that's
 used for developing games. You are not granted to publish, distribute,
 sublicense, and/or sell copies of Cocos Creator.

 The software or tools in this License Agreement are licensed, not sold.
 Xiamen Yaji Software Co., Ltd. reserves all rights not expressly granted to you.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
****************************************************************************/

#pragma once

#include "Graphics/core/Core.h"
#include "Graphics/core/gfx/GFXDevice.h"

//#undef CC_USE_NVN
//#undef CC_USE_VULKAN
//#undef CC_USE_METAL
//#undef CC_USE_GLES3
//#undef CC_USE_GLES2

// #ifdef CC_USE_NVN
// #    include "gfx-nvn/NVNDevice.h"
// #endif

#include "Graphics/gfx-vulkan/VKDevice.h"

// #ifdef CC_USE_METAL
// #    include "gfx-metal/MTLDevice.h"
// #endif

// #ifdef CC_USE_GLES3
// #    include "gfx-gles3/GLES3Device.h"
// #endif

// #ifdef CC_USE_GLES2
// #    include "gfx-gles2/GLES2Device.h"
// #endif

namespace cc
{
namespace gfx
{

class DeviceManager final
{
    static constexpr bool DETACH_DEVICE_THREAD{true};
    static constexpr bool FORCE_DISABLE_VALIDATION{false};
    static constexpr bool FORCE_ENABLE_VALIDATION{false};

public:
    static Device *create(const DeviceInfo &info)
    {
        // if (Device::instance)
        //     return Device::instance;

        Device *device = new CCVKDevice();

        if (!device)
            return nullptr;
        if (!device->initialize(info))
        {
            CC_SAFE_DELETE(device);
            return nullptr;
        }

        return device;
    }

    static constexpr bool isDetachDeviceThread() { return DETACH_DEVICE_THREAD; }

    static std::string getGFXName()
    {
        std::string gfx = "unknown";
        gfx             = "Vulkan";

        return gfx;
    }

private:
    static void addSurfaceEventListener()
    {
        // Device *device = Device::instance;
        // EventDispatcher::addCustomEventListener(EVENT_DESTROY_WINDOW,
        //                                         [device](const CustomEvent &e) -> void { device->destroySurface(e.args->ptrVal); });

        // EventDispatcher::addCustomEventListener(EVENT_RECREATE_WINDOW,
        //                                         [device](const CustomEvent &e) -> void { device->createSurface(e.args->ptrVal); });
    }

    // template <typename DeviceCtor, typename Enable = std::enable_if_t<std::is_base_of<Device, DeviceCtor>::value>>
    // static bool tryCreate(const DeviceInfo &info, Device **pDevice)
    // {
    //     Device *device = new DeviceCtor;

    //     if (!device->initialize(info))
    //     {
    //         CC_SAFE_DELETE(device);
    //         return false;
    //     }

    //     addSurfaceEventListener();
    //     *pDevice = device;

    //     return true;
    // }

    // #ifndef CC_DEBUG
    //     static constexpr int CC_DEBUG{0};
    // #endif
};

}  // namespace gfx
}  // namespace cc
