cmake_minimum_required(VERSION 3.5)
project(c-eng)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 23)
set(OpenGL_GL_PREFERENCE GLVND)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

if(MSVC)
    add_compile_options("$<$<CONFIG:RELEASE>:/O2>")
else()
    add_compile_options("$<$<CONFIG:RELEASE>:-O3>")
endif()

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_subdirectory(dependencies/glfw)
add_subdirectory(dependencies/glm)
add_subdirectory(dependencies/meshLoader)

include_directories(dependencies/glm)
include_directories(dependencies/glfw/include)
include_directories(dependencies/stb)
include_directories(dependencies/cds/include)
include_directories(dependencies/meshLoader/include)

find_package(OpenGL REQUIRED)

if(ASSIMP_FOUND)
    include_directories(${ASSIMP_INCLUDE_DIR})
endif()


if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_compile_options(-fprofile-instr-generate -fcoverage-mapping)
    add_link_options(-fprofile-instr-generate)
    #Uncomment in case of linker errors
    #link_libraries(clang_rt.profile-x86_64)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_compile_options(--coverage)
    #Uncomment in case of linker errors
    #if(WIN32)
        link_libraries(gcov)
    #endif()
endif ()

if (WIN32)
    if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:preprocessor")
    endif()
endif()


if(
        NOT $ENV{VULKAN_SDK} STREQUAL "" AND
        NOT $ENV{LD_LIBRARY_PATH} STREQUAL "" AND
        NOT $ENV{VK_LAYER_PATH} STREQUAL ""
)

    include_directories( $ENV{VULKAN_SDK}/include )

    message(-- LOCAL_VULKAN_PATH :   $ENV{VULKAN_SDK} )
    message(-- LOCAL_VULKAN_LIBS :   $ENV{LD_LIBRARY_PATH} )

    set(VK_LD_ITEM vulkan)

else()

    find_package(Vulkan)
    if(Vulkan_FOUND)
        include_directories( ${Vulkan_INCLUDE_DIRS} )

        message(-- VULKAN_PATH :   ${Vulkan_LIBRARY} )

        set(VK_LD_ITEM Vulkan::Vulkan)

    endif()

endif()

set (CMAKE_EXPORT_COMPILE_COMMANDS 1)

add_executable(
        standalone

        src/engine_v6/variant/TargetStandalone.cpp
        src/engine_v6/base/logging/Logger.cpp)

target_include_directories (
        standalone PRIVATE
        src/engine_v6/base
        src/engine_v6/impl
        src/engine_v6/variant
)
