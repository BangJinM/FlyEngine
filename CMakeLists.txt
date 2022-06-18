cmake_minimum_required (VERSION 3.1) 

set(CMAKE_TOOLCHAIN_FILE D:/Progroms/vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "Vcpkg toolchain file")

project(FlyEngine VERSION 0.0.1)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(Options)
include(Defines)

include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/Engine/")
include_directories("${PROJECT_SOURCE_DIR}/Engine/Core")
include_directories("${PROJECT_SOURCE_DIR}/Engine/Platforms")
include_directories("${PROJECT_SOURCE_DIR}/Engine/Graphics")

add_subdirectory(Engine)
add_subdirectory(Game)
add_subdirectory(App)

# 构建并运行单元测试
if (WITH_TESTS)
    enable_testing()
    add_subdirectory(Test)
endif()
