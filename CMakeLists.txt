cmake_minimum_required (VERSION 3.1) 
set (CMAKE_C_STANDARD 17)
set (CMAKE_CXX_STANDARD 17)


set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "Vcpkg toolchain file")

if(NOT DEFINED ENV{VCPKG_ROOT})
    message(ERROR "没有找到环境变量:VCPKG_ROOT")
endif()

set(VCPKG_ROOT "$ENV{VCPKG_ROOT}scripts/buildsystems/vcpkg.cmake")
message(STATUS "[VCPKG_ROOT ] ${VCPKG_ROOT}")
set(CMAKE_TOOLCHAIN_FILE ${VCPKG_ROOT} CACHE STRING "")

project(FlyEngine VERSION 0.0.1)
message(STATUS "[Project] ${PROJECT_NAME}")

include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/Engine/")
include_directories("${PROJECT_SOURCE_DIR}/Engine/Core")
include_directories("${PROJECT_SOURCE_DIR}/Engine/Platforms")
include_directories("${PROJECT_SOURCE_DIR}/Engine/Graphics")

if(CMAKE_HOST_WIN32)
    add_definitions("-D_CRT_SECURE_NO_WARNINGS")
	add_definitions("-DVK_USE_PLATFORM_WIN32_KHR")
    add_definitions("-DFLYENGINE_PLATFORM_WIN32")
    find_package(Vulkan REQUIRED FATAL_ERROR)

    include_directories ( 
        PUBLIC ${Vulkan_INCLUDE_DIRS}
    )
# elseif(CMAKE_HOST_APPLE)
# 	add_definitions("-DVK_USE_PLATFORM_METAL_EXT")
# elseif(COCOS_PLATFORM_ANDROID)
# 	add_definitions("-DVK_USE_PLATFORM_ANDROID_KHR")
# else()
# 	add_definitions("-DVK_USE_PLATFORM_XLIB_KHR")
endif()

add_subdirectory(Engine)
add_subdirectory(Game)

message(STATUS "[Project] ${Vulkan_INCLUDE_DIRS}")