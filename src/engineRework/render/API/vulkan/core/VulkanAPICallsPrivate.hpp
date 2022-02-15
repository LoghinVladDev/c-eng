//
// Created by loghin on 16.02.2022.
//

#ifndef C_ENG_VULKANAPICALLSPRIVATE_HPP
#define C_ENG_VULKANAPICALLSPRIVATE_HPP

#include <VulkanCoreConfig.hpp>

#define __C_ENG_LOOKUP_VULKAN_FUNCTION(_fName)                                          \
    static PFN_ ## _fName _fName ## Handle;                                             \
    if ( _fName ## Handle == nullptr ) {                                                \
        if (                                                                            \
                auto lResult = vulkan :: getFunctionAddress (                           \
                    # _fName,                                                           \
                    reinterpret_cast < FunctionHandleAddress > ( & _fName ## Handle )   \
                );                                                                      \
                lResult != vulkan :: ResultSuccess                                      \
        ) {                                                                             \
            return lResult;                                                             \
        }                                                                               \
    }

#define __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION(_instance, _fName)                      \
    static PFN_ ## _fName _fName ## Handle;                                             \
    if ( _fName ## Handle == nullptr ) {                                                \
        if (                                                                            \
                auto lResult = vulkan :: getInstanceFunctionAddress (                   \
                    _instance,                                                          \
                    # _fName,                                                           \
                    reinterpret_cast < FunctionHandleAddress > ( & _fName ## Handle )   \
                );                                                                      \
                lResult != vulkan :: ResultSuccess                                      \
        ) {                                                                             \
            return lResult;                                                             \
        }                                                                               \
    }

#define __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_2(_instance, _fName, _ext)                  \
    static PFN_ ## _fName _fName ## Handle;                                                 \
    if ( _fName ## Handle == nullptr ) {                                                    \
        if (                                                                                \
                auto lResult = vulkan :: getInstanceFunctionAddress (                       \
                    _instance,                                                              \
                    # _fName,                                                               \
                    reinterpret_cast < FunctionHandleAddress > ( & _fName ## Handle )       \
                );                                                                          \
                lResult != vulkan :: ResultSuccess                                          \
        ) {                                                                                 \
            if (                                                                            \
                    lResult = vulkan :: getInstanceFunctionAddress (                        \
                        _instance,                                                          \
                        __C_ENG_STRINGIFY ( _fName ## _ext ),                               \
                        reinterpret_cast < FunctionHandleAddress > ( & _fName ## Handle )   \
                    );                                                                      \
                    lResult != vulkan :: ResultSuccess                                      \
            ) {                                                                             \
                return lResult;                                                             \
            }                                                                               \
        }                                                                                   \
    }

#define __C_ENG_LOOKUP_VULKAN_DEVICE_FUNCTION_2(_device, _fName, _ext)                      \
    static PFN_ ## _fName _fName ## Handle;                                                 \
    if ( _fName ## Handle == nullptr ) {                                                    \
        if (                                                                                \
                auto lResult = vulkan :: getDeviceFunctionAddress (                         \
                    _device,                                                                \
                    # _fName,                                                               \
                    reinterpret_cast < FunctionHandleAddress > ( & _fName ## Handle )       \
                );                                                                          \
                lResult != vulkan :: ResultSuccess                                          \
        ) {                                                                                 \
            if (                                                                            \
                    lResult = vulkan :: getDeviceFunctionAddress (                          \
                        _device,                                                            \
                        __C_ENG_STRINGIFY ( _fName ## _ext ),                               \
                        reinterpret_cast < FunctionHandleAddress > ( & _fName ## Handle )   \
                    );                                                                      \
                    lResult != vulkan :: ResultSuccess                                      \
            ) {                                                                             \
                return lResult;                                                             \
            }                                                                               \
        }                                                                                   \
    }

#define __C_ENG_LOOKUP_VULKAN_DEVICE_FUNCTION(_device, _fName)                          \
    static PFN_ ## _fName _fName ## Handle;                                             \
    if ( _fName ## Handle == nullptr ) {                                                \
        if (                                                                            \
                auto lResult = vulkan :: getDeviceFunctionAddress (                     \
                    _device,                                                            \
                    # _fName,                                                           \
                    reinterpret_cast < FunctionHandleAddress > ( & _fName ## Handle )   \
                );                                                                      \
                lResult != vulkan :: ResultSuccess                                      \
        ) {                                                                             \
            return lResult;                                                             \
        }                                                                               \
    }


using FunctionHandleAddress = void **;


#endif //C_ENG_VULKANAPICALLSPRIVATE_HPP
