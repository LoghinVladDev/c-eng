//
// Created by vladl on 07/08/2020.
//

#include <VStdUtils.hpp>
#include "VPhysicalDevice.hpp"
#include "VPhysicalDeviceDefs.h"

bool engine::VPhysicalDevice::_physicalDevicesQueried = false;
std::vector < VulkanPhysicalDevice > engine::VPhysicalDevice::_availablePhysicalDeviceHandles = std::vector < VulkanPhysicalDevice > ();
std::vector < engine::VPhysicalDevice > engine::VPhysicalDevice::_availablePhysicalDevices = std::vector < engine::VPhysicalDevice > ();

auto engine::VPhysicalDevice::querySwapChainOnSurfaceSupport(
        engine::VSurface const * surface
) const noexcept -> engine::VPhysicalDevice::SwapChainSupportDetails {
    SwapChainSupportDetails details;

    if( surface == nullptr )
        return details; /// if surface is invalid, return empty details

    uint32 formatCount      = 0U;
    uint32 presentModeCount = 0U;

    /// query capabilities
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(
            this->_physicalDeviceHandle,
            surface->data(),
            & details.capabilities
    );

    /// query format count
    vkGetPhysicalDeviceSurfaceFormatsKHR(
            this->_physicalDeviceHandle,
            surface->data(),
            & formatCount,
            nullptr // do not pass any linear data structure yet as we do not know the count
    );

    /// query present mode count
    vkGetPhysicalDeviceSurfacePresentModesKHR(
            this->_physicalDeviceHandle,
            surface->data(),
            & presentModeCount,
            nullptr // same as above
    );

    if( formatCount != 0U ) { /// re-query formats if count != 0
        details.formats.resize ( formatCount );
        vkGetPhysicalDeviceSurfaceFormatsKHR(
                this->_physicalDeviceHandle,
                surface->data(),
                & formatCount,
                details.formats.data()
        );
    }

    if( presentModeCount != 0U ) { // re-query present modes if count != 0
        details.presentModes.resize ( presentModeCount );
        vkGetPhysicalDeviceSurfacePresentModesKHR(
                this->_physicalDeviceHandle,
                surface->data(),
                & presentModeCount,
                details.presentModes.data()
        );
    }

    return details;
}

auto engine::VPhysicalDevice::getPhysicalDeviceRenderRating() const noexcept -> uint32 {
    uint32 deviceScore = 0U;

    // TODO : definitely research into "scoring" of GPUs, but for development reasons, this will do

    if ( ! this->_physicalDeviceFeatures.geometryShader ) /// if incapable of rendering, score is 0
        return 0U;

    if( this->_physicalDeviceProperties.deviceType == __VK_PHYSICAL_DEVICE_TYPE_DEDICATED_GPU ) /// if dedicated GPU
        deviceScore += __VK_PHYSICAL_DEVICE_DEDICATED_GPU_VALUE_CONSTANT; /// apply dedicated GPU bias

    deviceScore += this->_physicalDeviceProperties.limits.maxImageDimension2D *
            __VK_PHYSICAL_DEVICE_PROPERTY_LIMIT_MAX_IMAGE_DIM_2D_SCALE; /// apply max image dimension as a score ( texture or resolution )

    return deviceScore;
}

auto engine::VPhysicalDevice::queryAvailablePhysicalDevices(
        engine::VInstance const & instance
) noexcept (false) -> void {
    if( VPhysicalDevice::_physicalDevicesQueried ) /// if already queried, do not re-query
        return;

    uint32 deviceCount = 0U;

    vkEnumeratePhysicalDevices( instance.data(), & deviceCount, nullptr ); /// acquire number of devices first

    if(deviceCount == 0U) /// if no devices, throw
        throw std::runtime_error ( "failed to find Vulkan supported GPUS" );

    /// acquire device handles
    VPhysicalDevice::_availablePhysicalDeviceHandles = std::vector < VulkanPhysicalDevice > ( deviceCount );
    vkEnumeratePhysicalDevices( instance.data(), & deviceCount, VPhysicalDevice::_availablePhysicalDeviceHandles.data() );

    /// create vector of Physical Device Objects
    VPhysicalDevice::_availablePhysicalDevices = std::vector < VPhysicalDevice > ();

    for( const auto & deviceHandle : VPhysicalDevice::_availablePhysicalDeviceHandles ) {
        /// emplace will create an object in place, calling the constructor with the argument given -> will call "copy"
        /// constructor, the one where a handle is given and a Physical Device will be constructed, its' properties
        /// being queried on creation
        VPhysicalDevice::_availablePhysicalDevices.emplace_back( deviceHandle ); // attach handles to objects, by creation
    }

    VPhysicalDevice::_physicalDevicesQueried = true; /// do not re-query again later
}


auto engine::VPhysicalDevice::supportsExtension (
        engine::VExtension const & extension
) const noexcept -> bool {
    /// aggregate operation, obtain extensions for device, see if it exists
    return VExtensionCollection::getPhysicalDeviceAvailableExtensions ( *this ).contains ( extension );
}

