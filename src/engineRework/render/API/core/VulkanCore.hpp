//
// Created by loghin on 26.12.2021.
//

#ifndef __C_ENG_VULKANCORE_HPP
#define __C_ENG_VULKANCORE_HPP

#include <Preprocess.hpp>
#include <CDS/Types>
#include <CDS/Limits>

#include <VulkanAPIDetails.hpp>
#include <VulkanAPIExtensionDetails.hpp>
#include <VulkanAPIKhronosExtensionDetails.hpp>
#include <VulkanAPIAMDExtensionDetails.hpp>
#include <VulkanAPINVidiaExtensionDetails.hpp>
#include <VulkanAPIGoogleExtensionDetails.hpp>
#include <VulkanAPIAppleExtensionDetails.hpp>
#include <VulkanAPIIntelExtensionDetails.hpp>
#include <VulkanAPIQualcommExtensionDetails.hpp>
#include <VulkanAPIARMExtensionDetails.hpp>
#include <VulkanAPIValveExtensionDetails.hpp>
#include <VulkanAPIHuaweiExtensionDetails.hpp>
#include <VulkanAPIBlackberryExtensionDetails.hpp>

namespace cds {
    class String;
}

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

            __C_ENG_ENUM_FIELD ( ApplicationInfo,                                                       VkStructureType :: VK_STRUCTURE_TYPE_APPLICATION_INFO ),
            __C_ENG_ENUM_FIELD ( InstanceCreateInfo,                                                    VkStructureType :: VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( DeviceQueueCreateInfo,                                                 VkStructureType :: VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( DeviceCreateInfo,                                                      VkStructureType :: VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO ),

            __C_ENG_ENUM_FIELD ( SubmitInfo,                                                            VkStructureType :: VK_STRUCTURE_TYPE_SUBMIT_INFO ),
            __C_ENG_ENUM_FIELD ( MemoryAllocateInfo,                                                    VkStructureType :: VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO ),
            __C_ENG_ENUM_FIELD ( MappedMemoryRange,                                                     VkStructureType :: VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE ),
            __C_ENG_ENUM_FIELD ( BindSparseInfo,                                                        VkStructureType :: VK_STRUCTURE_TYPE_BIND_SPARSE_INFO ),

            __C_ENG_ENUM_FIELD ( FenceCreateInfo,                                                       VkStructureType :: VK_STRUCTURE_TYPE_FENCE_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( SemaphoreCreateInfo,                                                   VkStructureType :: VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( EventCreateInfo,                                                       VkStructureType :: VK_STRUCTURE_TYPE_EVENT_CREATE_INFO ),

            __C_ENG_ENUM_FIELD ( QueryPoolCreateInfo,                                                   VkStructureType :: VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( BufferCreateInfo,                                                      VkStructureType :: VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( BufferViewCreateInfo,                                                  VkStructureType :: VK_STRUCTURE_TYPE_BUFFER_VIEW_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( ImageCreateInfo,                                                       VkStructureType :: VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( ImageViewCreateInfo,                                                   VkStructureType :: VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO ),

            __C_ENG_ENUM_FIELD ( ShaderModuleCreateInfo,                                                VkStructureType :: VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO ),

            __C_ENG_ENUM_FIELD ( PipelineCacheCreateInfo,                                               VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( PipelineShaderStageCreateInfo,                                         VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( PipelineVertexInputStateCreateInfo,                                    VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( PipelineInputAssemblyStateCreateInfo,                                  VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( PipelineTesselationStateCreateInfo,                                    VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( PipelineViewportStateCreateInfo,                                       VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( PipelineRasterizationStateCreateInfo,                                  VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( PipelineMultisampleStateCreateInfo,                                    VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( PipelineDepthStencilStateCreateInfo,                                   VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( PipelineColorBlendStateCreateInfo,                                     VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( PipelineDynamicStateCreateInfo,                                        VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO ),

            __C_ENG_ENUM_FIELD ( GraphicsPipelineCreateInfo,                                            VkStructureType :: VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( ComputePipelineCreateInfo,                                             VkStructureType :: VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( PipelineLayoutCreateInfo,                                              VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO ),

            __C_ENG_ENUM_FIELD ( SamplerCreateInfo,                                                     VkStructureType :: VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO ),

            __C_ENG_ENUM_FIELD ( DescriptorSetLayoutCreateInfo,                                         VkStructureType :: VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( DescriptorPoolCreateInfo,                                              VkStructureType :: VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( DescriptorSetAllocateInfo,                                             VkStructureType :: VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO ),
            __C_ENG_ENUM_FIELD ( WriteDescriptorSet,                                                    VkStructureType :: VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET ),
            __C_ENG_ENUM_FIELD ( CopyDescriptorSet,                                                     VkStructureType :: VK_STRUCTURE_TYPE_COPY_DESCRIPTOR_SET ),

            __C_ENG_ENUM_FIELD ( FramebufferCreateInfo,                                                 VkStructureType :: VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( RenderPassCreateInfo,                                                  VkStructureType :: VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO ),

            __C_ENG_ENUM_FIELD ( CommandPoolCreateInfo,                                                 VkStructureType :: VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( CommandBufferAllocateInfo,                                             VkStructureType :: VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO ),
            __C_ENG_ENUM_FIELD ( CommandBufferInheritanceInfo,                                          VkStructureType :: VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO ),
            __C_ENG_ENUM_FIELD ( CommandBufferBeginInfo,                                                VkStructureType :: VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO ),

            __C_ENG_ENUM_FIELD ( RenderPassBeginInfo,                                                   VkStructureType :: VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO ),

            __C_ENG_ENUM_FIELD ( BufferMemoryBarrier,                                                   VkStructureType :: VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER ),
            __C_ENG_ENUM_FIELD ( ImageMemoryBarrier,                                                    VkStructureType :: VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER ),
            __C_ENG_ENUM_FIELD ( MemoryBarrier,                                                         VkStructureType :: VK_STRUCTURE_TYPE_MEMORY_BARRIER ),

            __C_ENG_ENUM_FIELD ( LoaderInstanceCreateInfo,                                              VkStructureType :: VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( LoaderDeviceCreateInfo,                                                VkStructureType :: VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO ),

#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceSubgroupProperties,                                      VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBGROUP_PROPERTIES ),

            __C_ENG_ENUM_FIELD ( BindBufferMemoryInfo,                                                  VkStructureType :: VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO ),
            __C_ENG_ENUM_FIELD ( BindImageMemoryInfo,                                                   VkStructureType :: VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_INFO ),

            __C_ENG_ENUM_FIELD ( PhysicalDevice16BitStorageFeatures,                                    VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_16BIT_STORAGE_FEATURES ),

            __C_ENG_ENUM_FIELD ( MemoryDedicatedRequirements,                                           VkStructureType :: VK_STRUCTURE_TYPE_MEMORY_DEDICATED_REQUIREMENTS ),
            __C_ENG_ENUM_FIELD ( MemoryDedicatedAllocateInfo,                                           VkStructureType :: VK_STRUCTURE_TYPE_MEMORY_DEDICATED_ALLOCATE_INFO ),
            __C_ENG_ENUM_FIELD ( MemoryAllocateFlagsInfo,                                               VkStructureType :: VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO ),

            __C_ENG_ENUM_FIELD ( DeviceGroupRenderPassBeginInfo,                                        VkStructureType :: VK_STRUCTURE_TYPE_DEVICE_GROUP_RENDER_PASS_BEGIN_INFO ),
            __C_ENG_ENUM_FIELD ( DeviceGroupCommandBufferBeginInfo,                                     VkStructureType :: VK_STRUCTURE_TYPE_DEVICE_GROUP_COMMAND_BUFFER_BEGIN_INFO ),
            __C_ENG_ENUM_FIELD ( DeviceGroupSubmitInfo,                                                 VkStructureType :: VK_STRUCTURE_TYPE_DEVICE_GROUP_SUBMIT_INFO ),
            __C_ENG_ENUM_FIELD ( DeviceGroupBindSparseInfo,                                             VkStructureType :: VK_STRUCTURE_TYPE_DEVICE_GROUP_BIND_SPARSE_INFO ),

            __C_ENG_ENUM_FIELD ( BindBufferMemoryDeviceGroupInfo,                                       VkStructureType :: VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_DEVICE_GROUP_INFO ),
            __C_ENG_ENUM_FIELD ( BindImageMemoryDeviceGroupInfo,                                        VkStructureType :: VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_DEVICE_GROUP_INFO ),

            __C_ENG_ENUM_FIELD ( PhysicalDeviceGroupProperties,                                         VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_GROUP_PROPERTIES ),
            __C_ENG_ENUM_FIELD ( DeviceGroupDeviceCreateInfo,                                           VkStructureType :: VK_STRUCTURE_TYPE_DEVICE_GROUP_DEVICE_CREATE_INFO ),

            __C_ENG_ENUM_FIELD ( BufferMemoryRequirementsInfo,                                          VkStructureType :: VK_STRUCTURE_TYPE_BUFFER_MEMORY_REQUIREMENTS_INFO_2 ),
            __C_ENG_ENUM_FIELD ( ImageMemoryRequirementsInfo,                                           VkStructureType :: VK_STRUCTURE_TYPE_IMAGE_MEMORY_REQUIREMENTS_INFO_2 ),
            __C_ENG_ENUM_FIELD ( ImageSparseMemoryRequirementsInfo,                                     VkStructureType :: VK_STRUCTURE_TYPE_IMAGE_SPARSE_MEMORY_REQUIREMENTS_INFO_2 ),
            __C_ENG_ENUM_FIELD ( MemoryRequirements,                                                    VkStructureType :: VK_STRUCTURE_TYPE_MEMORY_REQUIREMENTS_2 ),
            __C_ENG_ENUM_FIELD ( SparseImageMemoryRequirements,                                         VkStructureType :: VK_STRUCTURE_TYPE_SPARSE_IMAGE_MEMORY_REQUIREMENTS_2 ),

            __C_ENG_ENUM_FIELD ( PhysicalDeviceFeatures,                                                VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2 ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceProperties,                                              VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2 ),

            __C_ENG_ENUM_FIELD ( FormatProperties,                                                      VkStructureType :: VK_STRUCTURE_TYPE_FORMAT_PROPERTIES_2 ),
            __C_ENG_ENUM_FIELD ( ImageFormatProperties,                                                 VkStructureType :: VK_STRUCTURE_TYPE_IMAGE_FORMAT_PROPERTIES_2 ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceImageFormatInfo,                                         VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_FORMAT_INFO_2 ),

            __C_ENG_ENUM_FIELD ( QueueFamilyProperties,                                                 VkStructureType :: VK_STRUCTURE_TYPE_QUEUE_FAMILY_PROPERTIES_2 ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceMemoryProperties,                                        VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_PROPERTIES_2 ),
            __C_ENG_ENUM_FIELD ( SparseImageFormatProperties,                                           VkStructureType :: VK_STRUCTURE_TYPE_SPARSE_IMAGE_FORMAT_PROPERTIES_2 ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceSparseImageFormatInfo,                                   VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SPARSE_IMAGE_FORMAT_INFO_2 ),
            __C_ENG_ENUM_FIELD ( PhysicalDevicePointClippingProperties,                                 VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_POINT_CLIPPING_PROPERTIES ),

            __C_ENG_ENUM_FIELD ( RenderPassInputAttachmentAspectCreateInfo,                             VkStructureType :: VK_STRUCTURE_TYPE_RENDER_PASS_INPUT_ATTACHMENT_ASPECT_CREATE_INFO ),

            __C_ENG_ENUM_FIELD ( ImageViewUsageCreateInfo,                                              VkStructureType :: VK_STRUCTURE_TYPE_IMAGE_VIEW_USAGE_CREATE_INFO ),

            __C_ENG_ENUM_FIELD ( PipelineTesselationDomainOriginStateCreateInfo,                        VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_DOMAIN_ORIGIN_STATE_CREATE_INFO ),

            __C_ENG_ENUM_FIELD ( RenderPassMultiviewCreateInfo,                                         VkStructureType :: VK_STRUCTURE_TYPE_RENDER_PASS_MULTIVIEW_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceMultiviewFeatures,                                       VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTIVIEW_FEATURES ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceMultiviewProperties,                                     VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTIVIEW_PROPERTIES ),

            __C_ENG_ENUM_FIELD ( PhysicalDeviceVariablePointersFeatures,                                VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VARIABLE_POINTERS_FEATURES ),

            __C_ENG_ENUM_FIELD ( ProtectedSubmitInfo,                                                   VkStructureType :: VK_STRUCTURE_TYPE_PROTECTED_SUBMIT_INFO ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceProtectedMemoryFeatures,                                 VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROTECTED_MEMORY_FEATURES ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceProtectedMemoryProperties,                               VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROTECTED_MEMORY_PROPERTIES ),

            __C_ENG_ENUM_FIELD ( DeviceQueueInfo,                                                       VkStructureType :: VK_STRUCTURE_TYPE_DEVICE_QUEUE_INFO_2 ),

            __C_ENG_ENUM_FIELD ( SamplerYCBCRConversionCreateInfo,                                      VkStructureType :: VK_STRUCTURE_TYPE_SAMPLER_YCBCR_CONVERSION_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( SamplerYCBCRConversionInfo,                                            VkStructureType :: VK_STRUCTURE_TYPE_SAMPLER_YCBCR_CONVERSION_INFO ),

            __C_ENG_ENUM_FIELD ( BindImagePlaneMemoryInfo,                                              VkStructureType :: VK_STRUCTURE_TYPE_BIND_IMAGE_PLANE_MEMORY_INFO ),
            __C_ENG_ENUM_FIELD ( ImagePlaneMemoryRequirementsInfo,                                      VkStructureType :: VK_STRUCTURE_TYPE_IMAGE_PLANE_MEMORY_REQUIREMENTS_INFO ),

            __C_ENG_ENUM_FIELD ( PhysicalDeviceSamplerYCBCRConversionFeatures,                          VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SAMPLER_YCBCR_CONVERSION_FEATURES ),
            __C_ENG_ENUM_FIELD ( SamplerYCBCRConversionImageFormatProperties,                           VkStructureType :: VK_STRUCTURE_TYPE_SAMPLER_YCBCR_CONVERSION_IMAGE_FORMAT_PROPERTIES ),

            __C_ENG_ENUM_FIELD ( DescriptorUpdateTemplateCreateInfo,                                    VkStructureType :: VK_STRUCTURE_TYPE_DESCRIPTOR_UPDATE_TEMPLATE_CREATE_INFO ),

            __C_ENG_ENUM_FIELD ( PhysicalDeviceExternalImageFormatInfo,                                 VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_IMAGE_FORMAT_INFO ),
            __C_ENG_ENUM_FIELD ( ExternalImageFormatProperties,                                         VkStructureType :: VK_STRUCTURE_TYPE_EXTERNAL_IMAGE_FORMAT_PROPERTIES ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceExternalBufferInfo,                                      VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_BUFFER_INFO ),
            __C_ENG_ENUM_FIELD ( ExternalBufferProperties,                                              VkStructureType :: VK_STRUCTURE_TYPE_EXTERNAL_BUFFER_PROPERTIES ),

            __C_ENG_ENUM_FIELD ( PhysicalDeviceIDProperties,                                            VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ID_PROPERTIES ),

            __C_ENG_ENUM_FIELD ( ExternalMemoryBufferCreateInfo,                                        VkStructureType :: VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_BUFFER_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( ExternalMemoryImageCreateInfo,                                         VkStructureType :: VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMAGE_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( ExportMemoryAllocateInfo,                                              VkStructureType :: VK_STRUCTURE_TYPE_EXPORT_MEMORY_ALLOCATE_INFO ),

            __C_ENG_ENUM_FIELD ( PhysicalDeviceExternalFenceInfo,                                       VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_FENCE_INFO ),
            __C_ENG_ENUM_FIELD ( ExternalFenceProperties,                                               VkStructureType :: VK_STRUCTURE_TYPE_EXTERNAL_FENCE_PROPERTIES ),
            __C_ENG_ENUM_FIELD ( ExportFenceCreateInfo,                                                 VkStructureType :: VK_STRUCTURE_TYPE_EXPORT_FENCE_CREATE_INFO ),

            __C_ENG_ENUM_FIELD ( ExportSemaphoreCreateInfo,                                             VkStructureType :: VK_STRUCTURE_TYPE_EXPORT_SEMAPHORE_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceExternalSempahoreInfo,                                   VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_SEMAPHORE_INFO ),
            __C_ENG_ENUM_FIELD ( ExternalSemaphoreProperties,                                           VkStructureType :: VK_STRUCTURE_TYPE_EXTERNAL_SEMAPHORE_PROPERTIES ),

            __C_ENG_ENUM_FIELD ( PhysicalDeviceMaintenanceProperties,                                   VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_3_PROPERTIES ),

            __C_ENG_ENUM_FIELD ( DescriptorSetLayoutSupport,                                            VkStructureType :: VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_SUPPORT ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceShaderDrawParametersFeatures,                            VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_DRAW_PARAMETERS_FEATURES ),

#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceVulkan_1_1_Features,                                     VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceVulkan_1_1_Properties,                                   VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_PROPERTIES ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceVulkan_1_2_Features,                                     VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceVulkan_1_2_Properties,                                   VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_PROPERTIES ),

            __C_ENG_ENUM_FIELD ( ImageFormatListCreateInfo,                                             VkStructureType :: VK_STRUCTURE_TYPE_IMAGE_FORMAT_LIST_CREATE_INFO ),

            __C_ENG_ENUM_FIELD ( AttachmentDescription,                                                 VkStructureType :: VK_STRUCTURE_TYPE_ATTACHMENT_DESCRIPTION_2 ),
            __C_ENG_ENUM_FIELD ( AttachmentReference,                                                   VkStructureType :: VK_STRUCTURE_TYPE_ATTACHMENT_REFERENCE_2 ),
            __C_ENG_ENUM_FIELD ( SubpassDescription,                                                    VkStructureType :: VK_STRUCTURE_TYPE_SUBPASS_DESCRIPTION_2 ),
            __C_ENG_ENUM_FIELD ( SubpassDependency,                                                     VkStructureType :: VK_STRUCTURE_TYPE_SUBPASS_DEPENDENCY_2 ),

            __C_ENG_ENUM_FIELD ( RenderPassCreateInfo2,                                                 VkStructureType :: VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO_2 ),

            __C_ENG_ENUM_FIELD ( SubpassBeginInfo,                                                      VkStructureType :: VK_STRUCTURE_TYPE_SUBPASS_BEGIN_INFO ),
            __C_ENG_ENUM_FIELD ( SubpassEndInfo,                                                        VkStructureType :: VK_STRUCTURE_TYPE_SUBPASS_END_INFO ),

            __C_ENG_ENUM_FIELD ( PhysicalDevice8BitStorageFeatures,                                     VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_8BIT_STORAGE_FEATURES ),

            __C_ENG_ENUM_FIELD ( PhysicalDeviceDriverProperties,                                        VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DRIVER_PROPERTIES ),

            __C_ENG_ENUM_FIELD ( PhysicalDeviceShaderAtomicInt64Features,                               VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ATOMIC_INT64_FEATURES ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceShaderFloat16Int8Features,                               VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_FLOAT16_INT8_FEATURES ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceFloatControlsProperties,                                 VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FLOAT_CONTROLS_PROPERTIES ),

            __C_ENG_ENUM_FIELD ( DescriptorSetLayoutBindingFlagsCreateInfo,                             VkStructureType :: VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO ),

            __C_ENG_ENUM_FIELD ( PhysicalDeviceDescriptorIndexingFeatures,                              VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_INDEXING_FEATURES ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceDescriptorIndexingProperties,                            VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_INDEXING_PROPERTIES ),

            __C_ENG_ENUM_FIELD ( DescriptorSetVariableDescriptorCountAllocateInfo,                      VkStructureType :: VK_STRUCTURE_TYPE_DESCRIPTOR_SET_VARIABLE_DESCRIPTOR_COUNT_ALLOCATE_INFO ),
            __C_ENG_ENUM_FIELD ( DescriptorSetVariableDescriptorCountLayoutSupport,                     VkStructureType :: VK_STRUCTURE_TYPE_DESCRIPTOR_SET_VARIABLE_DESCRIPTOR_COUNT_LAYOUT_SUPPORT ),

            __C_ENG_ENUM_FIELD ( PhysicalDeviceDepthStencilResolveProperties,                           VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEPTH_STENCIL_RESOLVE_PROPERTIES ),
            __C_ENG_ENUM_FIELD ( SubpassDescriptionDepthStencilResolve,                                 VkStructureType :: VK_STRUCTURE_TYPE_SUBPASS_DESCRIPTION_DEPTH_STENCIL_RESOLVE ),

            __C_ENG_ENUM_FIELD ( PhysicalDeviceScalarBlockLayoutFeatures,                               VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SCALAR_BLOCK_LAYOUT_FEATURES ),

            __C_ENG_ENUM_FIELD ( ImageStencilUsageCreateInfo,                                           VkStructureType :: VK_STRUCTURE_TYPE_IMAGE_STENCIL_USAGE_CREATE_INFO ),

            __C_ENG_ENUM_FIELD ( PhysicalDeviceSamplerFilterMinMaxProperties,                           VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SAMPLER_FILTER_MINMAX_PROPERTIES ),

            __C_ENG_ENUM_FIELD ( SamplerReductionModeCreateInfo,                                        VkStructureType :: VK_STRUCTURE_TYPE_SAMPLER_REDUCTION_MODE_CREATE_INFO ),

            __C_ENG_ENUM_FIELD ( PhysicalDeviceVulkanMemoryModelFeatures,                               VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_MEMORY_MODEL_FEATURES ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceImagelessFramebufferFeatures,                            VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGELESS_FRAMEBUFFER_FEATURES ),

            __C_ENG_ENUM_FIELD ( FramebufferAttachmentsCreateInfo,                                      VkStructureType :: VK_STRUCTURE_TYPE_FRAMEBUFFER_ATTACHMENTS_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( FramebufferAttachmentImageInfo,                                        VkStructureType :: VK_STRUCTURE_TYPE_FRAMEBUFFER_ATTACHMENT_IMAGE_INFO ),
            __C_ENG_ENUM_FIELD ( RenderPassAttachmentBeginInfo,                                         VkStructureType :: VK_STRUCTURE_TYPE_RENDER_PASS_ATTACHMENT_BEGIN_INFO ),

            __C_ENG_ENUM_FIELD ( PhysicalDeviceUniformBufferStandardLayoutFeatures,                     VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_UNIFORM_BUFFER_STANDARD_LAYOUT_FEATURES ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceShaderSubgroupExtendedTypesFeatures,                     VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_SUBGROUP_EXTENDED_TYPES_FEATURES ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceSeparateDepthStencilLayoutsFeatures,                     VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SEPARATE_DEPTH_STENCIL_LAYOUTS_FEATURES ),

            __C_ENG_ENUM_FIELD ( AttachmentReferenceStencilLayout,                                      VkStructureType :: VK_STRUCTURE_TYPE_ATTACHMENT_REFERENCE_STENCIL_LAYOUT ),
            __C_ENG_ENUM_FIELD ( AttachmentDescriptionStencilLayout,                                    VkStructureType :: VK_STRUCTURE_TYPE_ATTACHMENT_DESCRIPTION_STENCIL_LAYOUT ),

            __C_ENG_ENUM_FIELD ( PhysicalDeviceHostQueryResetFeatures,                                  VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_HOST_QUERY_RESET_FEATURES ),

            __C_ENG_ENUM_FIELD ( PhysicalDeviceTimelineSemaphoreFeatures,                               VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TIMELINE_SEMAPHORE_FEATURES ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceTimelineSemaphoreProperties,                             VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TIMELINE_SEMAPHORE_PROPERTIES ),

            __C_ENG_ENUM_FIELD ( SemaphoreTypeCreateInfo,                                               VkStructureType :: VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( TimelineSemaphoreSubmitInfo,                                           VkStructureType :: VK_STRUCTURE_TYPE_TIMELINE_SEMAPHORE_SUBMIT_INFO ),
            __C_ENG_ENUM_FIELD ( SemaphoreWaitInfo,                                                     VkStructureType :: VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO ),
            __C_ENG_ENUM_FIELD ( SemaphoreSignalInfo,                                                   VkStructureType :: VK_STRUCTURE_TYPE_SEMAPHORE_SIGNAL_INFO ),

            __C_ENG_ENUM_FIELD ( PhysicalDeviceBufferDeviceAddressFeatures,                             VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BUFFER_DEVICE_ADDRESS_FEATURES ),
            __C_ENG_ENUM_FIELD ( BufferDeviceAddressInfo,                                               VkStructureType :: VK_STRUCTURE_TYPE_BUFFER_DEVICE_ADDRESS_INFO ),
            __C_ENG_ENUM_FIELD ( BufferOpaqueCaptureAddressCreateInfo,                                  VkStructureType :: VK_STRUCTURE_TYPE_BUFFER_OPAQUE_CAPTURE_ADDRESS_CREATE_INFO ),
            __C_ENG_ENUM_FIELD ( MemoryOpaqueCaptureAddressAllocateInfo,                                VkStructureType :: VK_STRUCTURE_TYPE_MEMORY_OPAQUE_CAPTURE_ADDRESS_ALLOCATE_INFO ),
            __C_ENG_ENUM_FIELD ( DeviceMemoryOpaqueCaptureAddressInfo,                                  VkStructureType :: VK_STRUCTURE_TYPE_DEVICE_MEMORY_OPAQUE_CAPTURE_ADDRESS_INFO ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SWAP_CHAIN_AVAILABLE

            __C_ENG_ENUM_FIELD ( SwapchainCreateInfo,                                                   VkStructureType :: VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR ),
            __C_ENG_ENUM_FIELD ( PresentInfo,                                                           VkStructureType :: VK_STRUCTURE_TYPE_PRESENT_INFO_KHR ),

#endif

#if ( __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SWAP_CHAIN_AVAILABLE ) || ( __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DEVICE_GROUP_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SWAP_CHAIN_AVAILABLE )

            __C_ENG_ENUM_FIELD ( DeviceGroupPresentCapabilities,                                        VkStructureType :: VK_STRUCTURE_TYPE_DEVICE_GROUP_PRESENT_CAPABILITIES_KHR ),

            __C_ENG_ENUM_FIELD ( ImageSwapchainCreateInfo,                                              VkStructureType :: VK_STRUCTURE_TYPE_IMAGE_SWAPCHAIN_CREATE_INFO_KHR ),

            __C_ENG_ENUM_FIELD ( BindImageMemorySwapchainInfo,                                          VkStructureType :: VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_SWAPCHAIN_INFO_KHR ),
            __C_ENG_ENUM_FIELD ( AcquireNextImageInfo,                                                  VkStructureType :: VK_STRUCTURE_TYPE_ACQUIRE_NEXT_IMAGE_INFO_KHR ),

            __C_ENG_ENUM_FIELD ( DeviceGroupPresentInfo,                                                VkStructureType :: VK_STRUCTURE_TYPE_DEVICE_GROUP_PRESENT_INFO_KHR ),
            __C_ENG_ENUM_FIELD ( DeviceGroupSwapchainCreateInfo,                                        VkStructureType :: VK_STRUCTURE_TYPE_DEVICE_GROUP_SWAPCHAIN_CREATE_INFO_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DISPLAY_AVAILABLE

            __C_ENG_ENUM_FIELD ( DisplayModeCreateInfo,                                                 VkStructureType :: VK_STRUCTURE_TYPE_DISPLAY_MODE_CREATE_INFO_KHR ),
            __C_ENG_ENUM_FIELD ( DisplaySurfaceCreateInfo,                                              VkStructureType :: VK_STRUCTURE_TYPE_DISPLAY_SURFACE_CREATE_INFO_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DISPLAY_SWAP_CHAIN_AVAILABLE

            __C_ENG_ENUM_FIELD ( DisplayPresentInfo,                                                    VkStructureType :: VK_STRUCTURE_TYPE_DISPLAY_PRESENT_INFO_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_XLIB_SURFACE_AVAILABLE

            __C_ENG_ENUM_FIELD ( XLibSurfaceCreateInfo,                                                 VkStructureType :: VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_XCB_SURFACE_AVAILABLE

            __C_ENG_ENUM_FIELD ( XcbSurfaceCreateInfo,                                                  VkStructureType :: VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_WAYLAND_SURFACE_AVAILABLE

            __C_ENG_ENUM_FIELD ( WaylandSurfaceCreateInfo,                                              VkStructureType :: VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ANDROID_SURFACE_AVAILABLE

            __C_ENG_ENUM_FIELD ( AndroidSurfaceCreateInfo,                                              VkStructureType :: VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_WIN32_SURFACE_AVAILABLE

            __C_ENG_ENUM_FIELD ( Win32SurfaceCreateInfo,                                                VkStructureType :: VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEBUG_REPORT_AVAILABLE

            __C_ENG_ENUM_FIELD ( DebugReportCallbackCreateInfo,                                         VkStructureType :: VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_RASTERIZATION_ORDER_AVAILABLE

            __C_ENG_ENUM_FIELD ( PipelineRasterizationStateRasterizationOrderAMD,                       VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_RASTERIZATION_ORDER_AMD ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEBUG_MARKER_AVAILABLE

            __C_ENG_ENUM_FIELD ( DebugMarkerObjectNameInfo,                                             VkStructureType :: VK_STRUCTURE_TYPE_DEBUG_MARKER_OBJECT_NAME_INFO_EXT ),
            __C_ENG_ENUM_FIELD ( DebugMarkerObjectTagInfo,                                              VkStructureType :: VK_STRUCTURE_TYPE_DEBUG_MARKER_OBJECT_TAG_INFO_EXT ),
            __C_ENG_ENUM_FIELD ( DebugMarkerMarkerInfo,                                                 VkStructureType :: VK_STRUCTURE_TYPE_DEBUG_MARKER_MARKER_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE

            __C_ENG_ENUM_FIELD ( VideoProfile,                                                          VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_PROFILE_KHR ),
            __C_ENG_ENUM_FIELD ( VideoCapabilities,                                                     VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_CAPABILITIES_KHR ),
            __C_ENG_ENUM_FIELD ( VideoPictureResource,                                                  VkStructureType :: VK_STRUCTURE_VIDEO_PICTURE_RESOURCE_KHR ),
            __C_ENG_ENUM_FIELD ( VideoGetMemoryProperties,                                              VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_GET_MEMORY_PROPERTIES_KHR ),
            __C_ENG_ENUM_FIELD ( VideoBindMemory,                                                       VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_BIND_MEMORY_KHR ),
            __C_ENG_ENUM_FIELD ( VideoSessionCreateInfo,                                                VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_SESSION_CREATE_INFO_KHR ),
            __C_ENG_ENUM_FIELD ( VideoSessionParametersCreateInfo,                                      VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_SESSION_PARAMETERS_CREATE_INFO_KHR ),
            __C_ENG_ENUM_FIELD ( VideoSessionParametersUpdateInfo,                                      VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_SESSION_PARAMETERS_UPDATE_INFO_KHR ),
            __C_ENG_ENUM_FIELD ( VideoBeginCodingInfo,                                                  VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_BEGIN_CODING_INFO_KHR ),
            __C_ENG_ENUM_FIELD ( VideoEndCodingInfo,                                                    VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_END_CODING_INFO_KHR ),
            __C_ENG_ENUM_FIELD ( VideoCodingControlInfo,                                                VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_CODING_CONTROL_INFO_KHR ),
            __C_ENG_ENUM_FIELD ( VideoReferenceSlot,                                                    VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_REFERENCE_SLOT_KHR ),
            __C_ENG_ENUM_FIELD ( VideoQueueFamilyProperties,                                            VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_QUEUE_FAMILY_PROPERTIES_2_KHR ),
            __C_ENG_ENUM_FIELD ( VideoProfiles,                                                         VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_PROFILES_KHR ),

            __C_ENG_ENUM_FIELD ( PhysicalDeviceVideoFormatInfo,                                         VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VIDEO_FORMAT_INFO_KHR ),

            __C_ENG_ENUM_FIELD ( VideoFormatProperties,                                                 VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_FORMAT_PROPERTIES_KHR ),

            __C_ENG_ENUM_FIELD ( QueueFamilyQueryResultStatusProperties,                                VkStructureType :: VK_STRUCTURE_TYPE_QUEUE_FAMILY_QUERY_RESULT_STATUS_PROPERTIES_2_KHR ),

            __C_ENG_ENUM_FIELD ( VideoDecodeInfo,                                                       VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_DECODE_INFO_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEDICATED_ALLOCATION_AVAILABLE

            __C_ENG_ENUM_FIELD ( DedicatedAllocationImageCreateInfoNVidia,                              VkStructureType :: VK_STRUCTURE_TYPE_DEDICATED_ALLOCATION_IMAGE_CREATE_INFO_NV ),
            __C_ENG_ENUM_FIELD ( DedicatedAllocationBufferCreateInfoNVidia,                             VkStructureType :: VK_STRUCTURE_TYPE_DEDICATED_ALLOCATION_BUFFER_CREATE_INFO_NV ),
            __C_ENG_ENUM_FIELD ( DedicatedAllocationMemoryAllocateInfoNVidia,                           VkStructureType :: VK_STRUCTURE_TYPE_DEDICATED_ALLOCATION_MEMORY_ALLOCATE_INFO_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceTransformFeedbackFeatures,                               VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TRANSFORM_FEEDBACK_FEATURES_EXT ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceTransformFeedbackProperties,                             VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TRANSFORM_FEEDBACK_PROPERTIES_EXT ),

            __C_ENG_ENUM_FIELD ( PipelineRasterizationStateStreamCreateInfo,                            VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_STREAM_CREATE_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXPERIMENTAL_BINARY_IMPORT_AVAILABLE

            __C_ENG_ENUM_FIELD ( CudaModuleCreateInfoNVidiaExperimental,                                VkStructureType :: VK_STRUCTURE_TYPE_CU_MODULE_CREATE_INFO_NVX ),
            __C_ENG_ENUM_FIELD ( CudaFunctionCreateInfoNVidiaExperimental,                              VkStructureType :: VK_STRUCTURE_TYPE_CU_FUNCTION_CREATE_INFO_NVX ),
            __C_ENG_ENUM_FIELD ( CudaLaunchInfoNVidiaExperimental,                                      VkStructureType :: VK_STRUCTURE_TYPE_CU_LAUNCH_INFO_NVX ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXPERIMENTAL_IMAGE_VIEW_HANDLE_AVAILABLE

            __C_ENG_ENUM_FIELD ( ImageViewHandleInfoNVidiaExperimental,                                 VkStructureType :: VK_STRUCTURE_TYPE_IMAGE_VIEW_HANDLE_INFO_NVX ),
            __C_ENG_ENUM_FIELD ( ImageViewAddressPropertiesNVidiaExperimental,                          VkStructureType :: VK_STRUCTURE_TYPE_IMAGE_VIEW_ADDRESS_PROPERTIES_NVX ),

#endif

#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_VIDEO_ENCODE_H264_AVAILABLE

            __C_ENG_ENUM_FIELD ( VideoEncodeH264Capabilities,                                           VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_CAPABILITIES_EXT ),
            __C_ENG_ENUM_FIELD ( VideoEncodeH264SessionCreateInfo,                                      VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_SESSION_CREATE_INFO_EXT ),
            __C_ENG_ENUM_FIELD ( VideoEncodeH264SessionParametersCreateInfo,                            VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_SESSION_PARAMETERS_CREATE_INFO_EXT ),
            __C_ENG_ENUM_FIELD ( VideoEncodeH264SessionParametersAddInfo,                               VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_SESSION_PARAMETERS_ADD_INFO_EXT ),
            __C_ENG_ENUM_FIELD ( VideoEncodeH264VCLFrameInfo,                                           VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_VCL_FRAME_INFO_EXT ),
            __C_ENG_ENUM_FIELD ( VideoEncodeH264DPBSlotInfo,                                            VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_DPB_SLOT_INFO_EXT ),
            __C_ENG_ENUM_FIELD ( VideoEncodeH264NALUSlice,                                              VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_NALU_SLICE_EXT ),
            __C_ENG_ENUM_FIELD ( VideoEncodeH264EmitPictureParameters,                                  VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_EMIT_PICTURE_PARAMETERS_EXT ),
            __C_ENG_ENUM_FIELD ( VideoEncodeH264Profile,                                                VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_PROFILE_EXT ),
            __C_ENG_ENUM_FIELD ( VideoEncodeH264RateControlInfo,                                        VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_RATE_CONTROL_INFO_EXT ),
            __C_ENG_ENUM_FIELD ( VideoEncodeH264RateControlLayerInfo,                                   VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_RATE_CONTROL_LAYER_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_VIDEO_ENCODE_H265_AVAILABLE

            __C_ENG_ENUM_FIELD ( VideoEncodeH265Capabilities,                                           VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_CAPABILITIES_EXT ),
            __C_ENG_ENUM_FIELD ( VideoEncodeH265SessionCreateInfo,                                      VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_SESSION_CREATE_INFO_EXT ),
            __C_ENG_ENUM_FIELD ( VideoEncodeH265SessionParametersCreateInfo,                            VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_SESSION_PARAMETERS_CREATE_INFO_EXT ),
            __C_ENG_ENUM_FIELD ( VideoEncodeH265SessionParametersAddInfo,                               VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_SESSION_PARAMETERS_ADD_INFO_EXT ),
            __C_ENG_ENUM_FIELD ( VideoEncodeH265VCLFrameInfo,                                           VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_VCL_FRAME_INFO_EXT ),
            __C_ENG_ENUM_FIELD ( VideoEncodeH265DPBSlotInfo,                                            VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_DPB_SLOT_INFO_EXT ),
            __C_ENG_ENUM_FIELD ( VideoEncodeH265NALUSlice,                                              VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_NALU_SLICE_EXT ),
            __C_ENG_ENUM_FIELD ( VideoEncodeH265EmitPictureParameters,                                  VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_EMIT_PICTURE_PARAMETERS_EXT ),
            __C_ENG_ENUM_FIELD ( VideoEncodeH265Profile,                                                VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_PROFILE_EXT ),
            __C_ENG_ENUM_FIELD ( VideoEncodeH265ReferenceLists,                                         VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_REFERENCE_LISTS_EXT ),
            __C_ENG_ENUM_FIELD ( VideoEncodeH265RateControlInfo,                                        VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_RATE_CONTROL_INFO_EXT ),
            __C_ENG_ENUM_FIELD ( VideoEncodeH265RateControlLayerInfo,                                   VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_RATE_CONTROL_LAYER_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_VIDEO_DECODE_H264_AVAILABLE

            __C_ENG_ENUM_FIELD ( VideoDecodeH264Capabilities,                                           VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_CAPABILITIES_EXT ),
            __C_ENG_ENUM_FIELD ( VideoDecodeH264SessionCreateInfo,                                      VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_SESSION_CREATE_INFO_EXT ),
            __C_ENG_ENUM_FIELD ( VideoDecodeH264PictureInfo,                                            VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_PICTURE_INFO_EXT ),
            __C_ENG_ENUM_FIELD ( VideoDecodeH264MVC,                                                    VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_MVC_EXT ),
            __C_ENG_ENUM_FIELD ( VideoDecodeH264Profile,                                                VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_PROFILE_EXT ),
            __C_ENG_ENUM_FIELD ( VideoDecodeH264SessionParametersCreateInfo,                            VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_SESSION_PARAMETERS_CREATE_INFO_EXT ),
            __C_ENG_ENUM_FIELD ( VideoDecodeH264SessionParametersAddInfo,                               VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_SESSION_PARAMETERS_ADD_INFO_EXT ),
            __C_ENG_ENUM_FIELD ( VideoDecodeH264DPBSlotInfo,                                            VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_DPB_SLOT_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_TEXTURE_GATHER_BIAS_LOD_AVAILABLE

            __C_ENG_ENUM_FIELD ( TextureLODGatherFormatPropertiesAMD,                                   VkStructureType :: VK_STRUCTURE_TYPE_TEXTURE_LOD_GATHER_FORMAT_PROPERTIES_AMD ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE

            __C_ENG_ENUM_FIELD ( RenderingInfo,                                                         VkStructureType :: VK_STRUCTURE_TYPE_RENDERING_INFO_KHR ),
            __C_ENG_ENUM_FIELD ( RenderingAttachmentInfo,                                               VkStructureType :: VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO_KHR ),
            __C_ENG_ENUM_FIELD ( PipelineRenderingCreateInfo,                                           VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_RENDERING_CREATE_INFO_KHR ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceDynamicRenderingFeatures,                                VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DYNAMIC_RENDERING_FEATURES_KHR ),
            __C_ENG_ENUM_FIELD ( CommandBufferInheritanceRenderingInfo,                                 VkStructureType :: VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_RENDERING_INFO_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE

            __C_ENG_ENUM_FIELD ( RenderingFragmentShadingRateAttachmentInfo,                            VkStructureType :: VK_STRUCTURE_TYPE_RENDERING_FRAGMENT_SHADING_RATE_ATTACHMENT_INFO_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE

            __C_ENG_ENUM_FIELD ( RenderingFragmentDensityMapAttachmentInfo,                             VkStructureType :: VK_STRUCTURE_TYPE_RENDERING_FRAGMENT_DENSITY_MAP_ATTACHMENT_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_AMD_MIXED_ATTACHMENT_SAMPLES_AVAILABLE

            __C_ENG_ENUM_FIELD ( AttachmentSampleCountInfoAMD,                                          VkStructureType :: VK_STRUCTURE_TYPE_ATTACHMENT_SAMPLE_COUNT_INFO_AMD ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXPERIMENTAL_MULTIVIEW_PER_VIEW_ATTRIBUTES_AVAILABLE

            __C_ENG_ENUM_FIELD ( MutiviewPerViewAttributesInfoNVidiaExperimental,                       VkStructureType :: VK_STRUCTURE_TYPE_MULTIVIEW_PER_VIEW_ATTRIBUTES_INFO_NVX ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceMultiviewPerViewAttributesPropertiesNVidiaExperimental,  VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTIVIEW_PER_VIEW_ATTRIBUTES_PROPERTIES_NVX ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_GAMES_PLATFORM_STREAM_DESCRIPTOR_SURFACE_AVAILABLE

            __C_ENG_ENUM_FIELD ( StreamDescriptorSurfaceCreateInfoGoogle,                               VkStructureType :: VK_STRUCTURE_TYPE_STREAM_DESCRIPTOR_SURFACE_CREATE_INFO_GGP ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_CORNER_SAMPLED_IMAGE_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceCornerSampledImageFeatures,                              VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CORNER_SAMPLED_IMAGE_FEATURES_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_AVAILABLE

            __C_ENG_ENUM_FIELD ( ExternalMemoryImageCreateInfoNVidia,                                   VkStructureType :: VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMAGE_CREATE_INFO_NV ),
            __C_ENG_ENUM_FIELD ( ExportMemoryAllocateInfoNVidia,                                        VkStructureType :: VK_STRUCTURE_TYPE_EXPORT_MEMORY_ALLOCATE_INFO_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_WIN32_AVAILABLE

            __C_ENG_ENUM_FIELD ( ImportMemoryWin32HandleInfoNVidia,                                     VkStructureType :: VK_STRUCTURE_TYPE_IMPORT_MEMORY_WIN32_HANDLE_INFO_NV ),
            __C_ENG_ENUM_FIELD ( ExportMemoryWin32HandleInfoNVidia,                                     VkStructureType :: VK_STRUCTURE_TYPE_EXPORT_MEMORY_WIN32_HANDLE_INFO_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_WIN32_KEYED_MUTEX_AVAILABLE

            __C_ENG_ENUM_FIELD ( Win32KeyedMutexAcquireReleaseInfoNVidia,                               VkStructureType :: VK_STRUCTURE_TYPE_WIN32_KEYED_MUTEX_ACQUIRE_RELEASE_INFO_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_FLAGS_AVAILABLE

            __C_ENG_ENUM_FIELD ( ValidationFlags,                                                       VkStructureType :: VK_STRUCTURE_TYPE_VALIDATION_FLAGS_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_NINTENDO_VI_SURFACE_AVAILABLE

            __C_ENG_ENUM_FIELD ( ViSurfaceCreateInfoNVidia,                                             VkStructureType :: VK_STRUCTURE_TYPE_VI_SURFACE_CREATE_INFO_NN ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXTURE_COMPRESSION_ASTC_HDR_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceTextureCompressionASTCHDRFeatures,                       VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TEXTURE_COMPRESSION_ASTC_HDR_FEATURES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_ASTC_DECODE_MODE_AVAILABLE

            __C_ENG_ENUM_FIELD ( ImageViewASTCDecodeMode,                                               VkStructureType :: VK_STRUCTURE_TYPE_IMAGE_VIEW_ASTC_DECODE_MODE_EXT ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceASTCDecodeFeatures,                                      VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ASTC_DECODE_FEATURES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_MEMORY_WIN32_AVAILABLE

            __C_ENG_ENUM_FIELD ( ImportMemoryWin32HandleInfo,                                           VkStructureType :: VK_STRUCTURE_TYPE_IMPORT_MEMORY_WIN32_HANDLE_INFO_KHR ),
            __C_ENG_ENUM_FIELD ( ExportMemoryWin32HandleInfo,                                           VkStructureType :: VK_STRUCTURE_TYPE_EXPORT_MEMORY_WIN32_HANDLE_INFO_KHR ),
            __C_ENG_ENUM_FIELD ( MemoryWin32HandleProperties,                                           VkStructureType :: VK_STRUCTURE_TYPE_MEMORY_WIN32_HANDLE_PROPERTIES_KHR ),
            __C_ENG_ENUM_FIELD ( MemoryGetWin32HandleInfo,                                              VkStructureType :: VK_STRUCTURE_TYPE_MEMORY_GET_WIN32_HANDLE_INFO_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_MEMORY_FD_AVAILABLE

            __C_ENG_ENUM_FIELD ( ImportMemoryFdInfo,                                                    VkStructureType :: VK_STRUCTURE_TYPE_IMPORT_MEMORY_FD_INFO_KHR ),
            __C_ENG_ENUM_FIELD ( MemoryFdProperties,                                                    VkStructureType :: VK_STRUCTURE_TYPE_MEMORY_FD_PROPERTIES_KHR ),
            __C_ENG_ENUM_FIELD ( MemoryGetFdInfo,                                                       VkStructureType :: VK_STRUCTURE_TYPE_MEMORY_GET_FD_INFO_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_WIN32_KEYED_MUTEX_AVAILABLE

            __C_ENG_ENUM_FIELD ( Win32KeyedMutexAcquireReleaseInfo,                                     VkStructureType :: VK_STRUCTURE_TYPE_WIN32_KEYED_MUTEX_ACQUIRE_RELEASE_INFO_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_SEMAPHORE_WIN32_AVAILABLE

            __C_ENG_ENUM_FIELD ( ImportSemaphoreWin32HandleInfo,                                        VkStructureType :: VK_STRUCTURE_TYPE_IMPORT_SEMAPHORE_WIN32_HANDLE_INFO_KHR ),
            __C_ENG_ENUM_FIELD ( ExportSemaphoreWin32HandleInfo,                                        VkStructureType :: VK_STRUCTURE_TYPE_EXPORT_SEMAPHORE_WIN32_HANDLE_INFO_KHR ),
            __C_ENG_ENUM_FIELD ( D3D12FenceSubmitInfo,                                                  VkStructureType :: VK_STRUCTURE_TYPE_D3D12_FENCE_SUBMIT_INFO_KHR ),
            __C_ENG_ENUM_FIELD ( SemaphoreGetWin32HandleInfo,                                           VkStructureType :: VK_STRUCTURE_TYPE_SEMAPHORE_GET_WIN32_HANDLE_INFO_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_SEMAPHORE_FD_AVAILABLE

            __C_ENG_ENUM_FIELD ( ImportSemaphoreFdInfo,                                                 VkStructureType :: VK_STRUCTURE_TYPE_IMPORT_SEMAPHORE_FD_INFO_KHR ),
            __C_ENG_ENUM_FIELD ( SemaphoreGetFdInfo,                                                    VkStructureType :: VK_STRUCTURE_TYPE_SEMAPHORE_GET_FD_INFO_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PUSH_DESCRIPTOR_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDevicePushDescriptorProperties,                                VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PUSH_DESCRIPTOR_PROPERTIES_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CONDITIONAL_RENDERING_AVAILABLE

            __C_ENG_ENUM_FIELD ( CommandBufferInheritanceConditionalRenderingInfo,                      VkStructureType :: VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_CONDITIONAL_RENDERING_INFO_EXT ),

            __C_ENG_ENUM_FIELD ( PhysicalDeviceConditionalRenderingFeatures,                            VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CONDITIONAL_RENDERING_FEATURES_EXT ),

            __C_ENG_ENUM_FIELD ( ConditionalRenderingBeginInfo,                                         VkStructureType :: VK_STRUCTURE_TYPE_CONDITIONAL_RENDERING_BEGIN_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_INCREMENTAL_PRESENT_AVAILABLE

            __C_ENG_ENUM_FIELD ( PresentRegions,                                                        VkStructureType :: VK_STRUCTURE_TYPE_PRESENT_REGIONS_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_CLIP_SPACE_W_SCALING_AVAILABLE

            __C_ENG_ENUM_FIELD ( PipelineViewportWScalingStateCreateInfoNVidia,                         VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_W_SCALING_STATE_CREATE_INFO_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DISPLAY_SURFACE_COUNTER_AVAILABLE

            __C_ENG_ENUM_FIELD ( SurfaceCapabilities2,                                                  VkStructureType :: VK_STRUCTURE_TYPE_SURFACE_CAPABILITIES_2_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DISPLAY_CONTROL_AVAILABLE

            __C_ENG_ENUM_FIELD ( DisplayPowerInfo,                                                      VkStructureType :: VK_STRUCTURE_TYPE_DISPLAY_POWER_INFO_EXT ),
            __C_ENG_ENUM_FIELD ( DeviceEventInfo,                                                       VkStructureType :: VK_STRUCTURE_TYPE_DEVICE_EVENT_INFO_EXT ),
            __C_ENG_ENUM_FIELD ( DisplayEventInfo,                                                      VkStructureType :: VK_STRUCTURE_TYPE_DISPLAY_EVENT_INFO_EXT ),
            __C_ENG_ENUM_FIELD ( SwapchainCounterCreateInfo,                                            VkStructureType :: VK_STRUCTURE_TYPE_SWAPCHAIN_COUNTER_CREATE_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_DISPLAY_TIMING_AVAILABLE

            __C_ENG_ENUM_FIELD ( PresentTimesInfoGoogle,                                                VkStructureType :: VK_STRUCTURE_TYPE_PRESENT_TIMES_INFO_GOOGLE ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_VIEWPORT_SWIZZLE_AVAILABLE

            __C_ENG_ENUM_FIELD ( PipelineViewportSwizzleStateCreateInfoNVidia,                          VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_SWIZZLE_STATE_CREATE_INFO_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DISCARD_RECTANGLES_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceDiscardRectangleProperties,                              VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DISCARD_RECTANGLE_PROPERTIES_EXT ),
            __C_ENG_ENUM_FIELD ( PipelineDiscardRectangleStateCreateInfo,                               VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_DISCARD_RECTANGLE_STATE_CREATE_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CONSERVATIVE_RASTERIZATION_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceConservativeRasterizationProperties,                     VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CONSERVATIVE_RASTERIZATION_PROPERTIES_EXT ),
            __C_ENG_ENUM_FIELD ( PipelineRasterizationConservativeStateCreateInfo,                      VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_CONSERVATIVE_STATE_CREATE_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_ENABLE_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceDepthClipEnableFeatures,                                 VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEPTH_CLIP_ENABLE_FEATURES_EXT ),
            __C_ENG_ENUM_FIELD ( PipelineRasterizationDepthClipStateCreateInfo,                         VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_DEPTH_CLIP_STATE_CREATE_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_HDR_METADATA_AVAILABLE

            __C_ENG_ENUM_FIELD ( HDRMetadata,                                                           VkStructureType :: VK_STRUCTURE_TYPE_HDR_METADATA_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHARED_PRESENTABLE_IMAGE_AVAILABLE

            __C_ENG_ENUM_FIELD ( SharedPresentSurfaceCapabilities,                                      VkStructureType :: VK_STRUCTURE_TYPE_SHARED_PRESENT_SURFACE_CAPABILITIES_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_FENCE_WIN32_AVAILABLE

            __C_ENG_ENUM_FIELD ( ImportFenceWin32HandleInfo,                                            VkStructureType :: VK_STRUCTURE_TYPE_IMPORT_FENCE_WIN32_HANDLE_INFO_KHR ),
            __C_ENG_ENUM_FIELD ( ExportFenceWin32HandleInfo,                                            VkStructureType :: VK_STRUCTURE_TYPE_EXPORT_FENCE_WIN32_HANDLE_INFO_KHR ),
            __C_ENG_ENUM_FIELD ( FenceGetWin32HandleInfo,                                               VkStructureType :: VK_STRUCTURE_TYPE_FENCE_GET_WIN32_HANDLE_INFO_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_FENCE_FD_AVAILABLE

            __C_ENG_ENUM_FIELD ( ImportFenceFdInfo,                                                     VkStructureType :: VK_STRUCTURE_TYPE_IMPORT_FENCE_FD_INFO_KHR ),
            __C_ENG_ENUM_FIELD ( FenceGetFdInfo,                                                        VkStructureType :: VK_STRUCTURE_TYPE_FENCE_GET_FD_INFO_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDevicePerformanceQueryFeatures,                                VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PERFORMANCE_QUERY_FEATURES_KHR ),
            __C_ENG_ENUM_FIELD ( PhysicalDevicePerformanceQueryProperties,                              VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PERFORMANCE_QUERY_PROPERTIES_KHR ),
            __C_ENG_ENUM_FIELD ( QueryPoolPerformanceCreateInfo,                                        VkStructureType :: VK_STRUCTURE_TYPE_QUERY_POOL_PERFORMANCE_CREATE_INFO_KHR ),
            __C_ENG_ENUM_FIELD ( PerformanceQuerySubmitInfo,                                            VkStructureType :: VK_STRUCTURE_TYPE_PERFORMANCE_QUERY_SUBMIT_INFO_KHR ),
            __C_ENG_ENUM_FIELD ( AcquireProfilingLockInfo,                                              VkStructureType :: VK_STRUCTURE_TYPE_ACQUIRE_PROFILING_LOCK_INFO_KHR ),
            __C_ENG_ENUM_FIELD ( PerformanceCounter,                                                    VkStructureType :: VK_STRUCTURE_TYPE_PERFORMANCE_COUNTER_KHR ),
            __C_ENG_ENUM_FIELD ( PerformanceCounterDescription,                                         VkStructureType :: VK_STRUCTURE_TYPE_PERFORMANCE_COUNTER_DESCRIPTION_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_GET_SURFACE_CAPABILITIES_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceSurfaceInfo,                                             VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SURFACE_INFO_2_KHR ),
            __C_ENG_ENUM_FIELD ( SurfaceCapabilities,                                                   VkStructureType :: VK_STRUCTURE_TYPE_SURFACE_CAPABILITIES_2_KHR ),
            __C_ENG_ENUM_FIELD ( SurfaceFormat,                                                         VkStructureType :: VK_STRUCTURE_TYPE_SURFACE_FORMAT_2_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_GET_DISPLAY_PROPERTIES_AVAILABLE

            __C_ENG_ENUM_FIELD ( DisplayProperties,                                                     VkStructureType :: VK_STRUCTURE_TYPE_DISPLAY_PROPERTIES_2_KHR ),
            __C_ENG_ENUM_FIELD ( DisplayPlaneProperties,                                                VkStructureType :: VK_STRUCTURE_TYPE_DISPLAY_PLANE_PROPERTIES_2_KHR ),
            __C_ENG_ENUM_FIELD ( DisplayModeProperties,                                                 VkStructureType :: VK_STRUCTURE_TYPE_DISPLAY_MODE_PROPERTIES_2_KHR ),
            __C_ENG_ENUM_FIELD ( DisplayPlaneInfo,                                                      VkStructureType :: VK_STRUCTURE_TYPE_DISPLAY_PLANE_INFO_2_KHR ),
            __C_ENG_ENUM_FIELD ( DisplayPlaneCapabilities,                                              VkStructureType :: VK_STRUCTURE_TYPE_DISPLAY_PLANE_CAPABILITIES_2_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_APPLE_MOLTEN_VULKAN_IOS_SURFACE_AVAILABLE

            __C_ENG_ENUM_FIELD ( IOSSurfaceCreateInfoApple,                                             VkStructureType :: VK_STRUCTURE_TYPE_IOS_SURFACE_CREATE_INFO_MVK ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_APPLE_MOLTEN_VULKAN_MACOS_SURFACE_AVAILABLE

            __C_ENG_ENUM_FIELD ( MacOSSurfaceCreateInfoApple,                                           VkStructureType :: VK_STRUCTURE_TYPE_MACOS_SURFACE_CREATE_INFO_MVK ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEBUG_UTILS_AVAILABLE

            __C_ENG_ENUM_FIELD ( DebugUtilsObjectNameInfo,                                              VkStructureType :: VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT ),
            __C_ENG_ENUM_FIELD ( DebugUtilsObjectTagInfo,                                               VkStructureType :: VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_TAG_INFO_EXT ),
            __C_ENG_ENUM_FIELD ( DebugUtilsLabel,                                                       VkStructureType :: VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT ),
            __C_ENG_ENUM_FIELD ( DebugUtilsMessengerCallbackData,                                       VkStructureType :: VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CALLBACK_DATA_EXT ),
            __C_ENG_ENUM_FIELD ( DebugUtilsMessengerCreateInfo,                                         VkStructureType :: VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_ANDROID_EXTERNAL_MEMORY_ANDROID_HARDWARE_BUFFER_AVAILABLE

            __C_ENG_ENUM_FIELD ( AndroidHardwareBufferUsageGoogle,                                      VkStructureType :: VK_STRUCTURE_TYPE_ANDROID_HARDWARE_BUFFER_USAGE_ANDROID ),
            __C_ENG_ENUM_FIELD ( AndroidHardwareBufferPropertiesGoogle,                                 VkStructureType :: VK_STRUCTURE_TYPE_ANDROID_HARDWARE_BUFFER_PROPERTIES_ANDROID ),
            __C_ENG_ENUM_FIELD ( AndroidHardwareBufferFormatPropertiesGoogle,                           VkStructureType :: VK_STRUCTURE_TYPE_ANDROID_HARDWARE_BUFFER_FORMAT_PROPERTIES_ANDROID ),
            __C_ENG_ENUM_FIELD ( ImportAndroidHardwareBufferInfoGoogle,                                 VkStructureType :: VK_STRUCTURE_TYPE_IMPORT_ANDROID_HARDWARE_BUFFER_INFO_ANDROID ),
            __C_ENG_ENUM_FIELD ( MemoryGetAndroidHardwareBufferInfoGoogle,                              VkStructureType :: VK_STRUCTURE_TYPE_MEMORY_GET_ANDROID_HARDWARE_BUFFER_INFO_ANDROID ),
            __C_ENG_ENUM_FIELD ( ExternalFormatGoogle,                                                  VkStructureType :: VK_STRUCTURE_TYPE_EXTERNAL_FORMAT_ANDROID ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FORMAT_FEATURE_FLAGS_AVAILABLE && __C_ENG_VULKAN_API_ANDROID_EXTERNAL_MEMORY_ANDROID_HARDWARE_BUFFER_AVAILABLE

            __C_ENG_ENUM_FIELD ( AndroidHardwareBufferFormatPropertiesGoogle,                           VkStructureType :: VK_STRUCTURE_TYPE_ANDROID_HARDWARE_BUFFER_FORMAT_PROPERTIES_2_ANDROID ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceInlineUniformBlockFeatures,                              VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INLINE_UNIFORM_BLOCK_FEATURES_EXT ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceInlineUniformBlockProperties,                            VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INLINE_UNIFORM_BLOCK_PROPERTIES_EXT ),
            __C_ENG_ENUM_FIELD ( WriteDescriptorSetInlineUniformBlock,                                  VkStructureType :: VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET_INLINE_UNIFORM_BLOCK_EXT ),
            __C_ENG_ENUM_FIELD ( DescriptorPoolInlineUniformBlockCreateInfo,                            VkStructureType :: VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_INLINE_UNIFORM_BLOCK_CREATE_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SAMPLE_LOCATIONS_AVAILABLE

            __C_ENG_ENUM_FIELD ( SampleLocationsInfo,                                                   VkStructureType :: VK_STRUCTURE_TYPE_SAMPLE_LOCATIONS_INFO_EXT ),
            __C_ENG_ENUM_FIELD ( RenderPassSampleLocationsBeginInfo,                                    VkStructureType :: VK_STRUCTURE_TYPE_RENDER_PASS_SAMPLE_LOCATIONS_BEGIN_INFO_EXT ),
            __C_ENG_ENUM_FIELD ( PipelineSampleLocationsStateCreateInfo,                                VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_SAMPLE_LOCATIONS_STATE_CREATE_INFO_EXT ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceSampleLocationsProperties,                               VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SAMPLE_LOCATIONS_PROPERTIES_EXT ),
            __C_ENG_ENUM_FIELD ( MultisampleProperties,                                                 VkStructureType :: VK_STRUCTURE_TYPE_MULTISAMPLE_PROPERTIES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_BLEND_OPERATION_ADVANCED_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceBlendOperationAdvancedFeatures,                          VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BLEND_OPERATION_ADVANCED_FEATURES_EXT ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceBlendOperationAdvancedProperties,                        VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BLEND_OPERATION_ADVANCED_PROPERTIES_EXT ),
            __C_ENG_ENUM_FIELD ( PipelineColorBlendAdvancedStateCreateInfo,                             VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_ADVANCED_STATE_CREATE_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_COVERAGE_TO_COLOR_AVAILABLE

            __C_ENG_ENUM_FIELD ( PipelineCoverageToColorStateCreateInfoNVidia,                          VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_COVERAGE_TO_COLOR_STATE_CREATE_INFO_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE

            __C_ENG_ENUM_FIELD ( WriteDescriptorSetAccelerationStructure,                               VkStructureType :: VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET_ACCELERATION_STRUCTURE_KHR ),

            __C_ENG_ENUM_FIELD ( AccelerationStructureBuildGeometryInfo,                                VkStructureType :: VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR ),
            __C_ENG_ENUM_FIELD ( AccelerationStructureDeviceAddressInfo,                                VkStructureType :: VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_DEVICE_ADDRESS_INFO_KHR ),
            __C_ENG_ENUM_FIELD ( AccelerationStructureGeometryAABBSData,                                VkStructureType :: VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_AABBS_DATA_KHR ),
            __C_ENG_ENUM_FIELD ( AccelerationStructureGeometryInstancesData,                            VkStructureType :: VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_INSTANCES_DATA_KHR ),
            __C_ENG_ENUM_FIELD ( AccelerationStructureGeometryTrianglesData,                            VkStructureType :: VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR ),
            __C_ENG_ENUM_FIELD ( AccelerationStructureGeometry,                                         VkStructureType :: VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR ),
            __C_ENG_ENUM_FIELD ( AccelerationStructureVersionInfo,                                      VkStructureType :: VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_VERSION_INFO_KHR ),

            __C_ENG_ENUM_FIELD ( CopyAccelerationStructureInfo,                                         VkStructureType :: VK_STRUCTURE_TYPE_COPY_ACCELERATION_STRUCTURE_INFO_KHR ),
            __C_ENG_ENUM_FIELD ( CopyAccelerationStructureToMemoryInfo,                                 VkStructureType :: VK_STRUCTURE_TYPE_COPY_ACCELERATION_STRUCTURE_TO_MEMORY_INFO_KHR ),
            __C_ENG_ENUM_FIELD ( CopyMemoryToAccelerationStructureInfo,                                 VkStructureType :: VK_STRUCTURE_TYPE_COPY_MEMORY_TO_ACCELERATION_STRUCTURE_INFO_KHR ),

            __C_ENG_ENUM_FIELD ( PhysicalDeviceAccelerationStructureFeatures,                           VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ACCELERATION_STRUCTURE_FEATURES_KHR ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceAccelerationStructureProperties,                         VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ACCELERATION_STRUCTURE_PROPERTIES_KHR ),

            __C_ENG_ENUM_FIELD ( AccelerationStructureCreateInfo,                                       VkStructureType :: VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR ),
            __C_ENG_ENUM_FIELD ( AccelerationStructureBuildSizesInfo,                                   VkStructureType :: VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceRayTracingPipelineFeatures,                              VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PIPELINE_FEATURES_KHR ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceRayTracingPipelineProperties,                            VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PIPELINE_PROPERTIES_KHR ),
            __C_ENG_ENUM_FIELD ( RayTracingPipelineCreateInfo,                                          VkStructureType :: VK_STRUCTURE_TYPE_RAY_TRACING_PIPELINE_CREATE_INFO_KHR ),
            __C_ENG_ENUM_FIELD ( RayTracingShaderGroupCreateInfo,                                       VkStructureType :: VK_STRUCTURE_TYPE_RAY_TRACING_SHADER_GROUP_CREATE_INFO_KHR ),
            __C_ENG_ENUM_FIELD ( RayTracingPipelineInterfaceCreateInfo,                                 VkStructureType :: VK_STRUCTURE_TYPE_RAY_TRACING_PIPELINE_INTERFACE_CREATE_INFO_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_QUERY_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceRayQueryFeatures,                                        VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_QUERY_FEATURES_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAMEBUFFER_MIXED_SAMPLES_AVAILABLE

            __C_ENG_ENUM_FIELD ( PipelineCoverageModulationStateCreateInfoNVidia,                       VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_COVERAGE_MODULATION_STATE_CREATE_INFO_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_SM_BUILTINS_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceShaderSmBuiltinsFeaturesNVidia,                          VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_SM_BUILTINS_FEATURES_NV ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceShaderSmBuiltinsPropertiesNVidia,                        VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_SM_BUILTINS_PROPERTIES_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_DRM_FORMAT_MODIFIER_AVAILABLE

            __C_ENG_ENUM_FIELD ( DRMFormatModifierPropertiesList,                                       VkStructureType :: VK_STRUCTURE_TYPE_DRM_FORMAT_MODIFIER_PROPERTIES_LIST_EXT ),

            __C_ENG_ENUM_FIELD ( PhysicalDeviceImageDRMFormatModifierInfo,                              VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_DRM_FORMAT_MODIFIER_INFO_EXT ),

            __C_ENG_ENUM_FIELD ( ImageDRMFormatModifierListCreateInfo,                                  VkStructureType :: VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_LIST_CREATE_INFO_EXT ),
            __C_ENG_ENUM_FIELD ( ImageDRMFormatModifierExplicitCreateInfo,                              VkStructureType :: VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_EXPLICIT_CREATE_INFO_EXT ),
            __C_ENG_ENUM_FIELD ( ImageDRMFormatModifierProperties,                                      VkStructureType :: VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_PROPERTIES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_DRM_FORMAT_MODIFIER_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FORMAT_FEATURE_FLAGS_AVAILABLE

            __C_ENG_ENUM_FIELD ( DRMFormatModifierPropertiesList2,                                      VkStructureType :: VK_STRUCTURE_TYPE_DRM_FORMAT_MODIFIER_PROPERTIES_LIST_2_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_CACHE_AVAILABLE

            __C_ENG_ENUM_FIELD ( ValidationCacheCreateInfo,                                             VkStructureType :: VK_STRUCTURE_TYPE_VALIDATION_CACHE_CREATE_INFO_EXT ),
            __C_ENG_ENUM_FIELD ( ShaderModuleValidationCacheCreateInfo,                                 VkStructureType :: VK_STRUCTURE_TYPE_SHADER_MODULE_VALIDATION_CACHE_CREATE_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PORTABILITY_SUBSET_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDevicePortabilitySubsetFeatures,                               VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PORTABILITY_SUBSET_FEATURES_KHR ),
            __C_ENG_ENUM_FIELD ( PhysicalDevicePortabilitySubsetProperties,                             VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PORTABILITY_SUBSET_PROPERTIES_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE

            __C_ENG_ENUM_FIELD ( PipelineViewportShadingRateImageStateCreateInfoNVidia,                 VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_SHADING_RATE_IMAGE_STATE_CREATE_INFO_NV ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceShadingRateImageFeaturesNVidia,                          VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADING_RATE_IMAGE_FEATURES_NV ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceShadingRateImagePropertiesNVidia,                        VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADING_RATE_IMAGE_PROPERTIES_NV ),
            __C_ENG_ENUM_FIELD ( PipelineViewportCoarseSampleOrderStateCreateInfoNVidia,                VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_COARSE_SAMPLE_ORDER_STATE_CREATE_INFO_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE

            __C_ENG_ENUM_FIELD ( RayTracingPipelineCreateInfoNVidia,                                    VkStructureType :: VK_STRUCTURE_TYPE_RAY_TRACING_PIPELINE_CREATE_INFO_NV ),
            __C_ENG_ENUM_FIELD ( AccelerationStructureCreateInfoNVidia,                                 VkStructureType :: VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_NV ),

            __C_ENG_ENUM_FIELD ( GeometryNVidia,                                                        VkStructureType :: VK_STRUCTURE_TYPE_GEOMETRY_NV ),
            __C_ENG_ENUM_FIELD ( GeometryTrianglesNVidia,                                               VkStructureType :: VK_STRUCTURE_TYPE_GEOMETRY_TRIANGLES_NV ),
            __C_ENG_ENUM_FIELD ( GeometryAABBNVidia,                                                    VkStructureType :: VK_STRUCTURE_TYPE_GEOMETRY_AABB_NV ),

            __C_ENG_ENUM_FIELD ( BindAccelerationStructureMemoryInfoNVidia,                             VkStructureType :: VK_STRUCTURE_TYPE_BIND_ACCELERATION_STRUCTURE_MEMORY_INFO_NV ),
            __C_ENG_ENUM_FIELD ( WriteDescriptorSetAccelerationStructureNVidia,                         VkStructureType :: VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET_ACCELERATION_STRUCTURE_NV ),
            __C_ENG_ENUM_FIELD ( AccelerationStructureMemoryRequirementsInfoNVidia,                     VkStructureType :: VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_INFO_NV ),

            __C_ENG_ENUM_FIELD ( PhysicalDeviceRayTracingPropertiesNVidia,                              VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PROPERTIES_NV ),

            __C_ENG_ENUM_FIELD ( RayTracingShaderGroupCreateInfoNVidia,                                 VkStructureType :: VK_STRUCTURE_TYPE_RAY_TRACING_SHADER_GROUP_CREATE_INFO_NV ),
            __C_ENG_ENUM_FIELD ( AccelerationStructureInfoNVidia,                                       VkStructureType :: VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_INFO_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_REPRESENTATIVE_FRAGMENT_TEST_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceRepresentativeFragmentTestFeaturesNVidia,                VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_REPRESENTATIVE_FRAGMENT_TEST_FEATURES_NV ),
            __C_ENG_ENUM_FIELD ( PipelineRepresentativeFragmentTestStateCreateInfoNVidia,               VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_REPRESENTATIVE_FRAGMENT_TEST_STATE_CREATE_INFO_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FILTER_CUBIC_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceImageViewImageFormatInfo,                                VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_VIEW_IMAGE_FORMAT_INFO_EXT ),
            __C_ENG_ENUM_FIELD ( FilterCubicImageViewImageFormatProperties,                             VkStructureType :: VK_STRUCTURE_TYPE_FILTER_CUBIC_IMAGE_VIEW_IMAGE_FORMAT_PROPERTIES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GLOBAL_PRIORITY_AVAILABLE

            __C_ENG_ENUM_FIELD ( DeviceQueueGlobalPriorityCreateInfo,                                   VkStructureType :: VK_STRUCTURE_TYPE_DEVICE_QUEUE_GLOBAL_PRIORITY_CREATE_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTERNAL_MEMORY_HOST_AVAILABLE

            __C_ENG_ENUM_FIELD ( ImportMemoryHostPointerInfo,                                           VkStructureType :: VK_STRUCTURE_TYPE_IMPORT_MEMORY_HOST_POINTER_INFO_EXT ),
            __C_ENG_ENUM_FIELD ( MemoryHostPointerProperties,                                           VkStructureType :: VK_STRUCTURE_TYPE_MEMORY_HOST_POINTER_PROPERTIES_EXT ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceExternalMemoryHostProperties,                            VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_MEMORY_HOST_PROPERTIES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_CLOCK_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceShaderClockFeatures,                                     VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_CLOCK_FEATURES_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_PIPELINE_COMPILER_CONTROL_AVAILABLE

            __C_ENG_ENUM_FIELD ( PipelineCompilerControlCreateInfoAMD,                                  VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_COMPILER_CONTROL_CREATE_INFO_AMD ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CALIBRATED_TIMESTAMPS_AVAILABLE

            __C_ENG_ENUM_FIELD ( CalibratedTimestampInfo,                                               VkStructureType :: VK_STRUCTURE_TYPE_CALIBRATED_TIMESTAMP_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_SHADER_CORE_PROPERTIES_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceShaderCorePropertiesAMD,                                 VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_CORE_PROPERTIES_AMD ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_SHADER_CORE_PROPERTIES_2_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceShaderCoreProperties2AMD,                                VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_CORE_PROPERTIES_2_AMD ),

#endif

#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_VIDEO_DECODE_H265_AVAILABLE

            __C_ENG_ENUM_FIELD ( VideoDecodeH265Capabilities,                                           VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_CAPABILITIES_EXT ),
            __C_ENG_ENUM_FIELD ( VideoDecodeH265SessionCreateInfo,                                      VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_SESSION_CREATE_INFO_EXT ),
            __C_ENG_ENUM_FIELD ( VideoDecodeH265SessionParametersCreateInfo,                            VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_SESSION_PARAMETERS_CREATE_INFO_EXT ),
            __C_ENG_ENUM_FIELD ( VideoDecodeH265SessionParametersAddInfo,                               VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_SESSION_PARAMETERS_ADD_INFO_EXT ),
            __C_ENG_ENUM_FIELD ( VideoDecodeH265SessionProfile,                                         VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_PROFILE_EXT ),
            __C_ENG_ENUM_FIELD ( VideoDecodeH265SessionPictureInfo,                                     VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_PICTURE_INFO_EXT ),
            __C_ENG_ENUM_FIELD ( VideoDecodeH265SessionDPBSlotInfo,                                     VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_DPB_SLOT_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_MEMORY_OVERALLOCATION_BEHAVIOUR_AVAILABLE

            __C_ENG_ENUM_FIELD ( DeviceMemoryOverAllocationCreateInfoAMD,                               VkStructureType :: VK_STRUCTURE_TYPE_DEVICE_MEMORY_OVERALLOCATION_CREATE_INFO_AMD ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_ATTRIBUTE_DIVISOR_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceVertexAttributeDivisorFeatures,                          VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VERTEX_ATTRIBUTE_DIVISOR_FEATURES_EXT ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceVertexAttributeDivisorProperties,                        VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VERTEX_ATTRIBUTE_DIVISOR_PROPERTIES_EXT ),
            __C_ENG_ENUM_FIELD ( PipelineVertexInputDivisorStateCreateInfo,                             VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_DIVISOR_STATE_CREATE_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_GAMES_PLATFORM_FRAME_TOKEN_AVAILABLE

            __C_ENG_ENUM_FIELD ( PresentFrameTokenGoogle,                                               VkStructureType :: VK_STRUCTURE_TYPE_PRESENT_FRAME_TOKEN_GGP ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_FEEDBACK_AVAILABLE

            __C_ENG_ENUM_FIELD ( PipelineCreationFeedbackCreateInfo,                                    VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_CREATION_FEEDBACK_CREATE_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COMPUTE_SHADER_DERIVATIVES_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceComputeShaderDerivativesFeaturesNVidia,                  VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COMPUTE_SHADER_DERIVATIVES_FEATURES_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_MESH_SHADER_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceMeshShaderFeaturesNVidia,                                VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MESH_SHADER_FEATURES_NV ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceMeshShaderPropertiesNVidia,                              VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MESH_SHADER_PROPERTIES_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADER_BARYCENTRIC_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceFragmentShaderBarycentricFeaturesNVidia,                 VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADER_BARYCENTRIC_FEATURES_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_IMAGE_FOOTPRINT_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceShaderImageFootprintFeaturesNVidia,                      VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_IMAGE_FOOTPRINT_FEATURES_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SCISSOR_EXCLUSIVE_AVAILABLE

            __C_ENG_ENUM_FIELD ( PipelineViewportExclusiveScissorStateCreateInfoNVidia,                 VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_EXCLUSIVE_SCISSOR_STATE_CREATE_INFO_NV ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceExclusiveScissorFeaturesNVidia,                          VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXCLUSIVE_SCISSOR_FEATURES_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTIC_CHECKPOINTS_AVAILABLE

            __C_ENG_ENUM_FIELD ( CheckpointDataNVidia,                                                  VkStructureType :: VK_STRUCTURE_TYPE_CHECKPOINT_DATA_NV ),
            __C_ENG_ENUM_FIELD ( QueueFamilyCheckpointPropertiesNVidia,                                 VkStructureType :: VK_STRUCTURE_TYPE_QUEUE_FAMILY_CHECKPOINT_PROPERTIES_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_SHADER_INTEGER_FUNCTIONS_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceShaderIntegerFunctionFeaturesIntel,                      VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_INTEGER_FUNCTIONS_2_FEATURES_INTEL ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_PERFORMANCE_QUERY_AVAILABLE

            __C_ENG_ENUM_FIELD ( QueryPoolPerformanceQueryCreateInfoIntel,                              VkStructureType :: VK_STRUCTURE_TYPE_QUERY_POOL_PERFORMANCE_QUERY_CREATE_INFO_INTEL ),
            __C_ENG_ENUM_FIELD ( InitializePerformanceAPIInfoIntel,                                     VkStructureType :: VK_STRUCTURE_TYPE_INITIALIZE_PERFORMANCE_API_INFO_INTEL ),
            __C_ENG_ENUM_FIELD ( PerformanceMarkerInfoIntel,                                            VkStructureType :: VK_STRUCTURE_TYPE_PERFORMANCE_MARKER_INFO_INTEL ),
            __C_ENG_ENUM_FIELD ( PerformanceStreamMarkerInfoIntel,                                      VkStructureType :: VK_STRUCTURE_TYPE_PERFORMANCE_STREAM_MARKER_INFO_INTEL ),
            __C_ENG_ENUM_FIELD ( PerformanceOverrideInfoIntel,                                          VkStructureType :: VK_STRUCTURE_TYPE_PERFORMANCE_OVERRIDE_INFO_INTEL ),
            __C_ENG_ENUM_FIELD ( PerformanceConfigurationAcquireInfoIntel,                              VkStructureType :: VK_STRUCTURE_TYPE_PERFORMANCE_CONFIGURATION_ACQUIRE_INFO_INTEL ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PCI_BUS_INFO_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDevicePCIBusInfoProperties,                                    VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PCI_BUS_INFO_PROPERTIES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_DISPLAY_NATIVE_HDR_AVAILABLE

            __C_ENG_ENUM_FIELD ( DisplayNativeHDRSurfaceCapabilitiesAMD,                                VkStructureType :: VK_STRUCTURE_TYPE_DISPLAY_NATIVE_HDR_SURFACE_CAPABILITIES_AMD ),
            __C_ENG_ENUM_FIELD ( SwachainDisplayNativeHDRCreateInfoAMD,                                 VkStructureType :: VK_STRUCTURE_TYPE_SWAPCHAIN_DISPLAY_NATIVE_HDR_CREATE_INFO_AMD ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_IMAGEPIPE_SURFACE_AVAILABLE

            __C_ENG_ENUM_FIELD ( ImagepipeSurfaceCreateInfoGoogle,                                      VkStructureType :: VK_STRUCTURE_TYPE_IMAGEPIPE_SURFACE_CREATE_INFO_FUCHSIA ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_TERMINATE_INVOCATION_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceShaderTerminateInvocationFeatures,                       VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_TERMINATE_INVOCATION_FEATURES_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_METAL_SURFACE_AVAILABLE

            __C_ENG_ENUM_FIELD ( MetalSurfaceCreateInfo,                                                VkStructureType :: VK_STRUCTURE_TYPE_METAL_SURFACE_CREATE_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceFragmentDensityMapFeatures,                              VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_DENSITY_MAP_FEATURES_EXT ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceFragmentDensityMapProperties,                            VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_DENSITY_MAP_PROPERTIES_EXT ),
            __C_ENG_ENUM_FIELD ( RenderPassFragmentDensityMapCreateInfo,                                VkStructureType :: VK_STRUCTURE_TYPE_RENDER_PASS_FRAGMENT_DENSITY_MAP_CREATE_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceSubgroupSizeControlFeatures,                             VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBGROUP_SIZE_CONTROL_FEATURES_EXT ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceSubgroupSizeControlProperties,                           VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBGROUP_SIZE_CONTROL_PROPERTIES_EXT ),
            __C_ENG_ENUM_FIELD ( PipelineShaderStageRequiredSubgroupSizeCreateInfo,                     VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_REQUIRED_SUBGROUP_SIZE_CREATE_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceFragmentShadingRateFeatures,                             VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADING_RATE_FEATURES_KHR ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceFragmentShadingRateProperties,                           VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADING_RATE_PROPERTIES_KHR ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceFragmentShadingRate,                                     VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADING_RATE_KHR ),
            __C_ENG_ENUM_FIELD ( PipelineFragmentShadingRateStateCreateInfo,                            VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_FRAGMENT_SHADING_RATE_STATE_CREATE_INFO_KHR ),
            __C_ENG_ENUM_FIELD ( FragmentShadingRateAttachmentInfo,                                     VkStructureType :: VK_STRUCTURE_TYPE_FRAGMENT_SHADING_RATE_ATTACHMENT_INFO_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_DEVICE_COHERENT_MEMORY_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceCoherentMemoryFeaturesAMD,                               VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COHERENT_MEMORY_FEATURES_AMD ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_MEMORY_BUDGET_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceMemoryBudgetProperties,                                  VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_BUDGET_PROPERTIES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_MEMORY_PRIORITY_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceMemoryPriorityFeatures,                                  VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_PRIORITY_FEATURES_EXT ),
            __C_ENG_ENUM_FIELD ( MemoryPriorityAllocateInfo,                                            VkStructureType :: VK_STRUCTURE_TYPE_MEMORY_PRIORITY_ALLOCATE_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SURFACE_PROTECTED_CAPABILITIES_AVAILABLE

            __C_ENG_ENUM_FIELD ( SurfaceProtectedCapabilities,                                          VkStructureType :: VK_STRUCTURE_TYPE_SURFACE_PROTECTED_CAPABILITIES_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEDICATED_ALLOCATION_IMAGE_ALIASING_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceDedicatedAllocationImageAliasingFeaturesNVidia,          VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEDICATED_ALLOCATION_IMAGE_ALIASING_FEATURES_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_BUFFER_DEVICE_ADDRESS_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceBufferDeviceAddressFeaturesExt,                          VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BUFFER_DEVICE_ADDRESS_FEATURES_EXT ),
            __C_ENG_ENUM_FIELD ( BufferDeviceAddressCreateInfoExt,                                      VkStructureType :: VK_STRUCTURE_TYPE_BUFFER_DEVICE_ADDRESS_CREATE_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TOOLING_INFO_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceToolProperties,                                          VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TOOL_PROPERTIES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_FEATURES_AVAILABLE

            __C_ENG_ENUM_FIELD ( ValidationFeatures,                                                    VkStructureType :: VK_STRUCTURE_TYPE_VALIDATION_FEATURES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PRESENT_WAIT_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDevicePresentWaitFeatures,                                     VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PRESENT_WAIT_FEATURES_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COOPERATIVE_MATRIX_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceCooperativeMatrixFeaturesNVidia,                         VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COOPERATIVE_MATRIX_FEATURES_NV ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceCooperativeMatrixPropertiesNVidia,                       VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COOPERATIVE_MATRIX_PROPERTIES_NV ),
            __C_ENG_ENUM_FIELD ( CooperativeMatrixPropertiesNVidia,                                     VkStructureType :: VK_STRUCTURE_TYPE_COOPERATIVE_MATRIX_PROPERTIES_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COVERAGE_REDUCTION_MODE_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceCoverageReductionModeFeaturesNVidia,                     VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COVERAGE_REDUCTION_MODE_FEATURES_NV ),
            __C_ENG_ENUM_FIELD ( PipelineCoverageReductionStateCreateInfoNVidia,                        VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_COVERAGE_REDUCTION_STATE_CREATE_INFO_NV ),
            __C_ENG_ENUM_FIELD ( FramebufferMixedSamplesCombinationNVidia,                              VkStructureType :: VK_STRUCTURE_TYPE_FRAMEBUFFER_MIXED_SAMPLES_COMBINATION_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_SHADER_INTERLOCK_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceFragmentShaderInterlockFeatures,                         VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADER_INTERLOCK_FEATURES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_YCBCR_IMAGE_ARRAYS_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceYCBCRImageArraysFeatures,                                VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_YCBCR_IMAGE_ARRAYS_FEATURES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PROVOKING_VERTEX_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceProvokingVertexFeatures,                                 VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROVOKING_VERTEX_FEATURES_EXT ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceProvokingVertexProperties,                               VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROVOKING_VERTEX_PROPERTIES_EXT ),
            __C_ENG_ENUM_FIELD ( PipelineRasterizationProvokingVertexStateCreateInfo,                   VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_PROVOKING_VERTEX_STATE_CREATE_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FULL_SCREEN_EXCLUSIVE_AVAILABLE

            __C_ENG_ENUM_FIELD ( SurfaceFullScreenExclusiveInfo,                                        VkStructureType :: VK_STRUCTURE_TYPE_SURFACE_FULL_SCREEN_EXCLUSIVE_INFO_EXT ),
            __C_ENG_ENUM_FIELD ( SurfaceCapabilitiesFullScreenExclusive,                                VkStructureType :: VK_STRUCTURE_TYPE_SURFACE_CAPABILITIES_FULL_SCREEN_EXCLUSIVE_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_WIN32_SURFACE_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_FULL_SCREEN_EXCLUSIVE_AVAILABLE

            __C_ENG_ENUM_FIELD ( SurfaceFullScreenExclusiveWin32Info,                                   VkStructureType :: VK_STRUCTURE_TYPE_SURFACE_FULL_SCREEN_EXCLUSIVE_WIN32_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_HEADLESS_SURFACE_AVAILABLE

            __C_ENG_ENUM_FIELD ( HeadlessSurfaceCreateInfo,                                             VkStructureType :: VK_STRUCTURE_TYPE_HEADLESS_SURFACE_CREATE_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_LINE_RASTERIZATION_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceLineRasterizationFeatures,                               VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_LINE_RASTERIZATION_FEATURES_EXT ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceLineRasterizationProperties,                             VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_LINE_RASTERIZATION_PROPERTIES_EXT ),
            __C_ENG_ENUM_FIELD ( PipelineRasterizationLineStateCreateInfo,                              VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_LINE_STATE_CREATE_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_ATOMIC_FLOAT_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceShaderAtomicFloatFeatures,                               VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ATOMIC_FLOAT_FEATURES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INDEX_TYPE_UINT8_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceIndexTypeUInt8Features,                                  VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INDEX_TYPE_UINT8_FEATURES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceExtendedDynamicStateFeatures,                            VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTENDED_DYNAMIC_STATE_FEATURES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDevicePipelineExecutablePropertiesFeatures,                    VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PIPELINE_EXECUTABLE_PROPERTIES_FEATURES_KHR ),
            __C_ENG_ENUM_FIELD ( PipelineInfo,                                                          VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_INFO_KHR ),
            __C_ENG_ENUM_FIELD ( PipelineExecutableProperties,                                          VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_EXECUTABLE_PROPERTIES_KHR ),
            __C_ENG_ENUM_FIELD ( PipelineExecutableInfo,                                                VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_EXECUTABLE_INFO_KHR ),
            __C_ENG_ENUM_FIELD ( PipelineExecutableStatistic,                                           VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_EXECUTABLE_STATISTIC_KHR ),
            __C_ENG_ENUM_FIELD ( PipelineExecutableInternalRepresentation,                              VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_EXECUTABLE_INTERNAL_REPRESENTATION_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_ATOMIC_FLOAT_2_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceShaderAtomicFloat2Features,                              VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ATOMIC_FLOAT_2_FEATURES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_DEMOTE_TO_HELPER_INVOCATION_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceShaderDemoteToHelperInvocationFeatures,                  VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_DEMOTE_TO_HELPER_INVOCATION_FEATURES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceDeviceGeneratedCommandsPropertiesNVidia,                 VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEVICE_GENERATED_COMMANDS_FEATURES_NV ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceDeviceGeneratedCommandsFeaturesNVidia,                   VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEVICE_GENERATED_COMMANDS_PROPERTIES_NV ),
            __C_ENG_ENUM_FIELD ( GraphicsShaderGroupCreateInfoNVidia,                                   VkStructureType :: VK_STRUCTURE_TYPE_GRAPHICS_SHADER_GROUP_CREATE_INFO_NV ),
            __C_ENG_ENUM_FIELD ( GraphicsPipelineShaderGroupsCreateInfoNVidia,                          VkStructureType :: VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_SHADER_GROUPS_CREATE_INFO_NV ),
            __C_ENG_ENUM_FIELD ( IndirectCommandsLayoutTokenNVidia,                                     VkStructureType :: VK_STRUCTURE_TYPE_INDIRECT_COMMANDS_LAYOUT_TOKEN_NV ),
            __C_ENG_ENUM_FIELD ( IndirectCommandsLayoutCreateInfoNVidia,                                VkStructureType :: VK_STRUCTURE_TYPE_INDIRECT_COMMANDS_LAYOUT_CREATE_INFO_NV ),
            __C_ENG_ENUM_FIELD ( GeneratedCommandsInfoNVidia,                                           VkStructureType :: VK_STRUCTURE_TYPE_GENERATED_COMMANDS_INFO_NV ),
            __C_ENG_ENUM_FIELD ( GeneratedCommandsMemoryRequirementsInfoNVidia,                         VkStructureType :: VK_STRUCTURE_TYPE_GENERATED_COMMANDS_MEMORY_REQUIREMENTS_INFO_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_INHERITED_VIEWPORT_SCISSOR_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceInheritedViewportScissorFeaturesNVidia,                  VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INHERITED_VIEWPORT_SCISSOR_FEATURES_NV ),
            __C_ENG_ENUM_FIELD ( CommandBufferInheritanceViewportScissorInfoNVidia,                     VkStructureType :: VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_VIEWPORT_SCISSOR_INFO_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_INTEGER_DOT_PRODUCT_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceShaderIntegerDotProductFeatures,                         VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_INTEGER_DOT_PRODUCT_FEATURES_KHR ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceShaderIntegerDotProductProperties,                       VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_INTEGER_DOT_PRODUCT_PROPERTIES_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXEL_BUFFER_ALIGNMENT_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceTexelBufferAlignmentFeatures,                            VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TEXEL_BUFFER_ALIGNMENT_FEATURES_EXT ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceTexelBufferAlignmentProperties,                          VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TEXEL_BUFFER_ALIGNMENT_PROPERTIES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_RENDER_PASS_TRANSFORM_AVAILABLE

            __C_ENG_ENUM_FIELD ( CommandBufferInheritanceRenderPassTransformInfoQualcomm,               VkStructureType :: VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_RENDER_PASS_TRANSFORM_INFO_QCOM ),
            __C_ENG_ENUM_FIELD ( RenderPassTransformBeginInfoQualcomm,                                  VkStructureType :: VK_STRUCTURE_TYPE_RENDER_PASS_TRANSFORM_BEGIN_INFO_QCOM ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEVICE_MEMORY_REPORT_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceDeviceMemoryReportFeatures,                              VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEVICE_MEMORY_REPORT_FEATURES_EXT ),
            __C_ENG_ENUM_FIELD ( DeviceDeviceMemoryReportCreateInfo,                                    VkStructureType :: VK_STRUCTURE_TYPE_DEVICE_DEVICE_MEMORY_REPORT_CREATE_INFO_EXT ),
            __C_ENG_ENUM_FIELD ( DeviceMemoryReportCallbackData,                                        VkStructureType :: VK_STRUCTURE_TYPE_DEVICE_MEMORY_REPORT_CALLBACK_DATA_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_ROBUSTNESS_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceRobustnessFeatures,                                      VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ROBUSTNESS_2_FEATURES_EXT ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceRobustnessProperties,                                    VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ROBUSTNESS_2_PROPERTIES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CUSTOM_BORDER_COLOR_AVAILABLE

            __C_ENG_ENUM_FIELD ( SamplerCustomBorderColorCreateInfo,                                    VkStructureType :: VK_STRUCTURE_TYPE_SAMPLER_CUSTOM_BORDER_COLOR_CREATE_INFO_EXT ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceCustomBorderColorFeatures,                               VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CUSTOM_BORDER_COLOR_FEATURES_EXT ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceCustomBorderColorProperties,                             VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CUSTOM_BORDER_COLOR_PROPERTIES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_LIBRARY_AVAILABLE

            __C_ENG_ENUM_FIELD ( PipelineLibraryCreateInfo,                                             VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_LIBRARY_CREATE_INFO_KHR ),

#endif

#if _C_ENG_VULKAN_API_EXTENSION_KHRONOS_PRESENT_ID_AVAILABLE

            __C_ENG_ENUM_FIELD ( PresentID,                                                             VkStructureType :: VK_STRUCTURE_TYPE_PRESENT_ID_KHR ),
            __C_ENG_ENUM_FIELD ( PhysicalDevicePresentIDFeatures,                                       VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PRESENT_ID_FEATURES_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PRIVATE_DATA_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDevicePrivateDataFeatures,                                     VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PRIVATE_DATA_FEATURES_EXT ),
            __C_ENG_ENUM_FIELD ( DevicePrivateDataCreateInfo,                                           VkStructureType :: VK_STRUCTURE_TYPE_DEVICE_PRIVATE_DATA_CREATE_INFO_EXT ),
            __C_ENG_ENUM_FIELD ( PrivateDataSlotCreateInfo,                                             VkStructureType :: VK_STRUCTURE_TYPE_PRIVATE_DATA_SLOT_CREATE_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_CACHE_CONTROL_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDevicePipelineCreationCacheControlFeatures,                    VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PIPELINE_CREATION_CACHE_CONTROL_FEATURES_EXT ),

#endif

#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_ENCODE_QUEUE_AVAILABLE

            __C_ENG_ENUM_FIELD ( VideoEncodeInfo,                                                       VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_ENCODE_INFO_KHR ),
            __C_ENG_ENUM_FIELD ( VideoEncodeRateControlInfo,                                            VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_ENCODE_RATE_CONTROL_INFO_KHR ),
            __C_ENG_ENUM_FIELD ( VideoEncodeRateControlLayerInfo,                                       VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_ENCODE_RATE_CONTROL_LAYER_INFO_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTICS_CONFIG_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceDiagnosticsConfigFeaturesNVidia,                         VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DIAGNOSTICS_CONFIG_FEATURES_NV ),
            __C_ENG_ENUM_FIELD ( DeviceDiagnosticsConfigCreateInfoNVidia,                               VkStructureType :: VK_STRUCTURE_TYPE_DEVICE_DIAGNOSTICS_CONFIG_CREATE_INFO_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE

            __C_ENG_ENUM_FIELD ( MemoryBarrier2,                                                        VkStructureType :: VK_STRUCTURE_TYPE_MEMORY_BARRIER_2_KHR ),
            __C_ENG_ENUM_FIELD ( BufferMemoryBarrier2,                                                  VkStructureType :: VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER_2_KHR ),
            __C_ENG_ENUM_FIELD ( ImageMemoryBarrier2,                                                   VkStructureType :: VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2_KHR ),
            __C_ENG_ENUM_FIELD ( DependencryInfo,                                                       VkStructureType :: VK_STRUCTURE_TYPE_DEPENDENCY_INFO_KHR ),
            __C_ENG_ENUM_FIELD ( SubmitInfo2,                                                           VkStructureType :: VK_STRUCTURE_TYPE_SUBMIT_INFO_2_KHR ),
            __C_ENG_ENUM_FIELD ( SemaphoreSubmitInfo,                                                   VkStructureType :: VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO_KHR ),
            __C_ENG_ENUM_FIELD ( CommandBufferSubmitInfo,                                               VkStructureType :: VK_STRUCTURE_TYPE_COMMAND_BUFFER_SUBMIT_INFO_KHR ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceSynchronizationFeatures,                                 VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SYNCHRONIZATION_2_FEATURES_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTIC_CHECKPOINTS_AVAILABLE

            __C_ENG_ENUM_FIELD ( QueueFamilyCheckpointProperties2NVidia,                                VkStructureType :: VK_STRUCTURE_TYPE_QUEUE_FAMILY_CHECKPOINT_PROPERTIES_2_NV ),
            __C_ENG_ENUM_FIELD ( CheckpointData2NVidia,                                                 VkStructureType :: VK_STRUCTURE_TYPE_CHECKPOINT_DATA_2_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_SUBGROUP_UNIFORM_CONTROL_FLOW_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceShaderSubgroupUniformControlFlowFeatures,                VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_SUBGROUP_UNIFORM_CONTROL_FLOW_FEATURES_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ZERO_INITIALIZE_WORKGROUP_MEMORY_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceZeroInitializeWorkgroupMemoryFeatures,                   VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ZERO_INITIALIZE_WORKGROUP_MEMORY_FEATURES_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADING_RATE_ENUMS_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceFragmentShadingRateEnumsFeaturesNVidia,                  VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADING_RATE_ENUMS_FEATURES_NV ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceFragmentShadingRateEnumsPropertiesNVidia,                VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADING_RATE_ENUMS_PROPERTIES_NV ),
            __C_ENG_ENUM_FIELD ( PipelineFragmentShadingRateEnumStateCreateInfoNVidia,                  VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_FRAGMENT_SHADING_RATE_ENUM_STATE_CREATE_INFO_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_MOTION_BLUR_AVAILABLE

            __C_ENG_ENUM_FIELD ( AccelerationStructureGeometryMotionTrianglesDataNVidia,                VkStructureType :: VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_MOTION_TRIANGLES_DATA_NV ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceRayTracingMotionBlurFeaturesNVidia,                      VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_MOTION_BLUR_FEATURES_NV ),
            __C_ENG_ENUM_FIELD ( AccelerationStructureMotionInfoNVidia,                                 VkStructureType :: VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_MOTION_INFO_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_YCBCR_2_PLANE_444_FORMATS_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceYCBCR2Plane444FormatsFeatures,                           VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_YCBCR_2_PLANE_444_FORMATS_FEATURES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_2_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceFragmentDensityMap2Features,                             VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_DENSITY_MAP_2_FEATURES_EXT ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceFragmentDensityMap2Properties,                           VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_DENSITY_MAP_2_PROPERTIES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_ROTATED_COPY_COMMANDS_AVAILABLE

            __C_ENG_ENUM_FIELD ( CopyCommandTransformInfoQualcomm,                                      VkStructureType :: VK_STRUCTURE_TYPE_COPY_COMMAND_TRANSFORM_INFO_QCOM ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_ROBUSTNESS_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceImageRobustnessFeatures,                                 VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_ROBUSTNESS_FEATURES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_WORKGROUP_MEMORY_EXPLICIT_LAYOUT_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceWorkgroupMemoryExplicitLayoutFeatures,                   VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_WORKGROUP_MEMORY_EXPLICIT_LAYOUT_FEATURES_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_COPY_COMMANDS_AVAILABLE

            __C_ENG_ENUM_FIELD ( CopyBufferInfo,                                                        VkStructureType :: VK_STRUCTURE_TYPE_COPY_BUFFER_INFO_2_KHR ),
            __C_ENG_ENUM_FIELD ( CopyImageInfo,                                                         VkStructureType :: VK_STRUCTURE_TYPE_COPY_IMAGE_INFO_2_KHR ),
            __C_ENG_ENUM_FIELD ( CopyBufferToImageInfo,                                                 VkStructureType :: VK_STRUCTURE_TYPE_COPY_BUFFER_TO_IMAGE_INFO_2_KHR ),
            __C_ENG_ENUM_FIELD ( CopyImageToBufferInfo,                                                 VkStructureType :: VK_STRUCTURE_TYPE_COPY_IMAGE_TO_BUFFER_INFO_2_KHR ),
            __C_ENG_ENUM_FIELD ( BlitImageInfo,                                                         VkStructureType :: VK_STRUCTURE_TYPE_BLIT_IMAGE_INFO_2_KHR ),
            __C_ENG_ENUM_FIELD ( ResolveImageInfo,                                                      VkStructureType :: VK_STRUCTURE_TYPE_RESOLVE_IMAGE_INFO_2_KHR ),
            __C_ENG_ENUM_FIELD ( BufferCopy,                                                            VkStructureType :: VK_STRUCTURE_TYPE_BUFFER_COPY_2_KHR ),
            __C_ENG_ENUM_FIELD ( ImageCopy,                                                             VkStructureType :: VK_STRUCTURE_TYPE_IMAGE_COPY_2_KHR ),
            __C_ENG_ENUM_FIELD ( ImageBlit,                                                             VkStructureType :: VK_STRUCTURE_TYPE_IMAGE_BLIT_2_KHR ),
            __C_ENG_ENUM_FIELD ( BufferImageCopy,                                                       VkStructureType :: VK_STRUCTURE_TYPE_BUFFER_IMAGE_COPY_2_KHR ),
            __C_ENG_ENUM_FIELD ( ImageResolve,                                                          VkStructureType :: VK_STRUCTURE_TYPE_IMAGE_RESOLVE_2_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_4444_FORMATS_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDevice4444FormatsFeatures,                                     VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_4444_FORMATS_FEATURES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_ARM_RASTERIZATION_ORDER_ATTACHMENT_ACCESS_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceRasterizationOrderAttachmentAccessFeaturesARM,           VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RASTERIZATION_ORDER_ATTACHMENT_ACCESS_FEATURES_ARM ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_RGBA_10_X_6_FORMATS_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceRGBA10x6FormatsFeatures,                                 VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RGBA10X6_FORMATS_FEATURES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DIRECTFB_SURFACE_AVAILABLE

            __C_ENG_ENUM_FIELD ( DirectfbSurfaceCreateInfo,                                             VkStructureType :: VK_STRUCTURE_TYPE_DIRECTFB_SURFACE_CREATE_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALVE_MUTABLE_DESCRIPTOR_TYPE_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceMutableDescriptorTypeFeaturesValve,                      VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MUTABLE_DESCRIPTOR_TYPE_FEATURES_VALVE ),
            __C_ENG_ENUM_FIELD ( MutableDescriptorTypeCreateInfoValve,                                  VkStructureType :: VK_STRUCTURE_TYPE_MUTABLE_DESCRIPTOR_TYPE_CREATE_INFO_VALVE ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_INPUT_DYNAMIC_STATE_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceVertexInputDynamicStateFeatures,                         VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VERTEX_INPUT_DYNAMIC_STATE_FEATURES_EXT ),
            __C_ENG_ENUM_FIELD ( VertexInputBindingDescription,                                         VkStructureType :: VK_STRUCTURE_TYPE_VERTEX_INPUT_BINDING_DESCRIPTION_2_EXT ),
            __C_ENG_ENUM_FIELD ( VertexInputAttributeDescription,                                       VkStructureType :: VK_STRUCTURE_TYPE_VERTEX_INPUT_ATTRIBUTE_DESCRIPTION_2_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PHYSICAL_DEVICE_DRM_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceDRMProperties,                                           VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DRM_PROPERTIES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_CONTROL_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceDepthClipControlFeatures,                                VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEPTH_CLIP_CONTROL_FEATURES_EXT ),
            __C_ENG_ENUM_FIELD ( PipelineViewportDepthClipControlCreateInfo,                            VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_DEPTH_CLIP_CONTROL_CREATE_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PRIMITIVE_TOPOLOGY_LIST_RESTART_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDevicePrimitiveTopologyListRestartFeatures,                    VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PRIMITIVE_TOPOLOGY_LIST_RESTART_FEATURES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FORMAT_FEATURE_FLAGS_AVAILABLE

            __C_ENG_ENUM_FIELD ( FormatProperties3,                                                     VkStructureType :: VK_STRUCTURE_TYPE_FORMAT_PROPERTIES_3_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_EXTERNAL_MEMORY_AVAILABLE

            __C_ENG_ENUM_FIELD ( ImportMemoryZirconHandleInfoGoogle,                                    VkStructureType :: VK_STRUCTURE_TYPE_IMPORT_MEMORY_ZIRCON_HANDLE_INFO_FUCHSIA ),
            __C_ENG_ENUM_FIELD ( MemoryZirconHandlePropertiesGoogle,                                    VkStructureType :: VK_STRUCTURE_TYPE_MEMORY_ZIRCON_HANDLE_PROPERTIES_FUCHSIA ),
            __C_ENG_ENUM_FIELD ( GetZirconHandleInfo,                                                   VkStructureType :: VK_STRUCTURE_TYPE_MEMORY_GET_ZIRCON_HANDLE_INFO_FUCHSIA ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_EXTERNAL_SEMAPHORE_AVAILABLE

            __C_ENG_ENUM_FIELD ( ImportSemaphoreZirconHandleInfoGoogle,                                 VkStructureType :: VK_STRUCTURE_TYPE_IMPORT_SEMAPHORE_ZIRCON_HANDLE_INFO_FUCHSIA ),
            __C_ENG_ENUM_FIELD ( GetZirconHandleInfoGoogle,                                             VkStructureType :: VK_STRUCTURE_TYPE_SEMAPHORE_GET_ZIRCON_HANDLE_INFO_FUCHSIA ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_BUFFER_COLLECTION_AVAILABLE

            __C_ENG_ENUM_FIELD ( BufferCollectionCreateInfoGoogle,                                      VkStructureType :: VK_STRUCTURE_TYPE_BUFFER_COLLECTION_CREATE_INFO_FUCHSIA ),
            __C_ENG_ENUM_FIELD ( ImportMemoryBufferCollectionGoogle,                                    VkStructureType :: VK_STRUCTURE_TYPE_IMPORT_MEMORY_BUFFER_COLLECTION_FUCHSIA ),
            __C_ENG_ENUM_FIELD ( BufferCollectionImageCreateInfoGoogle,                                 VkStructureType :: VK_STRUCTURE_TYPE_BUFFER_COLLECTION_IMAGE_CREATE_INFO_FUCHSIA ),
            __C_ENG_ENUM_FIELD ( BufferCollectionPropertiesGoogle,                                      VkStructureType :: VK_STRUCTURE_TYPE_BUFFER_COLLECTION_PROPERTIES_FUCHSIA ),
            __C_ENG_ENUM_FIELD ( BufferConstraintsInfoGoogle,                                           VkStructureType :: VK_STRUCTURE_TYPE_BUFFER_CONSTRAINTS_INFO_FUCHSIA ),
            __C_ENG_ENUM_FIELD ( BufferCollectionBufferCreateInfoGoogle,                                VkStructureType :: VK_STRUCTURE_TYPE_BUFFER_COLLECTION_BUFFER_CREATE_INFO_FUCHSIA ),
            __C_ENG_ENUM_FIELD ( ImageConstraintsInfoGoogle,                                            VkStructureType :: VK_STRUCTURE_TYPE_IMAGE_CONSTRAINTS_INFO_FUCHSIA ),
            __C_ENG_ENUM_FIELD ( ImageFormatConstraintsInfoGoogle,                                      VkStructureType :: VK_STRUCTURE_TYPE_IMAGE_FORMAT_CONSTRAINTS_INFO_FUCHSIA ),
            __C_ENG_ENUM_FIELD ( SystemColorSpaceGoogle,                                                VkStructureType :: VK_STRUCTURE_TYPE_SYSMEM_COLOR_SPACE_FUCHSIA ),
            __C_ENG_ENUM_FIELD ( BufferCollectionConstraintsInfoGoogle,                                 VkStructureType :: VK_STRUCTURE_TYPE_BUFFER_COLLECTION_CONSTRAINTS_INFO_FUCHSIA ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE

            __C_ENG_ENUM_FIELD ( SubpassShadingPipelineCreateInfoHuawei,                                VkStructureType :: VK_STRUCTURE_TYPE_SUBPASS_SHADING_PIPELINE_CREATE_INFO_HUAWEI ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceSubpassShadingFeaturesHuawei,                            VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBPASS_SHADING_FEATURES_HUAWEI ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceSubpassShadingPropertiesHuawei,                          VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBPASS_SHADING_PROPERTIES_HUAWEI ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_INVOCATION_MASK_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceInvocationMaskFeaturesHuawei,                            VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INVOCATION_MASK_FEATURES_HUAWEI ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_RDMA_AVAILABLE

            __C_ENG_ENUM_FIELD ( MemoryGetRemoteAddressInfoNVidia,                                      VkStructureType :: VK_STRUCTURE_TYPE_MEMORY_GET_REMOTE_ADDRESS_INFO_NV ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceExternalMemoryRDMAFeaturesNVidia,                        VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_MEMORY_RDMA_FEATURES_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_2_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceExtendedDynamicState2Features,                           VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTENDED_DYNAMIC_STATE_2_FEATURES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_BLACKBERRY_QNX_SCREEN_SURFACE_AVAILABLE

            __C_ENG_ENUM_FIELD ( QnxScreenSurfaceCreateInfoBlackberry,                                  VkStructureType :: VK_STRUCTURE_TYPE_SCREEN_SURFACE_CREATE_INFO_QNX ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_COLOR_WRITE_ENABLE_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceColorWriteEnableFeatures,                                VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COLOR_WRITE_ENABLE_FEATURES_EXT ),
            __C_ENG_ENUM_FIELD ( PipelineColorWriteCreateInfo,                                          VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_COLOR_WRITE_CREATE_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GLOBAL_PRIORITY_QUERY_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceGlobalPriorityQueryFeatures,                             VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_GLOBAL_PRIORITY_QUERY_FEATURES_EXT ),
            __C_ENG_ENUM_FIELD ( QueueFamilyGlobalPriorityProperties,                                   VkStructureType :: VK_STRUCTURE_TYPE_QUEUE_FAMILY_GLOBAL_PRIORITY_PROPERTIES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_VIEW_MIN_LOD_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceImageViewMinLODFeatures,                                 VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_VIEW_MIN_LOD_FEATURES_EXT ),
            __C_ENG_ENUM_FIELD ( ImageViewMinLODCreateInfo,                                             VkStructureType :: VK_STRUCTURE_TYPE_IMAGE_VIEW_MIN_LOD_CREATE_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_MULTI_DRAW_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceMultiDrawFeatures,                                       VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTI_DRAW_FEATURES_EXT ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceMultiDrawProperties,                                     VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTI_DRAW_PROPERTIES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_BORDER_COLOR_SWIZZLE_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceBorderColorSwizzleFeatures,                              VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BORDER_COLOR_SWIZZLE_FEATURES_EXT ),
            __C_ENG_ENUM_FIELD ( SamplerBorderColorComponentMappingCreateInfo,                          VkStructureType :: VK_STRUCTURE_TYPE_SAMPLER_BORDER_COLOR_COMPONENT_MAPPING_CREATE_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PAGEABLE_DEVICE_LOCAL_MEMORY_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDevicePageableDeviceLocalMemoryFeatures,                       VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PAGEABLE_DEVICE_LOCAL_MEMORY_FEATURES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_4_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceMaintenance4Features,                                    VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_4_FEATURES_KHR ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceMaintenance4Properties,                                  VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_4_PROPERTIES_KHR ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceBufferMemoryRequirements,                                VkStructureType :: VK_STRUCTURE_TYPE_DEVICE_BUFFER_MEMORY_REQUIREMENTS_KHR ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceImageMemoryRequirements,                                 VkStructureType :: VK_STRUCTURE_TYPE_DEVICE_IMAGE_MEMORY_REQUIREMENTS_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_FRAGMENT_DENSITY_MAP_OFFSET_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceFragmentDensityMapOffsetFeaturesQualcomm,                VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_DENSITY_MAP_OFFSET_FEATURES_QCOM ),
            __C_ENG_ENUM_FIELD ( PhysicalDeviceFragmentDensityMapOffsetPropertiesQualcomm,              VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_DENSITY_MAP_OFFSET_PROPERTIES_QCOM ),
            __C_ENG_ENUM_FIELD ( SubpassFragmentDensityMapOffsetEndInfoQualcomm,                        VkStructureType :: VK_STRUCTURE_TYPE_SUBPASS_FRAGMENT_DENSITY_MAP_OFFSET_END_INFO_QCOM ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_LINEAR_COLOR_ATTACHMENT_AVAILABLE

            __C_ENG_ENUM_FIELD ( PhysicalDeviceLinearColorAttachmentFeaturesNVidia,                     VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_LINEAR_COLOR_ATTACHMENT_FEATURES_NV ),

#endif

            __C_ENG_ENUM_FIELD ( Unknown,                                                               cds :: limits :: S32_MAX )

        };

#pragma pop_macro("__C_ENG_OBJECT_TYPE")
#pragma pop_macro("__C_ENG_OBJECT_NAME")


        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( Result ) ) noexcept -> cds :: StringLiteral;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( StructureType ) ) noexcept -> cds :: StringLiteral;


        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( Offset2D ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( Offset3D ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( Extent2D ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( Extent3D ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( Rect ) const & ) noexcept -> cds :: String;

    }
}

#endif //__C_ENG_VULKANCORE_HPP
