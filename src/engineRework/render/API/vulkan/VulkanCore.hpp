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

#pragma push_macro("__C_ENG_OBJECT_NAME")
#pragma push_macro("__C_ENG_OBJECT_TYPE")

#undef  __C_ENG_OBJECT_NAME
#undef  __C_ENG_OBJECT_TYPE
#define __C_ENG_OBJECT_NAME Result /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_OBJECT_TYPE cds :: sint32 /* NOLINT(bugprone-reserved-identifier) */

        __C_ENG_ENUM {

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE

            __C_ENG_ENUM_FIELD ( Success,                                   VkResult :: VK_SUCCESS ),
            __C_ENG_ENUM_FIELD ( NotReady,                                  VkResult :: VK_NOT_READY ),
            __C_ENG_ENUM_FIELD ( Timeout,                                   VkResult :: VK_TIMEOUT ),
            __C_ENG_ENUM_FIELD ( EventSet,                                  VkResult :: VK_EVENT_SET ),
            __C_ENG_ENUM_FIELD ( EventReset,                                VkResult :: VK_EVENT_RESET ),
            __C_ENG_ENUM_FIELD ( Incomplete,                                VkResult :: VK_INCOMPLETE ),
            __C_ENG_ENUM_FIELD ( ErrorOutOfHostMemory,                      VkResult :: VK_ERROR_OUT_OF_HOST_MEMORY ),
            __C_ENG_ENUM_FIELD ( ErrorOutOfDeviceMemory,                    VkResult :: VK_ERROR_OUT_OF_DEVICE_MEMORY ),
            __C_ENG_ENUM_FIELD ( ErrorInitializationFailed,                 VkResult :: VK_ERROR_INITIALIZATION_FAILED ),
            __C_ENG_ENUM_FIELD ( ErrorDeviceLost,                           VkResult :: VK_ERROR_DEVICE_LOST ),
            __C_ENG_ENUM_FIELD ( ErrorMemoryMapFailed,                      VkResult :: VK_ERROR_MEMORY_MAP_FAILED ),
            __C_ENG_ENUM_FIELD ( ErrorLayerNotPresent,                      VkResult :: VK_ERROR_LAYER_NOT_PRESENT ),
            __C_ENG_ENUM_FIELD ( ErrorExtensionNotPresent,                  VkResult :: VK_ERROR_LAYER_NOT_PRESENT ),
            __C_ENG_ENUM_FIELD ( ErrorFeatureNotPresent,                    VkResult :: VK_ERROR_FEATURE_NOT_PRESENT ),
            __C_ENG_ENUM_FIELD ( ErrorIncompatibleDriver,                   VkResult :: VK_ERROR_INCOMPATIBLE_DRIVER ),
            __C_ENG_ENUM_FIELD ( ErrorTooManyObjects,                       VkResult :: VK_ERROR_TOO_MANY_OBJECTS ),
            __C_ENG_ENUM_FIELD ( ErrorFormatNotSupported,                   VkResult :: VK_ERROR_FORMAT_NOT_SUPPORTED ),
            __C_ENG_ENUM_FIELD ( ErrorFragmentedPool,                       VkResult :: VK_ERROR_FRAGMENTED_POOL ),
            __C_ENG_ENUM_FIELD ( ErrorUnknown,                              VkResult :: VK_ERROR_UNKNOWN ),

#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

            __C_ENG_ENUM_FIELD ( ErrorOutOfPoolMemory,                      VkResult :: VK_ERROR_OUT_OF_POOL_MEMORY ),
            __C_ENG_ENUM_FIELD ( ErrorInvalidExternalHandle,                VkResult :: VK_ERROR_INVALID_EXTERNAL_HANDLE ),

#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE

            __C_ENG_ENUM_FIELD ( ErrorFragmentation,                        VkResult :: VK_ERROR_FRAGMENTATION ),
            __C_ENG_ENUM_FIELD ( ErrorInvalidOpaqueCaptureAddress,          VkResult :: VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SURFACE_AVAILABLE

            __C_ENG_ENUM_FIELD ( ErrorSurfaceLost,                          VkResult :: VK_ERROR_SURFACE_LOST_KHR ),
            __C_ENG_ENUM_FIELD ( ErrorNativeWindowInUse,                    VkResult :: VK_ERROR_NATIVE_WINDOW_IN_USE_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DISPLAY_SWAP_CHAIN_AVAILABLE

            __C_ENG_ENUM_FIELD ( ErrorIncompatibleDisplay,                  VkResult :: VK_ERROR_INCOMPATIBLE_DISPLAY_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DEFERRED_HOST_OPERATIONS_AVAILABLE

            __C_ENG_ENUM_FIELD ( ThreadIdle,                                VkResult :: VK_THREAD_IDLE_KHR ),
            __C_ENG_ENUM_FIELD ( ThreadDone,                                VkResult :: VK_THREAD_DONE_KHR ),
            __C_ENG_ENUM_FIELD ( OperationDeferred,                         VkResult :: VK_OPERATION_DEFERRED_KHR ),
            __C_ENG_ENUM_FIELD ( OperationNotDeferred,                      VkResult :: VK_OPERATION_NOT_DEFERRED_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_GLSL_SHADER_AVAILABLE

            __C_ENG_ENUM_FIELD ( ErrorInvalidShader,                        VkResult :: VK_ERROR_INVALID_SHADER_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEBUG_REPORT_AVAILABLE

            __C_ENG_ENUM_FIELD ( ErrorValidationFailed,                     VkResult :: VK_ERROR_VALIDATION_FAILED_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_DRM_FORMAT_MODIFIER_AVAILABLE

            __C_ENG_ENUM_FIELD ( ErrorInvalidDRMFormatModifierPlaneLayout,  VkResult :: VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GLOBAL_PRIORITY_AVAILABLE

            __C_ENG_ENUM_FIELD ( ErrorNotPermitted,                         VkResult :: VK_ERROR_NOT_PERMITTED_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FULL_SCREEN_EXCLUSIVE_AVAILABLE

            __C_ENG_ENUM_FIELD ( ErrorFullScreenExclusiveModeLost,          VkResult :: VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_CACHE_CONTROL_AVAILABLE

            __C_ENG_ENUM_FIELD ( PipelineCompileRequired,                   VkResult :: VK_PIPELINE_COMPILE_REQUIRED_EXT ),

#endif

            __C_ENG_ENUM_FIELD ( Unknown,                                   cds :: limits :: S32_MAX )

        };

#pragma pop_macro("__C_ENG_OBJECT_TYPE")
#pragma pop_macro("__C_ENG_OBJECT_NAME")


#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE

        __C_ENG_ALIAS ( Offset2D, VkOffset2D );
        __C_ENG_ALIAS ( Offset3D, VkOffset3D );

        __C_ENG_ALIAS ( Extent2D, VkExtent2D );
        __C_ENG_ALIAS ( Extent3D, VkExtent3D );

        __C_ENG_ALIAS ( Rect, VkRect2D );

#endif


#pragma push_macro("__C_ENG_OBJECT_NAME")
#pragma push_macro("__C_ENG_OBJECT_TYPE")

#undef  __C_ENG_OBJECT_NAME
#undef  __C_ENG_OBJECT_TYPE
#define __C_ENG_OBJECT_NAME StructureType /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_OBJECT_TYPE cds :: sint32 /* NOLINT(bugprone-reserved-identifier) */

        __C_ENG_ENUM {

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE

            __C_ENG_ENUM_FIELD ( ApplicationInfo,                                    VkStructureType :: VK_STRUCTURE_TYPE_APPLICATION_INFO ),
            __C_ENG_ENUM_FIELD ( InstanceCreateInfo,                                 VkStructureType :: VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( DeviceQueueCreateInfo,                              VkStructureType :: VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( DeviceCreateInfo,                                   VkStructureType :: VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO ),

            __C_ENG_ENUM_FIELD ( SubmitInfo,                                         VkStructureType :: VK_STRUCTURE_TYPE_SUBMIT_INFO ),
            __C_ENG_ENUM_FIELD ( MemoryAllocateInfo,                                 VkStructureType :: VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO ),
            __C_ENG_ENUM_FIELD ( MappedMemoryRange,                                  VkStructureType :: VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE ),
            __C_ENG_ENUM_FIELD ( BindSparseInfo,                                     VkStructureType :: VK_STRUCTURE_TYPE_BIND_SPARSE_INFO ),

            __C_ENG_ENUM_FIELD ( FenceCreateInfo,                                    VkStructureType :: VK_STRUCTURE_TYPE_FENCE_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( SemaphoreCreateInfo,                                VkStructureType :: VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( EventCreateInfo,                                    VkStructureType :: VK_STRUCTURE_TYPE_EVENT_CREATE_INFO ),

            __C_ENG_ENUM_FIELD ( QueryPoolCreateInfo,                                VkStructureType :: VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( BufferCreateInfo,                                   VkStructureType :: VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( BufferViewCreateInfo,                               VkStructureType :: VK_STRUCTURE_TYPE_BUFFER_VIEW_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( ImageCreateInfo,                                    VkStructureType :: VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( ImageViewCreateInfo,                                VkStructureType :: VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO ),

            __C_ENG_ENUM_FIELD ( ShaderModuleCreateInfo,                             VkStructureType :: VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO ),

            __C_ENG_ENUM_FIELD ( PipelineCacheCreateInfo,                            VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( PipelineShaderStageCreateInfo,                      VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( PipelineVertexInputStateCreateInfo,                 VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( PipelineInputAssemblyStateCreateInfo,               VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( PipelineTesselationStateCreateInfo,                 VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( PipelineViewportStateCreateInfo,                    VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( PipelineRasterizationStateCreateInfo,               VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( PipelineMultisampleStateCreateInfo,                 VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( PipelineDepthStencilStateCreateInfo,                VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( PipelineColorBlendStateCreateInfo,                  VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( PipelineDynamicStateCreateInfo,                     VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO ),

            __C_ENG_ENUM_FIELD ( GraphicsPipelineCreateInfo,                         VkStructureType :: VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( ComputePipelineCreateInfo,                          VkStructureType :: VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( PipelineLayoutCreateInfo,                           VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO ),

            __C_ENG_ENUM_FIELD ( SamplerCreateInfo,                                  VkStructureType :: VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO ),

            __C_ENG_ENUM_FIELD ( DescriptorSetLayoutCreateInfo,                      VkStructureType :: VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( DescriptorPoolCreateInfo,                           VkStructureType :: VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( DescriptorSetAllocateInfo,                          VkStructureType :: VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO ),
            __C_ENG_ENUM_FIELD ( WriteDescriptorSet,                                 VkStructureType :: VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET ),
            __C_ENG_ENUM_FIELD ( CopyDescriptorSet,                                  VkStructureType :: VK_STRUCTURE_TYPE_COPY_DESCRIPTOR_SET ),

            __C_ENG_ENUM_FIELD ( FramebufferCreateInfo,                              VkStructureType :: VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( RenderPassCreateInfo,                               VkStructureType :: VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO ),

            __C_ENG_ENUM_FIELD ( CommandPoolCreateInfo,                              VkStructureType :: VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( CommandBufferAllocateInfo,                          VkStructureType :: VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO ),
            __C_ENG_ENUM_FIELD ( CommandBufferInheritanceInfo,                       VkStructureType :: VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO ),
            __C_ENG_ENUM_FIELD ( CommandBufferBeginInfo,                             VkStructureType :: VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO ),

            __C_ENG_ENUM_FIELD ( RenderPassBeginInfo,                                VkStructureType :: VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO ),

            __C_ENG_ENUM_FIELD ( BufferMemoryBarrier,                                VkStructureType :: VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER ),
            __C_ENG_ENUM_FIELD ( ImageMemoryBarrier,                                 VkStructureType :: VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER ),
            __C_ENG_ENUM_FIELD ( MemoryBarrier,                                      VkStructureType :: VK_STRUCTURE_TYPE_MEMORY_BARRIER ),

            __C_ENG_ENUM_FIELD ( LoaderInstanceCreateInfo,                           VkStructureType :: VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( LoaderDeviceCreateInfo,                             VkStructureType :: VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO ),

#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceSubgroupProperties,                   VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBGROUP_PROPERTIES ),

            __C_ENG_ENUM_FIELD ( BindBufferMemoryInfo,                               VkStructureType :: VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO ),
            __C_ENG_ENUM_FIELD ( BindImageMemoryInfo,                                VkStructureType :: VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_INFO ),

            __C_ENG_ENUM_FIELD ( PhysicalDevice16BitStorageFeatures,                 VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_16BIT_STORAGE_FEATURES ),

            __C_ENG_ENUM_FIELD ( MemoryDedicatedRequirements,                        VkStructureType :: VK_STRUCTURE_TYPE_MEMORY_DEDICATED_REQUIREMENTS ),
            __C_ENG_ENUM_FIELD ( MemoryDedicatedAllocateInfo,                        VkStructureType :: VK_STRUCTURE_TYPE_MEMORY_DEDICATED_ALLOCATE_INFO ),
            __C_ENG_ENUM_FIELD ( MemoryAllocateFlagsInfo,                            VkStructureType :: VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO ),

            __C_ENG_ENUM_FIELD ( DeviceGroupRenderPassBeginInfo,                     VkStructureType :: VK_STRUCTURE_TYPE_DEVICE_GROUP_RENDER_PASS_BEGIN_INFO ),
            __C_ENG_ENUM_FIELD ( DeviceGroupCommandBufferBeginInfo,                  VkStructureType :: VK_STRUCTURE_TYPE_DEVICE_GROUP_COMMAND_BUFFER_BEGIN_INFO ),
            __C_ENG_ENUM_FIELD ( DeviceGroupSubmitInfo,                              VkStructureType :: VK_STRUCTURE_TYPE_DEVICE_GROUP_SUBMIT_INFO ),
            __C_ENG_ENUM_FIELD ( DeviceGroupBindSparseInfo,                          VkStructureType :: VK_STRUCTURE_TYPE_DEVICE_GROUP_BIND_SPARSE_INFO ),

            __C_ENG_ENUM_FIELD ( BindBufferMemoryDeviceGroupInfo,                    VkStructureType :: VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_DEVICE_GROUP_INFO ),
            __C_ENG_ENUM_FIELD ( BindImageMemoryDeviceGroupInfo,                     VkStructureType :: VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_DEVICE_GROUP_INFO ),

            __C_ENG_ENUM_FIELD ( PhysicalDeviceGroupProperties,                      VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_GROUP_PROPERTIES ),
            __C_ENG_ENUM_FIELD ( DeviceGroupDeviceCreateInfo,                        VkStructureType :: VK_STRUCTURE_TYPE_DEVICE_GROUP_DEVICE_CREATE_INFO ),

            __C_ENG_ENUM_FIELD ( BufferMemoryRequirementsInfo,                       VkStructureType :: VK_STRUCTURE_TYPE_BUFFER_MEMORY_REQUIREMENTS_INFO_2 ),
            __C_ENG_ENUM_FIELD ( ImageMemoryRequirementsInfo,                        VkStructureType :: VK_STRUCTURE_TYPE_IMAGE_MEMORY_REQUIREMENTS_INFO_2 ),
            __C_ENG_ENUM_FIELD ( ImageSparseMemoryRequirementsInfo,                  VkStructureType :: VK_STRUCTURE_TYPE_IMAGE_SPARSE_MEMORY_REQUIREMENTS_INFO_2 ),
            __C_ENG_ENUM_FIELD ( MemoryRequirements,                                 VkStructureType :: VK_STRUCTURE_TYPE_MEMORY_REQUIREMENTS_2 ),
            __C_ENG_ENUM_FIELD ( SparseImageMemoryRequirements,                      VkStructureType :: VK_STRUCTURE_TYPE_SPARSE_IMAGE_MEMORY_REQUIREMENTS_2 ),

            __C_ENG_ENUM_FIELD ( PhysicalDeviceFeatures,                             VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2 ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceProperties,                           VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2 ),

            __C_ENG_ENUM_FIELD ( FormatProperties,                                   VkStructureType :: VK_STRUCTURE_TYPE_FORMAT_PROPERTIES_2 ),
            __C_ENG_ENUM_FIELD ( ImageFormatProperties,                              VkStructureType :: VK_STRUCTURE_TYPE_IMAGE_FORMAT_PROPERTIES_2 ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceImageFormatInfo,                      VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_FORMAT_INFO_2 ),

            __C_ENG_ENUM_FIELD ( QueueFamilyProperties,                              VkStructureType :: VK_STRUCTURE_TYPE_QUEUE_FAMILY_PROPERTIES_2 ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceMemoryProperties,                     VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_PROPERTIES_2 ),
            __C_ENG_ENUM_FIELD ( SparseImageFormatProperties,                        VkStructureType :: VK_STRUCTURE_TYPE_SPARSE_IMAGE_FORMAT_PROPERTIES_2 ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceSparseImageFormatInfo,                VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SPARSE_IMAGE_FORMAT_INFO_2 ),
            __C_ENG_ENUM_FIELD ( PhysicalDevicePointClippingProperties,              VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_POINT_CLIPPING_PROPERTIES ),

            __C_ENG_ENUM_FIELD ( RenderPassInputAttachmentAspectCreateInfo,          VkStructureType :: VK_STRUCTURE_TYPE_RENDER_PASS_INPUT_ATTACHMENT_ASPECT_CREATE_INFO ),

            __C_ENG_ENUM_FIELD ( ImageViewUsageCreateInfo,                           VkStructureType :: VK_STRUCTURE_TYPE_IMAGE_VIEW_USAGE_CREATE_INFO ),

            __C_ENG_ENUM_FIELD ( PipelineTesselationDomainOriginStateCreateInfo,     VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_DOMAIN_ORIGIN_STATE_CREATE_INFO ),

            __C_ENG_ENUM_FIELD ( RenderPassMultiviewCreateInfo,                      VkStructureType :: VK_STRUCTURE_TYPE_RENDER_PASS_MULTIVIEW_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceMultiviewFeatures,                    VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTIVIEW_FEATURES ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceMultiviewProperties,                  VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTIVIEW_PROPERTIES ),

            __C_ENG_ENUM_FIELD ( PhysicalDeviceVariablePointersFeatures,             VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VARIABLE_POINTERS_FEATURES ),

            __C_ENG_ENUM_FIELD ( ProtectedSubmitInfo,                                VkStructureType :: VK_STRUCTURE_TYPE_PROTECTED_SUBMIT_INFO ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceProtectedMemoryFeatures,              VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROTECTED_MEMORY_FEATURES ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceProtectedMemoryProperties,            VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROTECTED_MEMORY_PROPERTIES ),

            __C_ENG_ENUM_FIELD ( DeviceQueueInfo,                                    VkStructureType :: VK_STRUCTURE_TYPE_DEVICE_QUEUE_INFO_2 ),

            __C_ENG_ENUM_FIELD ( SamplerYCBCRConversionCreateInfo,                   VkStructureType :: VK_STRUCTURE_TYPE_SAMPLER_YCBCR_CONVERSION_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( SamplerYCBCRConversionInfo,                         VkStructureType :: VK_STRUCTURE_TYPE_SAMPLER_YCBCR_CONVERSION_INFO ),

            __C_ENG_ENUM_FIELD ( BindImagePlaneMemoryInfo,                           VkStructureType :: VK_STRUCTURE_TYPE_BIND_IMAGE_PLANE_MEMORY_INFO ),
            __C_ENG_ENUM_FIELD ( ImagePlaneMemoryRequirementsInfo,                   VkStructureType :: VK_STRUCTURE_TYPE_IMAGE_PLANE_MEMORY_REQUIREMENTS_INFO ),

            __C_ENG_ENUM_FIELD ( PhysicalDeviceSamplerYCBCRConversionFeatures,       VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SAMPLER_YCBCR_CONVERSION_FEATURES ),
            __C_ENG_ENUM_FIELD ( SamplerYCBCRConversionImageFormatProperties,        VkStructureType :: VK_STRUCTURE_TYPE_SAMPLER_YCBCR_CONVERSION_IMAGE_FORMAT_PROPERTIES ),

            __C_ENG_ENUM_FIELD ( DescriptorUpdateTemplateCreateInfo,                 VkStructureType :: VK_STRUCTURE_TYPE_DESCRIPTOR_UPDATE_TEMPLATE_CREATE_INFO ),

            __C_ENG_ENUM_FIELD ( PhysicalDeviceExternalImageFormatInfo,              VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_IMAGE_FORMAT_INFO ),
            __C_ENG_ENUM_FIELD ( ExternalImageFormatProperties,                      VkStructureType :: VK_STRUCTURE_TYPE_EXTERNAL_IMAGE_FORMAT_PROPERTIES ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceExternalBufferInfo,                   VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_BUFFER_INFO ),
            __C_ENG_ENUM_FIELD ( ExternalBufferProperties,                           VkStructureType :: VK_STRUCTURE_TYPE_EXTERNAL_BUFFER_PROPERTIES ),

            __C_ENG_ENUM_FIELD ( PhysicalDeviceIDProperties,                         VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ID_PROPERTIES ),

            __C_ENG_ENUM_FIELD ( ExternalMemoryBufferCreateInfo,                     VkStructureType :: VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_BUFFER_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( ExternalMemoryImageCreateInfo,                      VkStructureType :: VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMAGE_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( ExportMemoryAllocateInfo,                           VkStructureType :: VK_STRUCTURE_TYPE_EXPORT_MEMORY_ALLOCATE_INFO ),

            __C_ENG_ENUM_FIELD ( PhysicalDeviceExternalFenceInfo,                    VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_FENCE_INFO ),
            __C_ENG_ENUM_FIELD ( ExternalFenceProperties,                            VkStructureType :: VK_STRUCTURE_TYPE_EXTERNAL_FENCE_PROPERTIES ),
            __C_ENG_ENUM_FIELD ( ExportFenceCreateInfo,                              VkStructureType :: VK_STRUCTURE_TYPE_EXPORT_FENCE_CREATE_INFO ),

            __C_ENG_ENUM_FIELD ( ExportSemaphoreCreateInfo,                          VkStructureType :: VK_STRUCTURE_TYPE_EXPORT_SEMAPHORE_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceExternalSempahoreInfo,                VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_SEMAPHORE_INFO ),
            __C_ENG_ENUM_FIELD ( ExternalSemaphoreProperties,                        VkStructureType :: VK_STRUCTURE_TYPE_EXTERNAL_SEMAPHORE_PROPERTIES ),

            __C_ENG_ENUM_FIELD ( PhysicalDeviceMaintenanceProperties,                VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_3_PROPERTIES ),

            __C_ENG_ENUM_FIELD ( DescriptorSetLayoutSupport,                         VkStructureType :: VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_SUPPORT ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceShaderDrawParametersFeatures,         VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_DRAW_PARAMETERS_FEATURES ),

#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceVulkan_1_1_Features,                  VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceVulkan_1_1_Properties,                VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_PROPERTIES ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceVulkan_1_2_Features,                  VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceVulkan_1_2_Properties,                VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_PROPERTIES ),

            __C_ENG_ENUM_FIELD ( ImageFormatListCreateInfo,                          VkStructureType :: VK_STRUCTURE_TYPE_IMAGE_FORMAT_LIST_CREATE_INFO ),

            __C_ENG_ENUM_FIELD ( AttachmentDescription,                              VkStructureType :: VK_STRUCTURE_TYPE_ATTACHMENT_DESCRIPTION_2 ),
            __C_ENG_ENUM_FIELD ( AttachmentReference,                                VkStructureType :: VK_STRUCTURE_TYPE_ATTACHMENT_REFERENCE_2 ),
            __C_ENG_ENUM_FIELD ( SubpassDescription,                                 VkStructureType :: VK_STRUCTURE_TYPE_SUBPASS_DESCRIPTION_2 ),
            __C_ENG_ENUM_FIELD ( SubpassDependency,                                  VkStructureType :: VK_STRUCTURE_TYPE_SUBPASS_DEPENDENCY_2 ),

            __C_ENG_ENUM_FIELD ( RenderPassCreateInfo2,                              VkStructureType :: VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO_2 ),

            __C_ENG_ENUM_FIELD ( SubpassBeginInfo,                                   VkStructureType :: VK_STRUCTURE_TYPE_SUBPASS_BEGIN_INFO ),
            __C_ENG_ENUM_FIELD ( SubpassEndInfo,                                     VkStructureType :: VK_STRUCTURE_TYPE_SUBPASS_END_INFO ),

            __C_ENG_ENUM_FIELD ( PhysicalDevice8BitStorageFeatures,                  VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_8BIT_STORAGE_FEATURES ),

            __C_ENG_ENUM_FIELD ( PhysicalDeviceDriverProperties,                     VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DRIVER_PROPERTIES ),

            __C_ENG_ENUM_FIELD ( PhysicalDeviceShaderAtomicInt64Features,            VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ATOMIC_INT64_FEATURES ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceShaderFloat16Int8Features,            VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_FLOAT16_INT8_FEATURES ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceFloatControlsProperties,              VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FLOAT_CONTROLS_PROPERTIES ),

            __C_ENG_ENUM_FIELD ( DescriptorSetLayoutBindingFlagsCreateInfo,          VkStructureType :: VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO ),

            __C_ENG_ENUM_FIELD ( PhysicalDeviceDescriptorIndexingFeatures,           VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_INDEXING_FEATURES ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceDescriptorIndexingProperties,         VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_INDEXING_PROPERTIES ),

            __C_ENG_ENUM_FIELD ( DescriptorSetVariableDescriptorCountAllocateInfo,   VkStructureType :: VK_STRUCTURE_TYPE_DESCRIPTOR_SET_VARIABLE_DESCRIPTOR_COUNT_ALLOCATE_INFO ),
            __C_ENG_ENUM_FIELD ( DescriptorSetVariableDescriptorCountLayoutSupport,  VkStructureType :: VK_STRUCTURE_TYPE_DESCRIPTOR_SET_VARIABLE_DESCRIPTOR_COUNT_LAYOUT_SUPPORT ),

            __C_ENG_ENUM_FIELD ( PhysicalDeviceDepthStencilResolveProperties,        VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEPTH_STENCIL_RESOLVE_PROPERTIES ),
            __C_ENG_ENUM_FIELD ( SubpassDescriptionDepthStencilResolve,              VkStructureType :: VK_STRUCTURE_TYPE_SUBPASS_DESCRIPTION_DEPTH_STENCIL_RESOLVE ),

            __C_ENG_ENUM_FIELD ( PhysicalDeviceScalarBlockLayoutFeatures,            VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SCALAR_BLOCK_LAYOUT_FEATURES ),

            __C_ENG_ENUM_FIELD ( ImageStencilUsageCreateInfo,                        VkStructureType :: VK_STRUCTURE_TYPE_IMAGE_STENCIL_USAGE_CREATE_INFO ),

            __C_ENG_ENUM_FIELD ( PhysicalDeviceSamplerFilterMinMaxProperties,        VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SAMPLER_FILTER_MINMAX_PROPERTIES ),

            __C_ENG_ENUM_FIELD ( SamplerReductionModeCreateInfo,                     VkStructureType :: VK_STRUCTURE_TYPE_SAMPLER_REDUCTION_MODE_CREATE_INFO ),

            __C_ENG_ENUM_FIELD ( PhysicalDeviceVulkanMemoryModelFeatures,            VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_MEMORY_MODEL_FEATURES ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceImagelessFramebufferFeatures,         VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGELESS_FRAMEBUFFER_FEATURES ),

            __C_ENG_ENUM_FIELD ( FramebufferAttachmentsCreateInfo,                   VkStructureType :: VK_STRUCTURE_TYPE_FRAMEBUFFER_ATTACHMENTS_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( FramebufferAttachmentImageInfo,                     VkStructureType :: VK_STRUCTURE_TYPE_FRAMEBUFFER_ATTACHMENT_IMAGE_INFO ),
            __C_ENG_ENUM_FIELD ( RenderPassAttachmentBeginInfo,                      VkStructureType :: VK_STRUCTURE_TYPE_RENDER_PASS_ATTACHMENT_BEGIN_INFO ),

            __C_ENG_ENUM_FIELD ( PhysicalDeviceUniformBufferStandardLayoutFeatures,  VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_UNIFORM_BUFFER_STANDARD_LAYOUT_FEATURES ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceShaderSubgroupExtendedTypesFeatures,  VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_SUBGROUP_EXTENDED_TYPES_FEATURES ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceSeparateDepthStencilLayoutsFeatures,  VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SEPARATE_DEPTH_STENCIL_LAYOUTS_FEATURES ),

            __C_ENG_ENUM_FIELD ( AttachmentReferenceStencilLayout,                   VkStructureType :: VK_STRUCTURE_TYPE_ATTACHMENT_REFERENCE_STENCIL_LAYOUT ),
            __C_ENG_ENUM_FIELD ( AttachmentDescriptionStencilLayout,                 VkStructureType :: VK_STRUCTURE_TYPE_ATTACHMENT_DESCRIPTION_STENCIL_LAYOUT ),

            __C_ENG_ENUM_FIELD ( PhysicalDeviceHostQueryResetFeatures,               VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_HOST_QUERY_RESET_FEATURES ),

            __C_ENG_ENUM_FIELD ( PhysicalDeviceTimelineSemaphoreFeatures,            VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TIMELINE_SEMAPHORE_FEATURES ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceTimelineSemaphoreProperties,          VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TIMELINE_SEMAPHORE_PROPERTIES ),

            __C_ENG_ENUM_FIELD ( SemaphoreTypeCreateInfo,                            VkStructureType :: VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( TimelineSemaphoreSubmitInfo,                        VkStructureType :: VK_STRUCTURE_TYPE_TIMELINE_SEMAPHORE_SUBMIT_INFO ),
            __C_ENG_ENUM_FIELD ( SemaphoreWaitInfo,                                  VkStructureType :: VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO ),
            __C_ENG_ENUM_FIELD ( SemaphoreSignalInfo,                                VkStructureType :: VK_STRUCTURE_TYPE_SEMAPHORE_SIGNAL_INFO ),

            __C_ENG_ENUM_FIELD ( PhysicalDeviceBufferDeviceAddressFeatures,          VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BUFFER_DEVICE_ADDRESS_FEATURES ),
            __C_ENG_ENUM_FIELD ( BufferDeviceAddressInfo,                            VkStructureType :: VK_STRUCTURE_TYPE_BUFFER_DEVICE_ADDRESS_INFO ),
            __C_ENG_ENUM_FIELD ( BufferOpaqueCaptureAddressCreateInfo,               VkStructureType :: VK_STRUCTURE_TYPE_BUFFER_OPAQUE_CAPTURE_ADDRESS_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( MemoryOpaqueCaptureAddressAllocateInfo,             VkStructureType :: VK_STRUCTURE_TYPE_MEMORY_OPAQUE_CAPTURE_ADDRESS_ALLOCATE_INFO ),
            __C_ENG_ENUM_FIELD ( DeviceMemoryOpaqueCaptureAddressInfo,               VkStructureType :: VK_STRUCTURE_TYPE_DEVICE_MEMORY_OPAQUE_CAPTURE_ADDRESS_INFO ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SWAP_CHAIN_AVAILABLE

            __C_ENG_ENUM_FIELD ( SwapchainCreateInfo,                                VkStructureType :: VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR ),
            __C_ENG_ENUM_FIELD ( PresentInfo,                                        VkStructureType :: VK_STRUCTURE_TYPE_PRESENT_INFO_KHR ),

#endif

            __C_ENG_ENUM_FIELD ( Unknown,                                            cds :: limits :: S32_MAX )

        };

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( Result ) ) noexcept -> cds :: StringLiteral;

    }
}

#endif //__C_ENG_VULKANCORE_HPP