auto engine::VPhysicalDevice::supportsExtensions (
        engine::VExtensionCollection const & collection
) const noexcept -> bool {
    /// same as above, but for collection of extensions
    return VExtensionCollection::getPhysicalDeviceAvailableExtensions ( *this ).contains ( collection );
}


#ifndef NDEBUG

auto engine::VPhysicalDevice::debugPrintPhysicalDeviceProperties(
        std::ostream & buffer,
        bool detailedDebug,
        StringLiteral prefix
) const noexcept -> void {
    buffer << prefix << "VPhysicalDevice : \n";
    buffer << prefix << "\tHandle Ptr :                                                      " << this->_physicalDeviceHandle << '\n';
    buffer << prefix << "\tEngine Render Device Score :                                      " << this->getPhysicalDeviceRenderRating() << '\n';

    buffer << prefix << "\tBasic Properties : \n";
    VPhysicalDevice::debugPrintPhysicalDeviceBasicPropertiesStructure( this->_physicalDeviceProperties, buffer, std::string(prefix).append("\t\t").c_str() );

    if( detailedDebug ) {
        /// detailed debug = print all data
        this->debugPrintPhysicalDeviceSparseProperties(buffer, prefix);
        this->debugPrintPhysicalDeviceLimits(buffer, prefix);
        this->debugPrintPhysicalDeviceFeatures(buffer, prefix);
    }
}

auto engine::VPhysicalDevice::debugPrintPhysicalDeviceSparseProperties(
        std::ostream & buffer,
        StringLiteral prefix
) const noexcept -> void {
    buffer << prefix << "\tSparse Properties : \n";
    VPhysicalDevice::debugPrintPhysicalDeviceSparsePropertiesStructure( this->_physicalDeviceProperties.sparseProperties, buffer, std::string(prefix).append("\t\t").c_str() );
}

auto engine::VPhysicalDevice::debugPrintPhysicalDeviceLimits(
        std::ostream & buffer,
        StringLiteral prefix
) const noexcept -> void {
    buffer << prefix << "\tLimits : \n";
    VPhysicalDevice::debugPrintPhysicalDeviceLimitsStructure( this->_physicalDeviceProperties.limits, buffer, std::string(prefix).append("\t\t").c_str() );
}

auto engine::VPhysicalDevice::debugPrintPhysicalDeviceFeatures(
        std::ostream & buffer,
        StringLiteral prefix
) const noexcept -> void {
    buffer << prefix << "\tFeatures : \n";
    VPhysicalDevice::debugPrintPhysicalDeviceFeaturesStructure( this->_physicalDeviceFeatures, buffer, std::string(prefix).append("\t\t").c_str() );
}

#endif

#ifndef NDEBUG

auto engine::VPhysicalDevice::debugPrintAvailablePhysicalDevices(
        VInstance const & instance,
        std::ostream& buffer
) noexcept (false) -> void {
    VPhysicalDevice::queryAvailablePhysicalDevices( instance );
    uint32 deviceIndex = 0;

    buffer << "Vulkan Supported Physical Devices : \n";

    for( const auto & physicalDevice : VPhysicalDevice::_availablePhysicalDevices ) {
        buffer << "\tPhysical Device " << deviceIndex++ << " : \n";

        physicalDevice.debugPrintPhysicalDeviceProperties( buffer, true, "\t\t" );
    }
}

#endif

#ifndef NDEBUG

auto engine::VPhysicalDevice::debugPrintPhysicalDeviceBasicPropertiesStructure(
        VulkanPhysicalDeviceProperties const & properties,
        std::ostream & buffer,
        StringLiteral prefix
) noexcept -> void {
    buffer << prefix << "Name :                                                    " << properties.deviceName << '\n';
    buffer << prefix << "Device ID :                                               " << properties.deviceID << '\n';
    buffer << prefix << "Device Type :                                             " << properties.deviceType << '\n';
    buffer << prefix << "Api Version :                                             " << properties.apiVersion << '\n';
    buffer << prefix << "Driver Version :                                          " << properties.driverVersion << '\n';
    buffer << prefix << "Vendor ID :                                               " << properties.vendorID << '\n';

    buffer << prefix << "-------------------- Pipeline Cache UUID --------------------\n";
    for(uint16 it = 0; it < 16U; it++) {
        buffer << prefix << "Pipeline Cache UUID " << it << ( it < 10U ? "  : " : " : " ) << "                                 " << (uint16) properties.pipelineCacheUUID[it] << '\n';
    }
    buffer << prefix << "-------------------------------------------------------------\n";
}

#endif

#ifndef NDEBUG

