if(CMAKE_HOST_WIN32)
    add_definitions("-D_CRT_SECURE_NO_WARNINGS")
	add_definitions("-DVK_USE_PLATFORM_WIN32_KHR")
    add_definitions("-DFLYENGINE_PLATFORM_WIN32")
    add_definitions("-DFLY_USE_VULKAN")
# elseif(CMAKE_HOST_APPLE)
# 	add_definitions("-DVK_USE_PLATFORM_METAL_EXT")
# elseif(COCOS_PLATFORM_ANDROID)
# 	add_definitions("-DVK_USE_PLATFORM_ANDROID_KHR")
# else()
# 	add_definitions("-DVK_USE_PLATFORM_XLIB_KHR")
endif()