# 构建类型，支持Debug Release RelWithDebInfo MinSizeRel，默认为RelWithDebInfo
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING
        "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif()

# C++标准，使用C++17
set (CMAKE_C_STANDARD 17)
set (CMAKE_CXX_STANDARD 17)

# 是否构建代码覆盖率检测任务
option(WITH_COVERAGE "Test code coverage" OFF)

# 是否构建并运行单元测试
option(WITH_TESTS "Build and run tests" ON)
if (WITH_COVERAGE)
    set(WITH_TESTS ON)
endif()

# 设置编译执行文件的导出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/bin)    
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/bin) 

# 设置编译库的导出目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/bin/lib)    
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/bin/lib) 

# 设置库的后缀
set(CMAKE_DEBUG_POSTFIX "_d")    
set(CMAKE_RELEASE_POSTFIX "_r") 

# 设置执行文件的后缀
set_target_properties(${TARGET_NAME} PROPERTIES DEBUG_POSTFIX "_d")     
set_target_properties(${TARGET_NAME} PROPERTIES RELEASE_POSTFIX "_r") 

# 显示所有配置信息
macro(print_config)
    message("")
    message("------------------------------------------------------------------------")
    message("-- Configuring ${PROJECT_NAME} ${PROJECT_VERSION}${VERSION_SUFFIX}")
    message("------------------------------------------------------------------------")
    message("-- CMake              Cmake version and location   ${CMAKE_VERSION} (${CMAKE_COMMAND})")
    message("-- VCPKG              vcpkg root path              ${CMAKE_TOOLCHAIN_FILE} ")
    message("-- Compiler           C++ compiler version         ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
    message("-- TARGET_PLATFORM    Target platform              ${CMAKE_SYSTEM_NAME}")
    message("-- CMAKE_BUILD_TYPE   Build type                   ${CMAKE_BUILD_TYPE}")
    message("-- CMAKE_CXX_STANDARD C++ standard                 ${CMAKE_CXX_STANDARD}")
    message("-- WITH_COVERAGE      Test code coverage           ${WITH_COVERAGE}")
    message("-- WITH_TESTS         Build and run tests          ${WITH_TESTS}")
    message("------------------------------------------------------------------------")
    message("")
endmacro()
print_config()

macro(add_my_test add_test_name)
    message("")
    message("------------------------------------------------------------------------")
    message("-- add_my_test        ${add_test_name}")
    message("------------------------------------------------------------------------")
    message("")

    # 添加测试目标
    add_test(NAME ${add_test_name} COMMAND ${add_test_name})
endmacro(add_my_test)