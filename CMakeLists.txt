cmake_minimum_required (VERSION 3.1) 
set (CMAKE_C_STANDARD 17)
set (CMAKE_CXX_STANDARD 17)

if (CMAKE_HOST_WIN32)
    set(WINDOWS 1)
    set(VULKAN 1)
    add_definitions("-D WIN32")
    add_definitions("-D BACKEND_VULKAN")
elseif(CMAKE_HOST_APPLE)
    set(MACOS 1)
elseif(CMAKE_HOST_UNIX)
    set(LINUX 1)
endif()


if(WINDOWS)
    set(VCPKG_TARGET_TRIPLET x86-windows)
    message(STATUS "VCPKG_TARGET_TRIPLET：x86-windows")
else()
    set(VCPKG_TARGET_TRIPLET x86-windows)
endif()

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

add_subdirectory(Engine)
add_subdirectory(Game)

message(STATUS "[Project] ${Vulkan_INCLUDE_DIRS}")