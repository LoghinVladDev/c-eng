//
// Created by loghin on 26.12.2021.
//

#ifndef __C_ENG_VULKANCORE_HPP
#define __C_ENG_VULKANCORE_HPP

#include <Preprocess.hpp>
#include <CDS/Types>
#include <CDS/Limits>


#define __C_ENG_VULKAN_API_AVAILABLE false
#define __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE false
#define __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE false
#define __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE false

#define __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SURFACE_AVAILABLE false
#define __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SWAP_CHAIN_AVAILABLE false
#define __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DISPLAY_SWAP_CHAIN_AVAILABLE false
#define __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DEFERRED_HOST_OPERATIONS_AVAILABLE false
#define __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_AVAILABLE false
#define __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_MEMORY_AVAILABLE false

#define __C_ENG_VULKAN_API_EXTENSION_NVIDIA_GLSL_SHADER_AVAILABLE false

#define __C_ENG_VULKAN_API_EXTENSION_DEBUG_REPORT_AVAILABLE false
#define __C_ENG_VULKAN_API_EXTENSION_IMAGE_DRM_FORMAT_MODIFIER_AVAILABLE false
#define __C_ENG_VULKAN_API_EXTENSION_GLOBAL_PRIORITY_AVAILABLE false
#define __C_ENG_VULKAN_API_EXTENSION_FULL_SCREEN_EXCLUSIVE_AVAILABLE false
#define __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_CACHE_CONTROL_AVAILABLE false
#define __C_ENG_VULKAN_API_EXTENSION_DESCRIPTOR_INDEXING_AVAILABLE false
#define __C_ENG_VULKAN_API_EXTENSION_BUFFER_DEVICE_ADDRESS_AVAILABLE false


#if defined ( VK_VERSION_1_0 )

#undef  __C_ENG_VULKAN_API_AVAILABLE
#define __C_ENG_VULKAN_API_AVAILABLE true

#undef  __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE true

#endif


#if defined ( VK_VERSION_1_1 )

#undef  __C_ENG_VULKAN_API_AVAILABLE
#define __C_ENG_VULKAN_API_AVAILABLE true

#undef  __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE true

#undef  __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
#define __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE true

#endif


#if defined ( VK_VERSION_1_2 )

#undef  __C_ENG_VULKAN_API_AVAILABLE
#define __C_ENG_VULKAN_API_AVAILABLE true

#undef  __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE true

#undef  __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
#define __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE true

#undef  __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
#define __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE true

#endif


#if defined(VK_KHR_surface)

#undef  __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SURFACE_AVAILABLE
#define __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SURFACE_AVAILABLE true

#endif


#if defined(VK_KHR_swapchain)

#undef  __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SWAP_CHAIN_AVAILABLE
#define __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SWAP_CHAIN_AVAILABLE true

#endif


#if defined(VK_KHR_display_swapchain)

#undef __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DISPLAY_SWAP_CHAIN_AVAILABLE
#define __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DISPLAY_SWAP_CHAIN_AVAILABLE true

#endif


#if defined(VK_KHR_deferred_host_operations)

#undef __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DEFERRED_HOST_OPERATIONS_AVAILABLE
#define __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DEFERRED_HOST_OPERATIONS_AVAILABLE true

#endif


#if defined(VK_KHR_maintenance1)

#undef __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_AVAILABLE
#define __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_AVAILABLE true

#endif


#if defined(VK_KHR_external_memory)

#undef __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_MEMORY_AVAILABLE
#define __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_MEMORY_AVAILABLE true

#endif


#if defined(VK_NV_glsl_shader)

#undef __C_ENG_VULKAN_API_EXTENSION_NVIDIA_GLSL_SHADER_AVAILABLE
#define __C_ENG_VULKAN_API_EXTENSION_NVIDIA_GLSL_SHADER_AVAILABLE true

#endif


#if defined(VK_EXT_debug_report)

#undef __C_ENG_VULKAN_API_EXTENSION_DEBUG_REPORT_AVAILABLE
#define __C_ENG_VULKAN_API_EXTENSION_DEBUG_REPORT_AVAILABLE true

#endif


#if defined(VK_EXT_image_drm_format_modifier)

#undef __C_ENG_VULKAN_API_EXTENSION_IMAGE_DRM_FORMAT_MODIFIER_AVAILABLE
#define __C_ENG_VULKAN_API_EXTENSION_IMAGE_DRM_FORMAT_MODIFIER_AVAILABLE true

#endif


#if defined(VK_EXT_global_priority)

#undef __C_ENG_VULKAN_API_EXTENSION_GLOBAL_PRIORITY_AVAILABLE
#define __C_ENG_VULKAN_API_EXTENSION_GLOBAL_PRIORITY_AVAILABLE true

#endif


#if defined(VK_EXT_full_screen_exclusive)

#undef __C_ENG_VULKAN_API_EXTENSION_FULL_SCREEN_EXCLUSIVE_AVAILABLE
#define __C_ENG_VULKAN_API_EXTENSION_FULL_SCREEN_EXCLUSIVE_AVAILABLE true