auto engine::VPhysicalDevice::debugPrintPhysicalDeviceSparsePropertiesStructure(
        VulkanPhysicalDeviceSparseProperties const & sparseProperties,
        std::ostream & buffer,
        StringLiteral prefix
) noexcept -> void {
    /* VkBool32 */  buffer << prefix << "Residency Aligned MIP Size :                              " << engine::VStandardUtils::boolAlpha(
            sparseProperties.residencyAlignedMipSize) << '\n';
    /* VkBool32 */  buffer << prefix << "Residency Non Resident Strict :                           " << engine::VStandardUtils::boolAlpha(
            sparseProperties.residencyNonResidentStrict) << '\n';
    /* VkBool32 */  buffer << prefix << "Residency Standard 2D Block Shape :                       " << engine::VStandardUtils::boolAlpha(
            sparseProperties.residencyStandard2DBlockShape) << '\n';
    /* VkBool32 */  buffer << prefix << "Residency Standard 3D Block Shape :                       " << engine::VStandardUtils::boolAlpha(
            sparseProperties.residencyStandard3DBlockShape) << '\n';
    /* VkBool32 */  buffer << prefix << "Residency Standard 2D Multisample Block Shape :           " << engine::VStandardUtils::boolAlpha(
            sparseProperties.residencyStandard2DMultisampleBlockShape) << '\n';
}

#endif

#ifndef NDEBUG

