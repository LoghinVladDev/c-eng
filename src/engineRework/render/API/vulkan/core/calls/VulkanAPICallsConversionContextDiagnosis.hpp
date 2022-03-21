//
// Created by loghin on 07.03.2022.
//

#ifndef __C_ENG_VULKAN_API_CALLS_CONVERSION_CONTEXT_DIAGNOSIS_HPP__
#define __C_ENG_VULKAN_API_CALLS_CONVERSION_CONTEXT_DIAGNOSIS_HPP__

#include <calls/VulkanAPICallsConversion.hpp>
#include <calls/VulkanAPICallsPrivate.hpp>
#include <calls/VulkanAPICallsTypes.hpp>

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

#if defined(__CDS_compiler_clang) || defined(__CDS_compiler_gcc)

#define __C_ENG_DIAG_SET_CONTEXT_ERROR(_pContext, _error, ...)   _pContext->common.diag = { \
    .error      = _error,                                                                   \
    .file       = __FILE__,                                                                 \
    .function   = __PRETTY_FUNCTION__,                                                      \
    .line       = __LINE__,                                                                 \
    .pMessage   = (__VA_ARGS__).copy()                                                      \
};

#elif defined(__CDS_compiler_MinGW)

#define __C_ENG_DIAG_SET_CONTEXT_ERROR(_pContext, _error, ...)   _pContext->common.diag = { \
    .error      = _error,                                                                   \
    .file       = __FILE__,                                                                 \
    .function   = __PRETTY_FUNCTION__,                                                      \
    .line       = __LINE__,                                                                 \
    .pMessage   = (__VA_ARGS__).copy()                                                      \
};

#elif defined(__CDS_compiler_MSVC)

#define __C_ENG_DIAG_SET_CONTEXT_ERROR(_pContext, _error, ...)   _pContext->common.diag = { \
    .error      = _error,                                                                   \
    .file       = __FILE__,                                                                 \
    .function   = __FUNCSIG__,                                                              \
    .line       = __LINE__,                                                                 \
    .pMessage   = (__VA_ARGS__).copy()                                                      \
};

#else

#error Define The __C_ENG_DIAG_SET_CONTEXT_ERROR macro set for the selected compiler

#endif

#else

#define __C_ENG_DIAG_SET_CONTEXT_ERROR(_pContext, _error, ...)

#endif

#endif //__C_ENG_VULKAN_API_CALLS_CONVERSION_CONTEXT_DIAGNOSIS_HPP__
