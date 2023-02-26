cmake_minimum_required(VERSION 3.5)
project(c-eng)

set(CMAKE_CXX_STANDARD 20)
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

set (
        V4_BASE_CORE

        src/engine_v4/base/core/Object.cpp
)

set (
        V4_BASE_IO_DISPLAY

        src/engine_v4/base/io/display/Display.cpp
        src/engine_v4/base/io/display/Surface.cpp
        src/engine_v4/base/io/display/Window.cpp
)

set (
        V4_BASE_IO_LOGGING

        src/engine_v4/base/io/logging/Logger.cpp
)

set (
        V4_BASE_IO

        ${V4_BASE_IO_DISPLAY}
        ${V4_BASE_IO_LOGGING}
)

set (
        V4_BASE_STORAGE

        src/engine_v4/base/storage/Storage.cpp
)

set (
        V4_BASE

        ${V4_BASE_CORE}
        ${V4_BASE_IO}
        ${V4_BASE_STORAGE}

        src/engine_v4/base/Engine.cpp
)

set (
        V4_IMPL_GLFW_IO_DISPLAY

        src/engine_v4/impl/glfw/io/display/GlfwDisplay.cpp
)

set (
        V4_IMPL_GLFW_IO

        ${V4_IMPL_GLFW_IO_DISPLAY}
)

set (
        V4_IMPL_GLFW

        ${V4_IMPL_GLFW_IO}

        src/engine_v4/impl/glfw/Glfw.cpp
)

set (
        V4_BARE

        ${V4_BASE}
        ${V4_IMPL_GLFW}

        src/engine_v4/variant/bare/BareEngineBareWindow.cpp
)

set(
        WINDOW_SYSTEM_LD_ITEM glfw
)

add_executable (
        v4_bare

        ${V4_BARE}
)

target_link_libraries (
        v4_bare

        ${VK_LD_ITEM}
        ${WINDOW_SYSTEM_LD_ITEM}
        ${GLFW_LIBRARIES}
)

target_include_directories (
        v4_bare

        PRIVATE

        src/engine_v4
)
