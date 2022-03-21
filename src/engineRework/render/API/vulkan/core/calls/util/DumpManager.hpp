//
// Created by loghin on 16.03.2022.
//

#ifndef __C_ENG_DUMP_MANAGER_HPP__
#define __C_ENG_DUMP_MANAGER_HPP__

#include <calls/VulkanAPICallsTypes.hpp>

#define C_ENG_MAP_START HEADER
#include <ObjectMapping.hpp>

#define __C_ENG_DUMP_MANAGER_SET_TYPE(_of, _what) \
    template <>                                   \
    constexpr auto parameterTypeOfParameter < _of > ( _of const & ) noexcept -> ParameterType {  \
        return ParameterType :: _what;                                                                  \
    }

template < typename T >
constexpr auto parameterTypeOfParameter ( T const & parameter ) noexcept -> ParameterType {
    return ParameterType :: Unknown;
}

__C_ENG_DUMP_MANAGER_SET_TYPE( bool *,                  BoolPtr )
__C_ENG_DUMP_MANAGER_SET_TYPE( float,                   Float )
__C_ENG_DUMP_MANAGER_SET_TYPE( cds :: uint32 *,         UInt32Ptr )
__C_ENG_DUMP_MANAGER_SET_TYPE( cds :: uint32,           UInt32 )
__C_ENG_DUMP_MANAGER_SET_TYPE( cds :: uint64 *,         UInt64Ptr )
__C_ENG_DUMP_MANAGER_SET_TYPE( cds :: uint64,           UInt64 )
__C_ENG_DUMP_MANAGER_SET_TYPE( cds :: StringLiteral,    StringLiteral )

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( InstanceCreateInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ApplicationInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( DeviceQueueCreateInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( DeviceCreateInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( SubmitInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( MemoryAllocateInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( MappedMemoryRange ) const *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( BindSparseInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( FenceCreateInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( SemaphoreCreateInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( EventCreateInfo ) const *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( QueryPoolCreateInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( BufferCreateInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( BufferViewCreateInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ImageCreateInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ImageViewCreateInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ShaderModuleCreateInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PipelineCacheCreateInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PipelineShaderStageCreateInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PipelineVertexInputStateCreateInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PipelineInputAssemblyStateCreateInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PipelineTessellationStateCreateInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PipelineViewportStateCreateInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PipelineRasterizationStateCreateInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PipelineMultisampleStateCreateInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PipelineDepthStencilStateCreateInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PipelineColorBlendStateCreateInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PipelineDynamicStateCreateInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( GraphicsPipelineCreateInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ComputePipelineCreateInfo ) const *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PipelineLayoutCreateInfo ) const *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( SamplerCreateInfo ) const *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( DescriptorSetLayoutCreateInfo ) const *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( DescriptorPoolCreateInfo ) const *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( DescriptorSetAllocateInfo ) const *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( WriteDescriptorSet ) const *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( CopyDescriptorSet ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( FrameBufferCreateInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( RenderPassCreateInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( CommandPoolCreateInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( CommandBufferAllocateInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( CommandBufferInheritanceInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( CommandBufferBeginInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( RenderPassBeginInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( BufferMemoryBarrier ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ImageMemoryBarrier ) const *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( MemoryBarrier ) const *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( LoaderInstanceCreateInfo ) const *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( LoaderDeviceCreateInfo ) const *, StructurePtr )

__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( InstanceCreateInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ApplicationInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( DeviceQueueCreateInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( DeviceCreateInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( SubmitInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( MemoryAllocateInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( MappedMemoryRange ) *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( BindSparseInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( FenceCreateInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( SemaphoreCreateInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( EventCreateInfo ) *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( QueryPoolCreateInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( BufferCreateInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( BufferViewCreateInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ImageCreateInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ImageViewCreateInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ShaderModuleCreateInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PipelineCacheCreateInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PipelineShaderStageCreateInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PipelineVertexInputStateCreateInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PipelineInputAssemblyStateCreateInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PipelineTessellationStateCreateInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PipelineViewportStateCreateInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PipelineRasterizationStateCreateInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PipelineMultisampleStateCreateInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PipelineDepthStencilStateCreateInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PipelineColorBlendStateCreateInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PipelineDynamicStateCreateInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( GraphicsPipelineCreateInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ComputePipelineCreateInfo ) *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PipelineLayoutCreateInfo ) *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( SamplerCreateInfo ) *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( DescriptorSetLayoutCreateInfo ) *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( DescriptorPoolCreateInfo ) *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( DescriptorSetAllocateInfo ) *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( WriteDescriptorSet ) *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( CopyDescriptorSet ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( FrameBufferCreateInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( RenderPassCreateInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( CommandPoolCreateInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( CommandBufferAllocateInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( CommandBufferInheritanceInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( CommandBufferBeginInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( RenderPassBeginInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( BufferMemoryBarrier ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ImageMemoryBarrier ) *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( MemoryBarrier ) *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( LoaderInstanceCreateInfo ) *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( LoaderDeviceCreateInfo ) *, StructurePtr )
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceSubgroupProperties ) const *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( BindBufferMemoryInfo ) const *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( BindImageMemoryInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDevice16BitStorageFeatures ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( MemoryDedicatedRequirements ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( MemoryDedicatedAllocateInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( MemoryAllocateFlagsInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( DeviceGroupRenderPassBeginInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( DeviceGroupCommandBufferBeginInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( DeviceGroupSubmitInfo ) const *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( DeviceGroupBindSparseInfo ) const *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( BindBufferMemoryDeviceGroupInfo ) const *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( BindImageMemoryDeviceGroupInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceGroupProperties ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( DeviceGroupDeviceCreateInfo ) const *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( BufferMemoryRequirementsInfo ) const *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ImageMemoryRequirementsInfo ) const *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ImageSparseMemoryRequirementsInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( MemoryRequirements ) const *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( SparseImageMemoryRequirements ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceExtendedFeatures ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceExtendedProperties ) const *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( FormatProperties ) const *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ImageFormatProperties ) const *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceImageFormatInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( QueueFamilyExtendedProperties ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceMemoryProperties ) const *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( SparseImageFormatProperties ) const *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceSparseImageFormatInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDevicePointClippingProperties ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( RenderPassInputAttachmentAspectCreateInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ImageViewUsageCreateInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PipelineTessellationDomainOriginStateCreateInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( RenderPassMultiviewCreateInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceMultiviewFeatures ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceMultiviewProperties ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceVariablePointersFeatures ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ProtectedSubmitInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceProtectedMemoryFeatures ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceProtectedMemoryProperties ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( DeviceQueueInfo ) const *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( SamplerYCBCRConversionCreateInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( SamplerYCBCRConversionInfo ) const *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( BindImagePlaneMemoryInfo ) const *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ImagePlaneMemoryRequirementsInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceSamplerYCBCRConversionFeatures ) const *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( SamplerYCBCRConversionImageFormatProperties ) const *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( DescriptorUpdateTemplateCreateInfo ) const *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceExternalImageFormatInfo ) const *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ExternalImageFormatProperties ) const *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceExternalBufferInfo ) const *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ExternalBufferProperties ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceIDProperties ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ExternalMemoryBufferCreateInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ExternalMemoryImageCreateInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ExportMemoryAllocateInfo ) const *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceExternalFenceInfo ) const *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ExternalFenceProperties ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ExportFenceCreateInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ExportSemaphoreCreateInfo ) const *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceExternalSemaphoreInfo ) const *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ExternalSemaphoreProperties ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceMaintenanceProperties ) const *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( DescriptorSetLayoutSupport ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceShaderDrawParametersFeatures ) const *, StructurePtr )

__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceSubgroupProperties ) *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( BindBufferMemoryInfo ) *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( BindImageMemoryInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDevice16BitStorageFeatures ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( MemoryDedicatedRequirements ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( MemoryDedicatedAllocateInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( MemoryAllocateFlagsInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( DeviceGroupRenderPassBeginInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( DeviceGroupCommandBufferBeginInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( DeviceGroupSubmitInfo ) *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( DeviceGroupBindSparseInfo ) *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( BindBufferMemoryDeviceGroupInfo ) *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( BindImageMemoryDeviceGroupInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceGroupProperties ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( DeviceGroupDeviceCreateInfo ) *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( BufferMemoryRequirementsInfo ) *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ImageMemoryRequirementsInfo ) *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ImageSparseMemoryRequirementsInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( MemoryRequirements ) *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( SparseImageMemoryRequirements ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceExtendedFeatures ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceExtendedProperties ) *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( FormatProperties ) *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ImageFormatProperties ) *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceImageFormatInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( QueueFamilyProperties ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceMemoryProperties ) *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( SparseImageFormatProperties ) *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceSparseImageFormatInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDevicePointClippingProperties ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( RenderPassInputAttachmentAspectCreateInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ImageViewUsageCreateInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PipelineTessellationDomainOriginStateCreateInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( RenderPassMultiviewCreateInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceMultiviewFeatures ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceMultiviewProperties ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceVariablePointersFeatures ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ProtectedSubmitInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceProtectedMemoryFeatures ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceProtectedMemoryProperties ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( DeviceQueueInfo ) *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( SamplerYCBCRConversionCreateInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( SamplerYCBCRConversionInfo ) *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( BindImagePlaneMemoryInfo ) *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ImagePlaneMemoryRequirementsInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceSamplerYCBCRConversionFeatures ) *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( SamplerYCBCRConversionImageFormatProperties ) *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( DescriptorUpdateTemplateCreateInfo ) *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceExternalImageFormatInfo ) *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ExternalImageFormatProperties ) *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceExternalBufferInfo ) *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ExternalBufferProperties ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceIDProperties ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ExternalMemoryBufferCreateInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ExternalMemoryImageCreateInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ExportMemoryAllocateInfo ) *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceExternalFenceInfo ) *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ExternalFenceProperties ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ExportFenceCreateInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ExportSemaphoreCreateInfo ) *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceExternalSemaphoreInfo ) *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ExternalSemaphoreProperties ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceMaintenanceProperties ) *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( DescriptorSetLayoutSupport ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceShaderDrawParametersFeatures ) *, StructurePtr )
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceVulkan11Features ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceVulkan11Properties ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceVulkan12Features ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceVulkan12Properties ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ImageFormatListCreateInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( AttachmentDescription ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( AttachmentReference ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( SubpassDescription ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( SubpassDependency ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( RenderPassCreateInfo2 ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( SubpassBeginInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( SubpassEndInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDevice8BitStorageFeatures ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceDriverProperties ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceShaderAtomicInt64Features ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceShaderFloat16Int8Features ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceFloatControlsProperties ) const *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( DescriptorSetLayoutBindingFlagsCreateInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceDescriptorIndexingFeatures ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceDescriptorIndexingProperties ) const *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( DescriptorSetVariableDescriptorCountAllocateInfo ) const *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( DescriptorSetVariableDescriptorCountLayoutSupport ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceDepthStencilResolveProperties ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( SubpassDescriptionDepthStencilResolve ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceScalarBlockLayoutFeatures ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ImageStencilUsageCreateInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceSamplerFilterMinmaxProperties ) const *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( SamplerReductionModeCreateInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceVulkanMemoryModelFeatures ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceImagelessFrameBufferFeatures ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( FrameBufferAttachmentsCreateInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( FrameBufferAttachmentImageInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( RenderPassAttachmentBeginInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceUniformBufferStandardLayoutFeatures ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceShaderSubgroupExtendedTypesFeatures ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceSeparateDepthStencilLayoutsFeatures ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( AttachmentReferenceStencilLayout ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( AttachmentDescriptionStencilLayout ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceHostQueryResetFeatures ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceTimelineSemaphoreFeatures ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceTimelineSemaphoreProperties ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( SemaphoreTypeCreateInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( TimelineSemaphoreSubmitInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( SemaphoreWaitInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( SemaphoreSignalInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceBufferDeviceAddressFeatures ) const *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( BufferDeviceAddressInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( BufferOpaqueCaptureAddressCreateInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( MemoryOpaqueCaptureAddressAllocateInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( DeviceMemoryOpaqueCaptureAddressInfo ) const *, StructurePtr )

__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceVulkan11Features ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceVulkan11Properties ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceVulkan12Features ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceVulkan12Properties ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ImageFormatListCreateInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( AttachmentDescription ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( AttachmentReference ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( SubpassDescription ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( SubpassDependency ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( RenderPassCreateInfo2 ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( SubpassBeginInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( SubpassEndInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDevice8BitStorageFeatures ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceDriverProperties ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceShaderAtomicInt64Features ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceShaderFloat16Int8Features ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceFloatControlsProperties ) *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( DescriptorSetLayoutBindingFlagsCreateInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceDescriptorIndexingFeatures ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceDescriptorIndexingProperties ) *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( DescriptorSetVariableDescriptorCountAllocateInfo ) *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( DescriptorSetVariableDescriptorCountLayoutSupport ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceDepthStencilResolveProperties ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( SubpassDescriptionDepthStencilResolve ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceScalarBlockLayoutFeatures ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ImageStencilUsageCreateInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceSamplerFilterMinmaxProperties ) *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( SamplerReductionModeCreateInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceVulkanMemoryModelFeatures ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceImagelessFrameBufferFeatures ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( FrameBufferAttachmentsCreateInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( FrameBufferAttachmentImageInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( RenderPassAttachmentBeginInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceUniformBufferStandardLayoutFeatures ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceShaderSubgroupExtendedTypesFeatures ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceSeparateDepthStencilLayoutsFeatures ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( AttachmentReferenceStencilLayout ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( AttachmentDescriptionStencilLayout ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceHostQueryResetFeatures ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceTimelineSemaphoreFeatures ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceTimelineSemaphoreProperties ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( SemaphoreTypeCreateInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( TimelineSemaphoreSubmitInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( SemaphoreWaitInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( SemaphoreSignalInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceBufferDeviceAddressFeatures ) *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( BufferDeviceAddressInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( BufferOpaqueCaptureAddressCreateInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( MemoryOpaqueCaptureAddressAllocateInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( DeviceMemoryOpaqueCaptureAddressInfo ) *, StructurePtr )
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceVulkan13Features ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceVulkan13Properties ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PipelineCreationFeedbackCreateInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceShaderTerminateInvocationFeatures ) const *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceToolProperties ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceShaderDemoteToHelperInvocationFeatures ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDevicePrivateDataFeatures ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( DevicePrivateDataCreateInfo ) const *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PrivateDataSlotCreateInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDevicePipelineCreationCacheControlFeatures ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( MemoryBarrier2 ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( BufferMemoryBarrier2 ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ImageMemoryBarrier2 ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( DependencyInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( SubmitInfo2 ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( SemaphoreSubmitInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( CommandBufferSubmitInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceSynchronizationFeatures ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceZeroInitializeWorkgroupMemoryFeatures ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceImageRobustnessFeatures ) const *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( CopyBufferInfo ) const *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( CopyImageInfo ) const *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( CopyBufferToImageInfo ) const *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( CopyImageToBufferInfo ) const *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( BlitImageInfo ) const *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ResolveImageInfo ) const *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( BufferCopy ) const *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ImageCopy ) const *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ImageBlit ) const *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( BufferImageCopy ) const *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ImageResolve ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceSubgroupSizeControlFeatures ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceSubgroupSizeControlProperties ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PipelineShaderStageRequiredSubgroupSizeCreateInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceInlineUniformBlockFeatures ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceInlineUniformBlockProperties ) const *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( WriteDescriptorSetInlineUniformBlock ) const *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( DescriptorPoolInlineUniformBlockCreateInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceTextureCompressionASTCHDRFeatures ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( RenderingInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( RenderingAttachmentInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PipelineRenderingCreateInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceDynamicRenderingFeatures ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( CommandBufferInheritanceRenderingInfo ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceShaderIntegerDotProductFeatures ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceShaderIntegerDotProductProperties ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceTexelBufferAlignmentFeatures ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceTexelBufferAlignmentProperties ) const *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( FormatProperties3 ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceMaintenance4Features ) const *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceMaintenance4Properties ) const *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceBufferMemoryRequirements ) const *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceImageMemoryRequirements ) const *, StructurePtr )

__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceVulkan13Features ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceVulkan13Properties ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PipelineCreationFeedbackCreateInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceShaderTerminateInvocationFeatures ) *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceToolProperties ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceShaderDemoteToHelperInvocationFeatures ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDevicePrivateDataFeatures ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( DevicePrivateDataCreateInfo ) *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PrivateDataSlotCreateInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDevicePipelineCreationCacheControlFeatures ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( MemoryBarrier2 ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( BufferMemoryBarrier2 ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ImageMemoryBarrier2 ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( DependencyInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( SubmitInfo2 ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( SemaphoreSubmitInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( CommandBufferSubmitInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceSynchronizationFeatures ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceZeroInitializeWorkgroupMemoryFeatures ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceImageRobustnessFeatures ) *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( CopyBufferInfo ) *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( CopyImageInfo ) *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( CopyBufferToImageInfo ) *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( CopyImageToBufferInfo ) *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( BlitImageInfo ) *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ResolveImageInfo ) *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( BufferCopy ) *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ImageCopy ) *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ImageBlit ) *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( BufferImageCopy ) *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ImageResolve ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceSubgroupSizeControlFeatures ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceSubgroupSizeControlProperties ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PipelineShaderStageRequiredSubgroupSizeCreateInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceInlineUniformBlockFeatures ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceInlineUniformBlockProperties ) *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( WriteDescriptorSetInlineUniformBlock ) *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( DescriptorPoolInlineUniformBlockCreateInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceTextureCompressionASTCHDRFeatures ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( RenderingInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( RenderingAttachmentInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PipelineRenderingCreateInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceDynamicRenderingFeatures ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( CommandBufferInheritanceRenderingInfo ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceShaderIntegerDotProductFeatures ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceShaderIntegerDotProductProperties ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceTexelBufferAlignmentFeatures ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceTexelBufferAlignmentProperties ) *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( FormatProperties3 ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceMaintenance4Features ) *, StructurePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceMaintenance4Properties ) *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceBufferMemoryRequirements ) *, StructurePtr )
//__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceImageMemoryRequirements ) *, StructurePtr )
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( AllocationCallbacks ) const *, AllocationCallbacksPtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( LayerProperties ), LayerProperties )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ExtensionProperties ), ExtensionProperties )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PerformanceCounter ), PerformanceCounter )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PerformanceCounterDescription ), PerformanceCounterDescription )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceGroupProperties ), PhysicalDeviceGroupProperties )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( QueueFamilyProperties ), QueueFamilyProperties )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceProperties ) *, PhysicalDevicePropertiesPtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceFeatures ) *, PhysicalDeviceFeaturesPtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( SurfaceFormat ), SurfaceFormat )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( Extent2D ), Extent2DPtr )

__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( QueueFamilyExtendedProperties ), Structure )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( SubmitInfo ), Structure )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( DependencyInfo ), Structure )
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PipelineExecutableProperties ), Structure )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PipelineExecutableStatistic ), Structure )
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COOPERATIVE_MATRIX_AVAILABLE
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( CooperativeMatrixPropertiesNVidia ), CooperativeMatrixPropertiesNVidia )
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_CACHE_AVAILABLE
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ValidationCacheHandle ), Handle )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ValidationCacheHandle ) *, HandlePtr )
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( InstanceHandle ), Handle )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( InstanceHandle ) *, HandlePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceHandle ), Handle )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PhysicalDeviceHandle * ), HandlePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( DeviceHandle ), Handle )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( DeviceHandle ) *, HandlePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( DisplayHandle ), Handle )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( DisplayHandle ) *, HandlePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( DebugMessengerHandle ), Handle )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( DebugMessengerHandle ) *, HandlePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( SurfaceHandle ) , Handle )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( SurfaceHandle ) *, HandlePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( QueueHandle ) , Handle )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( QueueHandle ) * , HandlePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ImageViewHandle ) , Handle )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ImageViewHandle ) * , HandlePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ImageHandle ) , Handle )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ImageHandle ) * , HandlePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( CommandPoolHandle ) , Handle )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( CommandPoolHandle ) * , HandlePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( CommandBufferHandle ) , Handle )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( CommandBufferHandle ) * , HandlePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( SwapChainHandle ) , Handle )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( SwapChainHandle ) * , HandlePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( FenceHandle ) , Handle )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( FenceHandle ) * , HandlePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( SemaphoreHandle ) , Handle )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( SemaphoreHandle ) * , HandlePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( RenderPassHandle ) , Handle )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( RenderPassHandle ) * , HandlePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( FrameBufferHandle ) , Handle )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( FrameBufferHandle ) * , HandlePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ShaderModuleHandle ) , Handle )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( ShaderModuleHandle ) * , HandlePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PipelineCacheHandle ) , Handle )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PipelineCacheHandle ) * , HandlePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PipelineHandle ) , Handle )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( PipelineHandle ) * , HandlePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( DeferredOperationHandle ) , Handle )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( DeferredOperationHandle ) * , HandlePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( DeviceMemoryHandle ) , Handle )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( DeviceMemoryHandle ) * , HandlePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( BufferHandle ) , Handle )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( BufferHandle ) * , HandlePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( AccelerationStructureHandleNVidia ) , Handle )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( AccelerationStructureHandleNVidia ) * , HandlePtr )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( AccelerationStructureHandle ) , Handle )
__C_ENG_DUMP_MANAGER_SET_TYPE ( engine :: vulkan :: Type ( AccelerationStructureHandle ) * , HandlePtr )
#endif

__C_ENG_DUMP_MANAGER_SET_TYPE ( DumpedArray, DumpArrayPack )
__C_ENG_DUMP_MANAGER_SET_TYPE ( Flags, Flags )

#undef __C_ENG_DUMP_MANAGER_SET_TYPE

inline auto loadParameters (
        cds :: uint32           index,
        SharedContext         & dumpContext
) noexcept -> void {}

template < typename LastArgumentType >
inline auto loadParameters (
        cds :: uint32           index,
        SharedContext         & dumpContext,
        LastArgumentType     && lastArgument
) noexcept -> void {

    dumpContext.common.common.dump.params[index] = {
            .type   = parameterTypeOfParameter ( lastArgument ),
            .pParam = & lastArgument
    };
}

template < typename FirstArgumentType, typename ... ArgumentTypes >
inline auto loadParameters (
        cds :: uint32           index,
        SharedContext         & dumpContext,
        FirstArgumentType    && firstArgument,
        ArgumentTypes    && ... remainingArguments
) noexcept -> void {

    dumpContext.common.common.dump.params[index] = {
            .type   = parameterTypeOfParameter ( firstArgument ),
            .pParam = & firstArgument
    };

    loadParameters (
            index + 1,
            dumpContext,
            std :: forward < ArgumentTypes && > ( remainingArguments ) ...
    );
}

template < typename ... ArgumentTypes >
inline auto prepareDump (
        SharedContext             & dumpContext,
        cds :: StringLiteral        apiFunction,
        cds :: StringLiteral        apiFunctionDescription,
        ArgumentTypes        && ... arguments
) noexcept -> void {
    dumpContext.common.common.dump.contextType             = ContextType :: None;
    dumpContext.common.common.dump.apiFunction             = apiFunction;
    dumpContext.common.common.dump.apiFunctionDescription  = apiFunctionDescription;
    dumpContext.common.common.dump.paramCount              = sizeof ... (arguments);

    loadParameters (
            0,
            dumpContext,
            std :: forward < ArgumentTypes && > ( arguments ) ...
    );
}

template < typename ... ArgumentTypes >
inline auto prepareDump (
        SharedContext             & dumpContext,
        SharedContextType           contextType,
        cds :: StringLiteral        apiFunction,
        cds :: StringLiteral        apiFunctionDescription,
        ArgumentTypes        && ... arguments
) noexcept -> void {
    dumpContext.common.common.dump.contextType                      = ContextType :: Shared;
    dumpContext.common.common.dump.specializedContextType.shared    = contextType;
    dumpContext.common.common.dump.apiFunction                      = apiFunction;
    dumpContext.common.common.dump.apiFunctionDescription           = apiFunctionDescription;
    dumpContext.common.common.dump.paramCount                       = sizeof ... (arguments);

    loadParameters (
            0,
            dumpContext,
            std :: forward < ArgumentTypes && > ( arguments ) ...
    );
}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif //__C_ENG_DUMP_MANAGER_HPP__
