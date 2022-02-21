//
// Created by loghin on 16.02.2022.
//

#ifndef C_ENG_VULKANAPICALLSPRIVATE_HPP
#define C_ENG_VULKANAPICALLSPRIVATE_HPP

#include <VulkanAPICalls.hpp>
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

#define __C_ENG_LOOKUP_VULKAN_FUNCTION_R(_fName)                                            \
    static PFN_ ## _fName _fName ## Handle;                                                 \
    static Mutex _fName ## Lock;                                                            \
    if ( _fName ## Handle == nullptr ) {                                                    \
        LockGuard guard ( _fName ## Lock );                                                 \
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
        }                                                                                   \
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

#define __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R(_instance, _fName)                        \
    static PFN_ ## _fName _fName ## Handle;                                                 \
    static Mutex _fName ## Lock;                                                            \
    if ( _fName ## Handle == nullptr ) {                                                    \
        LockGuard guard ( _fName ## Lock );                                                 \
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
        }                                                                                   \
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

#define __C_ENG_LOOKUP_VULKAN_DEVICE_FUNCTION_R(_device, _fName)                            \
    static PFN_ ## _fName _fName ## Handle;                                                 \
    static Mutex _fName ## Lock;                                                            \
    if ( _fName ## Handle == nullptr ) {                                                    \
        LockGuard guard ( _fName ## Lock );                                                 \
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
        }                                                                                   \
    }


using FunctionHandleAddress = void **;


#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
using VkDevicePrivateDataCreateInfo_t   = VkDevicePrivateDataCreateInfo;
#elif __C_ENG_VULKAN_API_EXTENSION_PRIVATE_DATA_AVAILABLE
using VkDevicePrivateDataCreateInfo_t   = VkDevicePrivateDataCreateInfoEXT;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
using VkPhysicalDeviceDynamicRenderingFeatures_t    = VkPhysicalDeviceDynamicRenderingFeatures;
#elif __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE
using VkPhysicalDeviceDynamicRenderingFeatures_t    = VkPhysicalDeviceDynamicRenderingFeaturesKHR;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
using VkPhysicalDeviceImageRobustnessFeatures_t     = VkPhysicalDeviceImageRobustnessFeatures;
#elif __C_ENG_VULKAN_API_EXTENSION_IMAGE_ROBUSTNESS_AVAILABLE
using VkPhysicalDeviceImageRobustnessFeatures_t     = VkPhysicalDeviceImageRobustnessFeaturesEXT;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
using VkPhysicalDeviceInlineUniformBlockFeatures_t      = VkPhysicalDeviceInlineUniformBlockFeatures;
using VkPhysicalDeviceInlineUniformBlockProperties_t    = VkPhysicalDeviceInlineUniformBlockProperties;
#elif __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE
using VkPhysicalDeviceInlineUniformBlockFeatures_t  = VkPhysicalDeviceInlineUniformBlockFeaturesEXT;
using VkPhysicalDeviceInlineUniformBlockProperties_t    = VkPhysicalDeviceInlineUniformBlockPropertiesEXT;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
using VkPhysicalDeviceMaintenance4Features_t        = VkPhysicalDeviceMaintenance4Features;
using VkPhysicalDeviceMaintenance4Properties_t      = VkPhysicalDeviceMaintenance4Properties;
#elif __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_4_AVAILABLE
using VkPhysicalDeviceMaintenance4Features_t        = VkPhysicalDeviceMaintenance4FeaturesKHR;
using VkPhysicalDeviceMaintenance4Properties_t      = VkPhysicalDeviceMaintenance4PropertiesKHR;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
using VkPhysicalDevicePipelineCreationCacheControlFeatures_t    = VkPhysicalDevicePipelineCreationCacheControlFeatures;
#elif __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_CACHE_CONTROL_AVAILABLE
using VkPhysicalDevicePipelineCreationCacheControlFeatures_t    = VkPhysicalDevicePipelineCreationCacheControlFeaturesEXT;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
using VkPhysicalDevicePrivateDataFeatures_t                     = VkPhysicalDevicePrivateDataFeatures;
#elif __C_ENG_VULKAN_API_EXTENSION_PRIVATE_DATA_AVAILABLE
using VkPhysicalDevicePrivateDataFeatures_t                     = VkPhysicalDevicePrivateDataFeaturesEXT;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
using VkPhysicalDeviceShaderDemoteToHelperInvocationFeatures_t  = VkPhysicalDeviceShaderDemoteToHelperInvocationFeatures;
#elif __C_ENG_VULKAN_API_EXTENSION_SHADER_DEMOTE_TO_HELPER_INVOCATION_AVAILABLE
using VkPhysicalDeviceShaderDemoteToHelperInvocationFeatures_t  = VkPhysicalDeviceShaderDemoteToHelperInvocationFeaturesEXT;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
using VkPhysicalDeviceShaderTerminateInvocationFeatures_t       = VkPhysicalDeviceShaderTerminateInvocationFeatures;
#elif __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_TERMINATE_INVOCATION_AVAILABLE
using VkPhysicalDeviceShaderTerminateInvocationFeatures_t       = VkPhysicalDeviceShaderTerminateInvocationFeaturesKHR;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
using VkPhysicalDeviceSubgroupSizeControlFeatures_t             = VkPhysicalDeviceSubgroupSizeControlFeatures;
using VkPhysicalDeviceSubgroupSizeControlProperties_t           = VkPhysicalDeviceSubgroupSizeControlProperties;
#elif __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE
using VkPhysicalDeviceSubgroupSizeControlFeatures_t             = VkPhysicalDeviceSubgroupSizeControlFeaturesEXT;
using VkPhysicalDeviceSubgroupSizeControlProperties_t           = VkPhysicalDeviceSubgroupSizeControlPropertiesEXT;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
using VkPhysicalDeviceSynchronization2Features_t                = VkPhysicalDeviceSynchronization2Features;
#elif __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE
using VkPhysicalDeviceSynchronization2Features_t                = VkPhysicalDeviceSynchronization2FeaturesKHR;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
using VkPhysicalDeviceTexelBufferAlignmentFeatures_t            = VkPhysicalDeviceTexelBufferAlignmentFeaturesEXT;
using VkPhysicalDeviceTexelBufferAlignmentProperties_t          = VkPhysicalDeviceTexelBufferAlignmentProperties;
#elif __C_ENG_VULKAN_API_EXTENSION_TEXEL_BUFFER_ALIGNMENT_AVAILABLE
using VkPhysicalDeviceTexelBufferAlignmentFeatures_t            = VkPhysicalDeviceTexelBufferAlignmentFeaturesEXT;
using VkPhysicalDeviceTexelBufferAlignmentProperties_t          = VkPhysicalDeviceTexelBufferAlignmentPropertiesEXT;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
using VkPhysicalDeviceTextureCompressionASTCHDRFeatures_t       = VkPhysicalDeviceTextureCompressionASTCHDRFeatures;
#elif __C_ENG_VULKAN_API_EXTENSION_TEXTURE_COMPRESSION_ASTC_HDR_AVAILABLE
using VkPhysicalDeviceTextureCompressionASTCHDRFeatures_t       = VkPhysicalDeviceTextureCompressionASTCHDRFeaturesEXT;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
using VkPhysicalDeviceShaderIntegerDotProductFeatures_t         = VkPhysicalDeviceShaderIntegerDotProductFeatures;
using VkPhysicalDeviceShaderIntegerDotProductProperties_t       = VkPhysicalDeviceShaderIntegerDotProductProperties;
#elif __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_INTEGER_DOT_PRODUCT_AVAILABLE
using VkPhysicalDeviceShaderIntegerDotProductFeatures_t         = VkPhysicalDeviceShaderIntegerDotProductFeaturesKHR;
using VkPhysicalDeviceShaderIntegerDotProductProperties_t       = VkPhysicalDeviceShaderIntegerDotProductPropertiesKHR;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
using VkPhysicalDeviceZeroInitializeWorkgroupMemoryFeatures_t   = VkPhysicalDeviceZeroInitializeWorkgroupMemoryFeatures;
#elif __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ZERO_INITIALIZE_WORKGROUP_MEMORY_AVAILABLE
using VkPhysicalDeviceZeroInitializeWorkgroupMemoryFeatures_t   = VkPhysicalDeviceZeroInitializeWorkgroupMemoryFeaturesKHR;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
using VkCommandBufferInheritanceRenderingInfo_t                 = VkCommandBufferInheritanceRenderingInfo;
#elif __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE
using VkCommandBufferInheritanceRenderingInfo_t                 = VkCommandBufferInheritanceRenderingInfoKHR;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
using VkDeviceGroupDeviceCreateInfo_t                           = VkDeviceGroupDeviceCreateInfo;
#elif __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DEVICE_GROUP_AVAILABLE
using VkDeviceGroupDeviceCreateInfo_t                           = VkDeviceGroupDeviceCreateInfoKHR;
#endif


#endif //C_ENG_VULKANAPICALLSPRIVATE_HPP
