//
// Created by Vlad on 12/08/2020.
//

#ifndef ENG1_VKPLATFORMDEFS_H
#define ENG1_VKPLATFORMDEFS_H

#if defined(_WIN32)

#define GLFW_EXPOSE_NATIVE_WIN32
#define VK_USE_PLATFORM_WIN32_KHR /// required for surface object
#define ENGINE_OS_WINDOWS_32_64

#if defined(_WIN64)
#define ENGINE_OS_WINDOWS_64
#endif

#elif defined(__linux__)

//// TODO : add linux platform def
#define ENGINE_OS_LINUX

#elif defined(__APPLE__)

//// TODO : add apple platform def
#define ENGINE_OS_MAC_OS_X

#endif

#endif //ENG1_VKPLATFORMDEFS_H
