//
// Created by loghin on 18.04.2025.
//

#pragma once

#ifndef C_ENG_VK_USE_64_BIT_PTR_DEFINES
#if defined(__LP64__) || defined(_WIN64) || (defined(__x86_64__) \
    && !defined(__ILP32__)) || defined(_M_X64) || defined(__ia64) || defined (_M_IA64) \
    || defined(__aarch64__) || defined(__powerpc64__) || (defined(__riscv) && __riscv_xlen == 64)
#define C_ENG_VK_USE_64_BIT_PTR_DEFINES 1
#else
#define C_ENG_VK_USE_64_BIT_PTR_DEFINES 0
#endif
#endif

#ifndef C_ENG_VK_DEFINE_NON_DISPATCHABLE_HANDLE
#if (C_ENG_VK_USE_64_BIT_PTR_DEFINES==1)
#if (defined(__cplusplus) && (__cplusplus >= 201103L)) || (defined(_MSVC_LANG) \
&& (_MSVC_LANG >= 201103L))
#define C_ENG_VK_NULL_HANDLE nullptr
#else
#define C_ENG_VK_NULL_HANDLE ((void*)0)
#endif
#else
#define C_ENG_VK_NULL_HANDLE 0ULL
#endif
#endif

#ifndef C_ENG_VK_NULL_HANDLE
#define C_ENG_VK_NULL_HANDLE 0
#endif

#ifndef C_ENG_VK_DEFINE_HANDLE
#define C_ENG_VK_DEFINE_HANDLE(object) typedef struct object##_T* object
#endif

#ifndef C_ENG_VK_DEFINE_NON_DISPATCHABLE_HANDLE
#if C_ENG_VK_USE_64_BIT_PTR_DEFINES
#define C_ENG_VK_DEFINE_NON_DISPATCHABLE_HANDLE(object) typedef struct object##_T* object
#else
#define C_ENG_VK_DEFINE_NON_DISPATCHABLE_HANDLE(object) typedef uint64_t object
#endif
#endif

extern "C" {
C_ENG_VK_DEFINE_HANDLE(VkInstance);
C_ENG_VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkDebugUtilsMessengerEXT);
// enum VkResult;
}

namespace vk {
using Instance = VkInstance;
using DebugUtilsMessenger = VkDebugUtilsMessengerEXT;

// using Result = VkResult;

inline constexpr auto nullHandle = C_ENG_VK_NULL_HANDLE;
} // namespace vk

#undef C_ENG_VK_USE_64_BIT_PTR_DEFINES
#undef C_ENG_VK_DEFINE_HANDLE
#undef C_ENG_VK_DEFINE_NON_DISPATCHABLE_HANDLE
#undef C_ENG_VK_NULL_HANDLE
