//
// Created by Vlad on 12/08/2020.
//

#ifndef ENG1_VKPLATFORMDEFS_H
#define ENG1_VKPLATFORMDEFS_H

#if defined(_WIN32)

#define GLFW_EXPOSE_NATIVE_WIN32
#define VK_USE_PLATFORM_WIN32_KHR /// required for surface object
#define ENGINE_OS_WINDOWS_32_64

#define WINDOWS_VULKAN_GLSL_COMPILER "glslc"

#if defined(_WIN64)
#define ENGINE_OS_WINDOWS_64
#endif

#elif defined(__linux__)

//// TODO : add linux platform defs

#define GLFW_EXPOSE_NATIVE_XCB
#define VK_USE_PLATFORM_XCB_KHR

#define LINUX_VULKAN_GLSL_COMPILER "glslc"
#define LINUX_VULKAN_GLSL_COMPILER_OUTPUT_ARGUMENT "-o"
#define LINUX_VULKAN_GLSL_COMPILATION_FAILED_RETURN_VALUE 1U
#define LINUX_VULKAN_GLSL_COMPILATION_FAILED_CHILD_RETURN_VALUE 256
#define LINUX_VULKAN_GLSL_DEFAULT_ARGUMENT_COUNT 4

#define ENGINE_OS_LINUX

#elif defined(__APPLE__)

//// TODO : add apple platform def
#define ENGINE_OS_MAC_OS_X

#endif

#endif //ENG1_VKPLATFORMDEFS_H
