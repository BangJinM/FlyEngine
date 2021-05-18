
file(GLOB_RECURSE HEADER_FILES *.h)
file(GLOB_RECURSE HEADER_FILES *.hpp)
file(GLOB_RECURSE SOURCE_CPP_FILES *.cpp *.cc)
file(GLOB_RECURSE SOURCE_C_FILES *.c)

set(ALL_FILES
    ${HEADER_FILES}
    ${SOURCE_CPP_FILES}
    ${SOURCE_C_FILES}
)

find_package(glfw3 CONFIG REQUIRED)
link_libraries(glfw)

add_library(NULL ${HEADER_FILES} ${ALL_FILES})

find_package(Vulkan REQUIRED FATAL_ERROR)

target_link_libraries( NULL
    ${Vulkan_LIBRARIES}
)
target_include_directories (NULL 
    PUBLIC ${Vulkan_INCLUDE_DIRS}
)