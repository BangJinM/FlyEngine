#pragma once

#include "Core/PlatformDefine.hpp"

FLYENGINE_PLATFORM_BEGIN_NAMESPACE

struct WinNativeWindow
{
    void *hWnd = nullptr;

    WinNativeWindow() noexcept {}

    explicit WinNativeWindow(void *_hWnd) noexcept : hWnd{_hWnd} {}
};

FLYENGINE_END_NAMESPACE