#endif


#if defined(VK_EXT_pipeline_creation_cache_control)

#undef __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_CACHE_CONTROL_AVAILABLE
#define __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_CACHE_CONTROL_AVAILABLE true

#endif


#if defined(VK_EXT_descriptor_indexing)

#undef __C_ENG_VULKAN_API_EXTENSION_DESCRIPTOR_INDEXING_AVAILABLE
#define __C_ENG_VULKAN_API_EXTENSION_DESCRIPTOR_INDEXING_AVAILABLE true

#endif


#if defined(VK_KHR_buffer_device_address)

#undef __C_ENG_VULKAN_API_EXTENSION_BUFFER_DEVICE_ADDRESS_AVAILABLE
#define __C_ENG_VULKAN_API_EXTENSION_BUFFER_DEVICE_ADDRESS_AVAILABLE true

#endif




namespace engine { // NOLINT(modernize-concat-nested-namespaces)
    namespace vulkan {

        __C_ENG_ENUM ( Result, cds :: sint32 ) {

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE

            __C_ENG_ENUM_FIELD ( Result, Success,                                   static_cast < cds :: sint32 > ( VkResult :: VK_SUCCESS ) ),
            __C_ENG_ENUM_FIELD ( Result, NotReady,                                  static_cast < cds :: sint32 > ( VkResult :: VK_NOT_READY ) ),
            __C_ENG_ENUM_FIELD ( Result, Timeout,                                   static_cast < cds :: sint32 > ( VkResult :: VK_TIMEOUT ) ),
            __C_ENG_ENUM_FIELD ( Result, EventSet,                                  static_cast < cds :: sint32 > ( VkResult :: VK_EVENT_SET ) ),
            __C_ENG_ENUM_FIELD ( Result, EventReset,                                static_cast < cds :: sint32 > ( VkResult :: VK_EVENT_RESET ) ),
            __C_ENG_ENUM_FIELD ( Result, Incomplete,                                static_cast < cds :: sint32 > ( VkResult :: VK_INCOMPLETE ) ),
            __C_ENG_ENUM_FIELD ( Result, ErrorOutOfHostMemory,                      static_cast < cds :: sint32 > ( VkResult :: VK_ERROR_OUT_OF_HOST_MEMORY ) ),
            __C_ENG_ENUM_FIELD ( Result, ErrorOutOfDeviceMemory,                    static_cast < cds :: sint32 > ( VkResult :: VK_ERROR_OUT_OF_DEVICE_MEMORY ) ),
            __C_ENG_ENUM_FIELD ( Result, ErrorInitializationFailed,                 static_cast < cds :: sint32 > ( VkResult :: VK_ERROR_INITIALIZATION_FAILED ) ),
            __C_ENG_ENUM_FIELD ( Result, ErrorDeviceLost,                           static_cast < cds :: sint32 > ( VkResult :: VK_ERROR_DEVICE_LOST ) ),
            __C_ENG_ENUM_FIELD ( Result, ErrorMemoryMapFailed,                      static_cast < cds :: sint32 > ( VkResult :: VK_ERROR_MEMORY_MAP_FAILED ) ),
            __C_ENG_ENUM_FIELD ( Result, ErrorLayerNotPresent,                      static_cast < cds :: sint32 > ( VkResult :: VK_ERROR_LAYER_NOT_PRESENT ) ),
            __C_ENG_ENUM_FIELD ( Result, ErrorExtensionNotPresent,                  static_cast < cds :: sint32 > ( VkResult :: VK_ERROR_LAYER_NOT_PRESENT ) ),
            __C_ENG_ENUM_FIELD ( Result, ErrorFeatureNotPresent,                    static_cast < cds :: sint32 > ( VkResult :: VK_ERROR_FEATURE_NOT_PRESENT ) ),
            __C_ENG_ENUM_FIELD ( Result, ErrorIncompatibleDriver,                   static_cast < cds :: sint32 > ( VkResult :: VK_ERROR_INCOMPATIBLE_DRIVER ) ),
            __C_ENG_ENUM_FIELD ( Result, ErrorTooManyObjects,                       static_cast < cds :: sint32 > ( VkResult :: VK_ERROR_TOO_MANY_OBJECTS ) ),
            __C_ENG_ENUM_FIELD ( Result, ErrorFormatNotSupported,                   static_cast < cds :: sint32 > ( VkResult :: VK_ERROR_FORMAT_NOT_SUPPORTED ) ),
            __C_ENG_ENUM_FIELD ( Result, ErrorFragmentedPool,                       static_cast < cds :: sint32 > ( VkResult :: VK_ERROR_FRAGMENTED_POOL ) ),
            __C_ENG_ENUM_FIELD ( Result, ErrorUnknown,                              static_cast < cds :: sint32 > ( VkResult :: VK_ERROR_UNKNOWN ) ),

#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

            __C_ENG_ENUM_FIELD ( Result, ErrorOutOfPoolMemory,                      static_cast < cds :: sint32 > ( VkResult :: VK_ERROR_OUT_OF_POOL_MEMORY ) ),
            __C_ENG_ENUM_FIELD ( Result, ErrorInvalidExternalHandle,                static_cast < cds :: sint32 > ( VkResult :: VK_ERROR_INVALID_EXTERNAL_HANDLE ) ),

#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE

            __C_ENG_ENUM_FIELD ( Result, ErrorFragmentation,                        static_cast < cds :: sint32 > ( VkResult :: VK_ERROR_FRAGMENTATION ) ),
            __C_ENG_ENUM_FIELD ( Result, ErrorInvalidOpaqueCaptureAddress,          static_cast < cds :: sint32 > ( VkResult :: VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS ) ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SURFACE_AVAILABLE

            __C_ENG_ENUM_FIELD ( Result, ErrorSurfaceLost,                          static_cast < cds :: sint32 > ( VkResult :: VK_ERROR_SURFACE_LOST_KHR ) ),
            __C_ENG_ENUM_FIELD ( Result, ErrorNativeWindowInUse,                    static_cast < cds :: sint32 > ( VkResult :: VK_ERROR_NATIVE_WINDOW_IN_USE_KHR ) ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DISPLAY_SWAP_CHAIN_AVAILABLE

            __C_ENG_ENUM_FIELD ( Result, ErrorIncompatibleDisplay,                  static_cast < cds :: sint32 > ( VkResult :: VK_ERROR_INCOMPATIBLE_DISPLAY_KHR ) ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DEFERRED_HOST_OPERATIONS_AVAILABLE

            __C_ENG_ENUM_FIELD ( Result, ThreadIdle,                                static_cast < cds :: sint32 > ( VkResult :: VK_THREAD_IDLE_KHR ) ),
            __C_ENG_ENUM_FIELD ( Result, ThreadDone,                                static_cast < cds :: sint32 > ( VkResult :: VK_THREAD_DONE_KHR ) ),
            __C_ENG_ENUM_FIELD ( Result, OperationDeferred,                         static_cast < cds :: sint32 > ( VkResult :: VK_OPERATION_DEFERRED_KHR ) ),
            __C_ENG_ENUM_FIELD ( Result, OperationNotDeferred,                      static_cast < cds :: sint32 > ( VkResult :: VK_OPERATION_NOT_DEFERRED_KHR ) ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_GLSL_SHADER_AVAILABLE

            __C_ENG_ENUM_FIELD ( Result, ErrorInvalidShader,                        static_cast < cds :: sint32 > ( VkResult :: VK_ERROR_INVALID_SHADER_NV ) ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEBUG_REPORT_AVAILABLE

            __C_ENG_ENUM_FIELD ( Result, ErrorValidationFailed,                     static_cast < cds :: sint32 > ( VkResult :: VK_ERROR_VALIDATION_FAILED_EXT ) ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_DRM_FORMAT_MODIFIER_AVAILABLE

            __C_ENG_ENUM_FIELD ( Result, ErrorInvalidDRMFormatModifierPlaneLayout,  static_cast < cds :: sint32 > ( VkResult :: VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT ) ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GLOBAL_PRIORITY_AVAILABLE

            __C_ENG_ENUM_FIELD ( Result, ErrorNotPermitted,                         static_cast < cds :: sint32 > ( VkResult :: VK_ERROR_NOT_PERMITTED_EXT ) ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FULL_SCREEN_EXCLUSIVE_AVAILABLE

            __C_ENG_ENUM_FIELD ( Result, ErrorFullScreenExclusiveModeLost,          static_cast < cds :: sint32 > ( VkResult :: VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT ) ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_CACHE_CONTROL_AVAILABLE

            __C_ENG_ENUM_FIELD ( Result, PipelineCompileRequired,                   static_cast < cds :: sint32 > ( VkResult :: VK_PIPELINE_COMPILE_REQUIRED_EXT ) ),

#endif

            __C_ENG_ENUM_FIELD ( Result, Unknown,                                   cds :: limits :: S32_MAX )

        };

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE

        __C_ENG_ALIAS ( Offset2D, VkOffset2D );
        __C_ENG_ALIAS ( Offset3D, VkOffset3D );

        __C_ENG_ALIAS ( Extent2D, VkExtent2D );
        __C_ENG_ALIAS ( Extent3D, VkExtent3D );

        __C_ENG_ALIAS ( Rect, VkRect2D );

#endif

        __C_ENG_ENUM ( StructureType, cds :: sint32 ) {

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE

            __C_ENG_ENUM_FIELD ( StructureType, ApplicationInfo,            static_cast < cds :: sint32 > ( VkStructureType :: VK_STRUCTURE_TYPE_APPLICATION_INFO ) ),
            __C_ENG_ENUM_FIELD ( StructureType, InstanceCreateInfo,         static_cast < cds :: sint32 > ( VkStructureType :: VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO ) ),

#endif

        };

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( Result ) ) noexcept -> cds :: StringLiteral;

    }
}

#endif //__C_ENG_VULKANCORE_HPP