auto engine::VPhysicalDevice::debugPrintPhysicalDeviceLimitsStructure(
        VulkanPhysicalDeviceLimits const & limits,
        std::ostream & buffer,
        StringLiteral prefix
) noexcept -> void {

    /* uint32_t              */ buffer << prefix << "Max Image Dimension 1D :                                  " << limits.maxImageDimension1D                               << '\n';
    /* uint32_t              */ buffer << prefix << "Max Image Dimension 2D :                                  " << limits.maxImageDimension2D                               << '\n';
    /* uint32_t              */ buffer << prefix << "Max Image Dimension 3D :                                  " << limits.maxImageDimension3D                               << '\n';
    /* uint32_t              */ buffer << prefix << "Max Image Dimension Cube :                                " << limits.maxImageDimensionCube                             << '\n';
    /* uint32_t              */ buffer << prefix << "Max Image Array Layers :                                  " << limits.maxImageArrayLayers                               << '\n';
    /* uint32_t              */ buffer << prefix << "Max Texel Buffer Elements :                               " << limits.maxTexelBufferElements                            << '\n';
    /* uint32_t              */ buffer << prefix << "Max Uniform Buffer Range :                                " << limits.maxUniformBufferRange                             << '\n';
    /* uint32_t              */ buffer << prefix << "Max Storage Buffer Range :                                " << limits.maxStorageBufferRange                             << '\n';
    /* uint32_t              */ buffer << prefix << "Max Push Constants Size :                                 " << limits.maxPushConstantsSize                              << '\n';
    /* uint32_t              */ buffer << prefix << "Max Memory Allocation Count :                             " << limits.maxMemoryAllocationCount                          << '\n';
    /* uint32_t              */ buffer << prefix << "Max Sampler Allocation Count :                            " << limits.maxSamplerAllocationCount                         << '\n';
    /* VkDeviceSize          */ buffer << prefix << "Buffer Image Granularity :                                " << limits.bufferImageGranularity                            << '\n';
    /* VkDeviceSize          */ buffer << prefix << "Sparse Address Space Size :                               " << limits.sparseAddressSpaceSize                            << '\n';
    /* uint32_t              */ buffer << prefix << "Max Bound Descriptor Sets :                               " << limits.maxBoundDescriptorSets                            << '\n';
    /* uint32_t              */ buffer << prefix << "Max Per Stage Descriptor Samples :                        " << limits.maxPerStageDescriptorSamplers                     << '\n';
    /* uint32_t              */ buffer << prefix << "Max Per Stage Descriptor Uniform Buffers :                " << limits.maxPerStageDescriptorUniformBuffers               << '\n';
    /* uint32_t              */ buffer << prefix << "Max Per Stage Descriptor Storage Buffers :                " << limits.maxPerStageDescriptorStorageBuffers               << '\n';
    /* uint32_t              */ buffer << prefix << "Max Per Stage Descriptor Sampled Images :                 " << limits.maxPerStageDescriptorSampledImages                << '\n';
    /* uint32_t              */ buffer << prefix << "Max Per Stage Descriptor Storage Items :                  " << limits.maxPerStageDescriptorStorageImages                << '\n';
    /* uint32_t              */ buffer << prefix << "Max Per Stage Descriptor Input Attachments :              " << limits.maxPerStageDescriptorInputAttachments             << '\n';
    /* uint32_t              */ buffer << prefix << "Max Per Stage Resources :                                 " << limits.maxPerStageResources                              << '\n';
    /* uint32_t              */ buffer << prefix << "Max Descriptor Set Samples :                              " << limits.maxDescriptorSetSamplers                          << '\n';
    /* uint32_t              */ buffer << prefix << "Max Descriptor Set Uniform Buffers :                      " << limits.maxDescriptorSetUniformBuffers                    << '\n';
    /* uint32_t              */ buffer << prefix << "Max Descriptor Set Uniform Buffers Dynamic :              " << limits.maxDescriptorSetUniformBuffersDynamic             << '\n';
    /* uint32_t              */ buffer << prefix << "Max Descriptor Set Storage Buffers :                      " << limits.maxDescriptorSetStorageBuffers                    << '\n';
    /* uint32_t              */ buffer << prefix << "Max Descriptor Set Storage Buffers Dynamic :              " << limits.maxDescriptorSetStorageBuffersDynamic             << '\n';
    /* uint32_t              */ buffer << prefix << "Max Descriptor Set Sampled Images :                       " << limits.maxDescriptorSetSampledImages                     << '\n';
    /* uint32_t              */ buffer << prefix << "Max Descriptor Set Storage Images :                       " << limits.maxDescriptorSetStorageImages                     << '\n';
    /* uint32_t              */ buffer << prefix << "Max Descriptor Set Input Attachments :                    " << limits.maxDescriptorSetInputAttachments                  << '\n';
    /* uint32_t              */ buffer << prefix << "Max Vertex Input Attributes :                             " << limits.maxVertexInputAttributes                          << '\n';
    /* uint32_t              */ buffer << prefix << "Max Vertex Input Bindings :                               " << limits.maxVertexInputBindings                            << '\n';
    /* uint32_t              */ buffer << prefix << "Max Vertex Input Attribute Offset :                       " << limits.maxVertexInputAttributeOffset                     << '\n';
    /* uint32_t              */ buffer << prefix << "Max Vertex Input Binding Stride :                         " << limits.maxVertexInputBindingStride                       << '\n';
    /* uint32_t              */ buffer << prefix << "Max Vertex Output Components :                            " << limits.maxVertexOutputComponents                         << '\n';
    /* uint32_t              */ buffer << prefix << "Max Tesselation Generation Level :                        " << limits.maxTessellationGenerationLevel                    << '\n';
    /* uint32_t              */ buffer << prefix << "Max Tesselation Patch Size :                              " << limits.maxTessellationPatchSize                          << '\n';
    /* uint32_t              */ buffer << prefix << "Max Tesselation Control Per Vertex Input Components :     " << limits.maxTessellationControlPerVertexInputComponents    << '\n';
    /* uint32_t              */ buffer << prefix << "Max Tesselation Control Per Vertex Output Components :    " << limits.maxTessellationControlPerVertexOutputComponents   << '\n';
    /* uint32_t              */ buffer << prefix << "Max Tesselation Control Per Patch Output Components :     " << limits.maxTessellationControlPerPatchOutputComponents    << '\n';
    /* uint32_t              */ buffer << prefix << "Max Tesselation Control Total Output Components :         " << limits.maxTessellationControlTotalOutputComponents       << '\n';
    /* uint32_t              */ buffer << prefix << "Max Tesselation Evaluation Input Components :             " << limits.maxTessellationEvaluationInputComponents          << '\n';
    /* uint32_t              */ buffer << prefix << "Max Tesselation Evaluation Output Components :            " << limits.maxTessellationEvaluationOutputComponents         << '\n';
    /* uint32_t              */ buffer << prefix << "Max Geometry Shader Invocations :                         " << limits.maxGeometryShaderInvocations                      << '\n';
    /* uint32_t              */ buffer << prefix << "Max Geometry Input Components :                           " << limits.maxGeometryInputComponents                        << '\n';
    /* uint32_t              */ buffer << prefix << "Max Geometry Output Components :                          " << limits.maxGeometryOutputComponents                       << '\n';
    /* uint32_t              */ buffer << prefix << "Max Geometry Output Vertices :                            " << limits.maxGeometryOutputVertices                         << '\n';
    /* uint32_t              */ buffer << prefix << "Max Geometry Total Output Components :                    " << limits.maxGeometryTotalOutputComponents                  << '\n';
    /* uint32_t              */ buffer << prefix << "Max Fragment Input Components :                           " << limits.maxFragmentInputComponents                        << '\n';
    /* uint32_t              */ buffer << prefix << "Max Fragment Output Attachments :                         " << limits.maxFragmentOutputAttachments                      << '\n';
    /* uint32_t              */ buffer << prefix << "Max Fragment Dual Source Attachments :                    " << limits.maxFragmentDualSrcAttachments                     << '\n';
    /* uint32_t              */ buffer << prefix << "Max Fragment Combined Output Resources :                  " << limits.maxFragmentCombinedOutputResources                << '\n';
    /* uint32_t              */ buffer << prefix << "Max Compute Shader Memory Size :                          " << limits.maxComputeSharedMemorySize                        << '\n';
    /* uint32_t              */ buffer << prefix << "Max Compute Work Group Count _first_ :                    " << limits.maxComputeWorkGroupCount[0]                       << '\n'; //[3];
    /* uint32_t              */ buffer << prefix << "Max Compute Work Group Count _second_ :                   " << limits.maxComputeWorkGroupCount[1]                       << '\n'; //[3];
    /* uint32_t              */ buffer << prefix << "Max Compute Work Group Count _third_ :                    " << limits.maxComputeWorkGroupCount[2]                       << '\n'; //[3];
    /* uint32_t              */ buffer << prefix << "Max Compute Work Group Invocations :                      " << limits.maxComputeWorkGroupInvocations                    << '\n';
    /* uint32_t              */ buffer << prefix << "Max Compute Work Group Size _first_ :                     " << limits.maxComputeWorkGroupSize[0]                        << '\n'; // [3];
    /* uint32_t              */ buffer << prefix << "Max Compute Work Group Size _second_ :                    " << limits.maxComputeWorkGroupSize[1]                        << '\n'; // [3];
    /* uint32_t              */ buffer << prefix << "Max Compute Work Group Size _third_ :                     " << limits.maxComputeWorkGroupSize[2]                        << '\n'; // [3];
    /* uint32_t              */ buffer << prefix << "Sub Pixel Precision Bits :                                " << limits.subPixelPrecisionBits                             << '\n';
    /* uint32_t              */ buffer << prefix << "Sub Texel Precision Bits :                                " << limits.subTexelPrecisionBits                             << '\n';
    /* uint32_t              */ buffer << prefix << "Mipmap Precision Bits :                                   " << limits.mipmapPrecisionBits                               << '\n';
    /* uint32_t              */ buffer << prefix << "Max Draw Indexed Index Value :                            " << limits.maxDrawIndexedIndexValue                          << '\n';
    /* uint32_t              */ buffer << prefix << "Max Draw Indirect Count :                                 " << limits.maxDrawIndirectCount                              << '\n';
    /* float                 */ buffer << prefix << "Max Sampler Level Of Detail Bias :                        " << limits.maxSamplerLodBias                                 << '\n';
    /* float                 */ buffer << prefix << "Max Sampler Anisotropy :                                  " << limits.maxSamplerAnisotropy                              << '\n';
    /* uint32_t              */ buffer << prefix << "Max Viewports :                                           " << limits.maxViewports                                      << '\n';
    /* uint32_t              */ buffer << prefix << "Max Viewport Dimensions _first_ :                         " << limits.maxViewportDimensions[0]                          << '\n';//[2];
    /* uint32_t              */ buffer << prefix << "Max Viewport Dimensions _second_ :                        " << limits.maxViewportDimensions[1]                          << '\n';//[2];
    /* float                 */ buffer << prefix << "Max Viewport Bounds Range _first_                         " << limits.viewportBoundsRange[0]                            << '\n';//[2];
    /* float                 */ buffer << prefix << "Max Viewport Bounds Range _second_                        " << limits.viewportBoundsRange[1]                            << '\n';//[2];
    /* uint32_t              */ buffer << prefix << "Viewport Sub Pixel Bits :                                 " << limits.viewportSubPixelBits                              << '\n';
    /* size_t                */ buffer << prefix << "Min Memory Map Alignment :                                " << limits.minMemoryMapAlignment                             << '\n';
    /* VkDeviceSize          */ buffer << prefix << "Min Texel Buffer Offset Alignment :                       " << limits.minTexelBufferOffsetAlignment                     << '\n';
    /* VkDeviceSize          */ buffer << prefix << "Min Uniform Buffer Offset Alignment :                     " << limits.minUniformBufferOffsetAlignment                   << '\n';
    /* VkDeviceSize          */ buffer << prefix << "Min Storage Buffer Offset Alignment :                     " << limits.minStorageBufferOffsetAlignment                   << '\n';
    /* int32_t               */ buffer << prefix << "Min Texel Offset :                                        " << limits.minTexelOffset                                    << '\n';
    /* uint32_t              */ buffer << prefix << "Max Texel Offset :                                        " << limits.maxTexelOffset                                    << '\n';
    /* int32_t               */ buffer << prefix << "Min Texel Gather Offset :                                 " << limits.minTexelGatherOffset                              << '\n';
    /* uint32_t              */ buffer << prefix << "Max texel Gather Offset :                                 " << limits.maxTexelGatherOffset                              << '\n';
    /* float                 */ buffer << prefix << "Min Interpolation Offset :                                " << limits.minInterpolationOffset                            << '\n';
    /* float                 */ buffer << prefix << "Max Interpolation Offset :                                " << limits.maxInterpolationOffset                            << '\n';
    /* uint32_t              */ buffer << prefix << "Sub Pixel Interpolation Offset Bits :                     " << limits.subPixelInterpolationOffsetBits                   << '\n';
    /* uint32_t              */ buffer << prefix << "Max Framebuffer Width :                                   " << limits.maxFramebufferWidth                               << '\n';
    /* uint32_t              */ buffer << prefix << "Max Framebuffer Height :                                  " << limits.maxFramebufferHeight                              << '\n';
    /* uint32_t              */ buffer << prefix << "Max Framebuffer Layers :                                  " << limits.maxFramebufferLayers                              << '\n';
    /* VkSampleCountFlags    */ buffer << prefix << "Framebuffer Color Sample Counts _flags_ :                 " << limits.framebufferColorSampleCounts                      << '\n';
    /* VkSampleCountFlags    */ buffer << prefix << "Framebuffer Depth Sample Counts _flags_ :                 " << limits.framebufferDepthSampleCounts                      << '\n';
    /* VkSampleCountFlags    */ buffer << prefix << "Framebuffer Stencil Sample Counts _flags_ :               " << limits.framebufferStencilSampleCounts                    << '\n';
    /* VkSampleCountFlags    */ buffer << prefix << "Framebuffer No Attachments Sample Counts _flags_ :        " << limits.framebufferNoAttachmentsSampleCounts              << '\n';
    /* uint32_t              */ buffer << prefix << "Max Color Attachments :                                   " << limits.maxColorAttachments                               << '\n';
    /* VkSampleCountFlags    */ buffer << prefix << "Sampled Image Color Sample Counts _flags_ :               " << limits.sampledImageColorSampleCounts                     << '\n';
    /* VkSampleCountFlags    */ buffer << prefix << "Sampled Image Integer Sample Counts _flags_ :             " << limits.sampledImageIntegerSampleCounts                   << '\n';
    /* VkSampleCountFlags    */ buffer << prefix << "Sampled Image Depth Sample Counts _flags_ :               " << limits.sampledImageDepthSampleCounts                     << '\n';
    /* VkSampleCountFlags    */ buffer << prefix << "Sampled Image Stencil Sample Counts _flags_ :             " << limits.sampledImageStencilSampleCounts                   << '\n';
    /* VkSampleCountFlags    */ buffer << prefix << "Storage Image Sample Counts _flags_ :                     " << limits.storageImageSampleCounts                          << '\n';
    /* uint32_t              */ buffer << prefix << "Max Sample Mask Words :                                   " << limits.maxSampleMaskWords                                << '\n';
    /* VkBool32              */ buffer << prefix << "Timestamp Compute and Graphics :                          " << limits.timestampComputeAndGraphics                       << '\n';
    /* float                 */ buffer << prefix << "Timestamp Period :                                        " << limits.timestampPeriod                                   << '\n';
    /* uint32_t              */ buffer << prefix << "Max Clip Distances :                                      " << limits.maxClipDistances                                  << '\n';
    /* uint32_t              */ buffer << prefix << "Max Cull Distances :                                      " << limits.maxCullDistances                                  << '\n';
    /* uint32_t              */ buffer << prefix << "Max Combined Clip, Cull Distances :                       " << limits.maxCombinedClipAndCullDistances                   << '\n';
    /* uint32_t              */ buffer << prefix << "Discrete Queue Priorities :                               " << limits.discreteQueuePriorities                           << '\n';
    /* float                 */ buffer << prefix << "Point Size Range _first_ :                                " << limits.pointSizeRange[0]                                 << '\n';//[2];
    /* float                 */ buffer << prefix << "Point Size Range _second_ :                               " << limits.pointSizeRange[1]                                 << '\n';//[2];
    /* float                 */ buffer << prefix << "Line Width Range _first_ :                                " << limits.lineWidthRange[0]                                 << '\n';//[2];
    /* float                 */ buffer << prefix << "Line Width Range _second_ :                               " << limits.lineWidthRange[1]                                 << '\n';//[2];
    /* float                 */ buffer << prefix << "Point Size Granularity :                                  " << limits.pointSizeGranularity                              << '\n';
    /* float                 */ buffer << prefix << "Line Width Granularity :                                  " << limits.lineWidthGranularity                              << '\n';
    /* VkBool32              */ buffer << prefix << "Strict Lines :                                            " << limits.strictLines                                       << '\n';
    /* VkBool32              */ buffer << prefix << "Standard Sample Locations :                               " << limits.standardSampleLocations                           << '\n';
    /* VkDeviceSize          */ buffer << prefix << "Optimal Buffer Copy Offset Alignment :                    " << limits.optimalBufferCopyOffsetAlignment                  << '\n';
    /* VkDeviceSize          */ buffer << prefix << "Optimal Buffer Copy Row Pitch Alignment :                 " << limits.optimalBufferCopyRowPitchAlignment                << '\n';
    /* VkDeviceSize          */ buffer << prefix << "Non Coherent Atom Size :                                  " << limits.nonCoherentAtomSize                               << '\n';
}

#endif

#ifndef NDEBUG

auto engine::VPhysicalDevice::debugPrintPhysicalDeviceFeaturesStructure(
        VulkanPhysicalDeviceFeatures const & features,
        std::ostream & buffer,
        StringLiteral prefix
) noexcept -> void {
    /* VkBool32 */  buffer << prefix << "Robust Buffer Access :                                    " << engine::VStandardUtils::boolAlpha(
            features.robustBufferAccess) << '\n';
    /* VkBool32 */  buffer << prefix << "Full Draw Index Unsigned Integer 32 :                     " << engine::VStandardUtils::boolAlpha(
            features.fullDrawIndexUint32) << '\n';
    /* VkBool32 */  buffer << prefix << "Image Cube Array :                                        " << engine::VStandardUtils::boolAlpha(
            features.imageCubeArray) << '\n';
    /* VkBool32 */  buffer << prefix << "Implement Blend :                                         " << engine::VStandardUtils::boolAlpha(
            features.independentBlend) << '\n';
    /* VkBool32 */  buffer << prefix << "Geometry Shader :                                         " << engine::VStandardUtils::boolAlpha(
            features.geometryShader) << '\n';
    /* VkBool32 */  buffer << prefix << "Tesselation Shader :                                      " << engine::VStandardUtils::boolAlpha(
            features.tessellationShader) << '\n';
    /* VkBool32 */  buffer << prefix << "Sample Rate Shading :                                     " << engine::VStandardUtils::boolAlpha(
            features.sampleRateShading) << '\n';
    /* VkBool32 */  buffer << prefix << "Dual Source Blend :                                       " << engine::VStandardUtils::boolAlpha(
            features.dualSrcBlend) << '\n';
    /* VkBool32 */  buffer << prefix << "Logic Operations :                                        " << engine::VStandardUtils::boolAlpha(
            features.logicOp) << '\n';
    /* VkBool32 */  buffer << prefix << "Multi Draw Indirect :                                     " << engine::VStandardUtils::boolAlpha(
            features.multiDrawIndirect) << '\n';
    /* VkBool32 */  buffer << prefix << "Draw Indirect First Instance :                            " << engine::VStandardUtils::boolAlpha(
            features.drawIndirectFirstInstance) << '\n';
    /* VkBool32 */  buffer << prefix << "Depth Clamp :                                             " << engine::VStandardUtils::boolAlpha(
            features.depthClamp) << '\n';
    /* VkBool32 */  buffer << prefix << "Depth Bias Clamp :                                        " << engine::VStandardUtils::boolAlpha(
            features.depthBiasClamp) << '\n';
    /* VkBool32 */  buffer << prefix << "Fill Mode Non Solid :                                     " << engine::VStandardUtils::boolAlpha(
            features.fillModeNonSolid) << '\n';
    /* VkBool32 */  buffer << prefix << "Depth Bounds :                                            " << engine::VStandardUtils::boolAlpha(
            features.depthBounds) << '\n';
    /* VkBool32 */  buffer << prefix << "Wide Lines :                                              " << engine::VStandardUtils::boolAlpha(
            features.wideLines) << '\n';
    /* VkBool32 */  buffer << prefix << "Large Points :                                            " << engine::VStandardUtils::boolAlpha(
            features.largePoints) << '\n';
    /* VkBool32 */  buffer << prefix << "Alpha to One :                                            " << engine::VStandardUtils::boolAlpha(
            features.alphaToOne) << '\n';
    /* VkBool32 */  buffer << prefix << "Multiple Viewports :                                      " << engine::VStandardUtils::boolAlpha(
            features.multiViewport) << '\n';
    /* VkBool32 */  buffer << prefix << "Sampler Anisotropy :                                      " << engine::VStandardUtils::boolAlpha(
            features.samplerAnisotropy) << '\n';
    /* VkBool32 */  buffer << prefix << "Texture Compression ETC2 :                                " << engine::VStandardUtils::boolAlpha(
            features.textureCompressionETC2) << '\n';
    /* VkBool32 */  buffer << prefix << "Texture Compression ATSC_LDR :                            " << engine::VStandardUtils::boolAlpha(
            features.textureCompressionASTC_LDR) << '\n';
    /* VkBool32 */  buffer << prefix << "Texture Compression BC :                                  " << engine::VStandardUtils::boolAlpha(
            features.textureCompressionBC) << '\n';
    /* VkBool32 */  buffer << prefix << "Occlusion Query Precise :                                 " << engine::VStandardUtils::boolAlpha(
            features.occlusionQueryPrecise) << '\n';
    /* VkBool32 */  buffer << prefix << "Pipeline Statistics Query :                               " << engine::VStandardUtils::boolAlpha(
            features.pipelineStatisticsQuery) << '\n';
    /* VkBool32 */  buffer << prefix << "Vertex Pipeline Stores And Atomics :                      " << engine::VStandardUtils::boolAlpha(
            features.vertexPipelineStoresAndAtomics) << '\n';
    /* VkBool32 */  buffer << prefix << "Fragment Stores and Atomics :                             " << engine::VStandardUtils::boolAlpha(
            features.fragmentStoresAndAtomics) << '\n';
    /* VkBool32 */  buffer << prefix << "Shader Tesselation and Geometry Point Size :              " << engine::VStandardUtils::boolAlpha(
            features.shaderTessellationAndGeometryPointSize) << '\n';
    /* VkBool32 */  buffer << prefix << "Shader Image Gather Extended :                            " << engine::VStandardUtils::boolAlpha(
            features.shaderImageGatherExtended) << '\n';
    /* VkBool32 */  buffer << prefix << "Shader Storage Image Extended Formats :                   " << engine::VStandardUtils::boolAlpha(
            features.shaderStorageImageExtendedFormats) << '\n';
    /* VkBool32 */  buffer << prefix << "Shader Storage Image Multisample :                        " << engine::VStandardUtils::boolAlpha(
            features.shaderStorageImageMultisample) << '\n';
    /* VkBool32 */  buffer << prefix << "Shader Storage Image Read Without Format :                " << engine::VStandardUtils::boolAlpha(
            features.shaderStorageImageReadWithoutFormat) << '\n';
    /* VkBool32 */  buffer << prefix << "Shader Storage Image Write Without Format :               " << engine::VStandardUtils::boolAlpha(
            features.shaderStorageImageWriteWithoutFormat) << '\n';
    /* VkBool32 */  buffer << prefix << "Shader Uniform Buffer Array Dynamic Indexing :            " << engine::VStandardUtils::boolAlpha(
            features.shaderUniformBufferArrayDynamicIndexing) << '\n';
    /* VkBool32 */  buffer << prefix << "Shader Sampled Image Array Dynamic Indexing :             " << engine::VStandardUtils::boolAlpha(
            features.shaderSampledImageArrayDynamicIndexing) << '\n';
    /* VkBool32 */  buffer << prefix << "Shader Storage Buffer Array Dynamic Indexing :            " << engine::VStandardUtils::boolAlpha(
            features.shaderStorageBufferArrayDynamicIndexing) << '\n';
    /* VkBool32 */  buffer << prefix << "Shader Storage Image Array Dynamic Indexing :             " << engine::VStandardUtils::boolAlpha(
            features.shaderStorageImageArrayDynamicIndexing) << '\n';
    /* VkBool32 */  buffer << prefix << "Shader Clip Distance :                                    " << engine::VStandardUtils::boolAlpha(
            features.shaderClipDistance) << '\n';
    /* VkBool32 */  buffer << prefix << "Shader Cull Distance :                                    " << engine::VStandardUtils::boolAlpha(
            features.shaderCullDistance) << '\n';
    /* VkBool32 */  buffer << prefix << "Shader Float 64 :                                         " << engine::VStandardUtils::boolAlpha(
            features.shaderFloat64) << '\n';
    /* VkBool32 */  buffer << prefix << "Shader Int 64 :                                           " << engine::VStandardUtils::boolAlpha(
            features.shaderInt64) << '\n';
    /* VkBool32 */  buffer << prefix << "Shader Int 16 :                                           " << engine::VStandardUtils::boolAlpha(
            features.shaderInt16) << '\n';
    /* VkBool32 */  buffer << prefix << "Shader Resource Residency :                               " << engine::VStandardUtils::boolAlpha(
            features.shaderResourceResidency) << '\n';
    /* VkBool32 */  buffer << prefix << "Shader Resource Min LOD :                                 " << engine::VStandardUtils::boolAlpha(
            features.shaderResourceMinLod) << '\n';
    /* VkBool32 */  buffer << prefix << "Sparse Binding :                                          " << engine::VStandardUtils::boolAlpha(
            features.sparseBinding) << '\n';
    /* VkBool32 */  buffer << prefix << "Sparse Residency Buffer :                                 " << engine::VStandardUtils::boolAlpha(
            features.sparseResidencyBuffer) << '\n';
    /* VkBool32 */  buffer << prefix << "Sparse Residency Image 2D :                               " << engine::VStandardUtils::boolAlpha(
            features.sparseResidencyImage2D) << '\n';
    /* VkBool32 */  buffer << prefix << "Sparse Residency Image 3D :                               " << engine::VStandardUtils::boolAlpha(
            features.sparseResidencyImage3D) << '\n';
    /* VkBool32 */  buffer << prefix << "Sparse Residency 2 Samples :                              " << engine::VStandardUtils::boolAlpha(
            features.sparseResidency2Samples) << '\n';
    /* VkBool32 */  buffer << prefix << "Sparse Residency 4 Samples :                              " << engine::VStandardUtils::boolAlpha(
            features.sparseResidency4Samples) << '\n';
    /* VkBool32 */  buffer << prefix << "Sparse Residency 8 Samples :                              " << engine::VStandardUtils::boolAlpha(
            features.sparseResidency8Samples) << '\n';
    /* VkBool32 */  buffer << prefix << "Sparse Residency 16 Samples :                             " << engine::VStandardUtils::boolAlpha(
            features.sparseResidency16Samples) << '\n';
    /* VkBool32 */  buffer << prefix << "Sparse Residency Aliased :                                " << engine::VStandardUtils::boolAlpha(
            features.sparseResidencyAliased) << '\n';
    /* VkBool32 */  buffer << prefix << "Variable Multisample Rate :                               " << engine::VStandardUtils::boolAlpha(
            features.variableMultisampleRate) << '\n';
    /* VkBool32 */  buffer << prefix << "Inherited Queries :                                       " << engine::VStandardUtils::boolAlpha(
            features.inheritedQueries) << '\n';
}

#endif

#include <sstream>

auto engine::VPhysicalDevice::toString() const noexcept -> String {
    std::stringstream oss;

    oss << "VPhysicalDevice " <<
        "{ handle = 0x" << std::hex << this->_physicalDeviceHandle <<
        ", features & properties : use VPhysicalDevice::debugPrintPhysicalDeviceBasicPropertiesStructure, VPhysicalDevice::debugPrintPhysicalDeviceSparsePropertiesStructure, "
        "VPhysicalDevice::debugPrintPhysicalDeviceLimitsStructure, VPhysicalDevice::debugPrintPhysicalDeviceFeaturesStructure, "
        "or use VPhysicalDevice::debugPrintPhysicalDeviceProperties with true for param }";

    return oss.str();
}