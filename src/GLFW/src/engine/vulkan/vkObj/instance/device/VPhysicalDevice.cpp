//
// Created by vladl on 07/08/2020.
//

#include <src/GLFW/src/engine/vulkan/vkUtils/VStdUtils.h>
#include "VPhysicalDevice.h"
#include "VPhysicalDeviceDefs.h"

bool engine::VPhysicalDevice::_physicalDevicesQueried = false;
std::vector < VulkanPhysicalDevice > engine::VPhysicalDevice::_availablePhysicalDeviceHandles = std::vector < VulkanPhysicalDevice > ();
std::vector < engine::VPhysicalDevice > engine::VPhysicalDevice::_availablePhysicalDevices = std::vector < engine::VPhysicalDevice > ();

[[nodiscard]] engine::VPhysicalDevice::SwapChainSupportDetails engine::VPhysicalDevice::querySwapChainOnSurfaceSupport( const engine::VSurface * surface ) const noexcept {
    SwapChainSupportDetails details;

    if( surface == nullptr )
        return details;

    uint32 formatCount      = 0U;
    uint32 presentModeCount = 0U;

    vkGetPhysicalDeviceSurfaceCapabilitiesKHR( this->_physicalDeviceHandle, surface->data(), & details.capabilities );
    vkGetPhysicalDeviceSurfaceFormatsKHR( this->_physicalDeviceHandle, surface->data(), & formatCount, nullptr );
    vkGetPhysicalDeviceSurfacePresentModesKHR( this->_physicalDeviceHandle, surface->data(), & presentModeCount, nullptr );

    if( formatCount != 0U ) {
        details.formats.resize ( formatCount );
        vkGetPhysicalDeviceSurfaceFormatsKHR( this->_physicalDeviceHandle, surface->data(), & formatCount, details.formats.data() );
    }

    if( presentModeCount != 0U ) {
        details.presentModes.resize ( presentModeCount );
        vkGetPhysicalDeviceSurfacePresentModesKHR( this->_physicalDeviceHandle, surface->data(), & presentModeCount, details.presentModes.data() );
    }

    return details;
}

[[nodiscard]] uint32 engine::VPhysicalDevice::getPhysicalDeviceRenderRating() const noexcept {
    uint32 deviceScore = 0U;

    // TODO : definitely research into "scoring" of GPUs, but for development reasons, this will do

    if ( ! this->_physicalDeviceFeatures.geometryShader )
        return 0U;

    if( this->_physicalDeviceProperties.deviceType == __VK_PHYSICAL_DEVICE_TYPE_DEDICATED_GPU )
        deviceScore += __VK_PHYSICAL_DEVICE_DEDICATED_GPU_VALUE_CONSTANT;

    deviceScore += this->_physicalDeviceProperties.limits.maxImageDimension2D *
            __VK_PHYSICAL_DEVICE_PROPERTY_LIMIT_MAX_IMAGE_DIM_2D_SCALE;

    return deviceScore;
}

void engine::VPhysicalDevice::queryAvailablePhysicalDevices(const engine::VInstance & instance) noexcept (false) {
    if( VPhysicalDevice::_physicalDevicesQueried )
        return;

    uint32 deviceCount = 0U;

    vkEnumeratePhysicalDevices( instance.data(), & deviceCount, nullptr );

    if(deviceCount == 0U)
        throw std::runtime_error ( "failed to find Vulkan supported GPUS" );

    VPhysicalDevice::_availablePhysicalDeviceHandles = std::vector < VulkanPhysicalDevice > ( deviceCount );
    vkEnumeratePhysicalDevices( instance.data(), & deviceCount, VPhysicalDevice::_availablePhysicalDeviceHandles.data() );

    VPhysicalDevice::_availablePhysicalDevices = std::vector < VPhysicalDevice > ();

    for( const auto & deviceHandle : VPhysicalDevice::_availablePhysicalDeviceHandles ) {
        VPhysicalDevice::_availablePhysicalDevices.emplace_back( deviceHandle );
    }

    VPhysicalDevice::_physicalDevicesQueried = true;
}


[[nodiscard]] bool engine::VPhysicalDevice::supportsExtension  ( const engine::VExtension & extension ) const noexcept {
    return VExtensionCollection::getPhysicalDeviceAvailableExtensions ( *this ).contains ( extension );
}

[[nodiscard]] bool engine::VPhysicalDevice::supportsExtensions ( const engine::VExtensionCollection & collection ) const noexcept {
    return VExtensionCollection::getPhysicalDeviceAvailableExtensions ( *this ).contains ( collection );
}


#ifndef NDEBUG

void engine::VPhysicalDevice::debugPrintPhysicalDeviceProperties(std::ostream& buffer, bool detailedDebug, const char* prefix) const noexcept {
    buffer << prefix << "VPhysicalDevice : \n";
    buffer << prefix << "\tHandle Ptr :                                                      " << this->_physicalDeviceHandle << '\n';
    buffer << prefix << "\tEngine Render Device Score :                                      " << this->getPhysicalDeviceRenderRating() << '\n';

    buffer << prefix << "\tBasic Properties : \n";
    VPhysicalDevice::debugPrintPhysicalDeviceBasicPropertiesStructure( this->_physicalDeviceProperties, buffer, std::string(prefix).append("\t\t").c_str() );

    if( detailedDebug ) {
        this->debugPrintPhysicalDeviceSparseProperties(buffer, prefix);
        this->debugPrintPhysicalDeviceLimits(buffer, prefix);
        this->debugPrintPhysicalDeviceFeatures(buffer, prefix);
    }
}

void engine::VPhysicalDevice::debugPrintPhysicalDeviceSparseProperties(std::ostream& buffer, const char* prefix) const noexcept {
    buffer << prefix << "\tSparse Properties : \n";
    VPhysicalDevice::debugPrintPhysicalDeviceSparsePropertiesStructure( this->_physicalDeviceProperties.sparseProperties, buffer, std::string(prefix).append("\t\t").c_str() );
}

void engine::VPhysicalDevice::debugPrintPhysicalDeviceLimits(std::ostream& buffer, const char* prefix) const noexcept {
    buffer << prefix << "\tLimits : \n";
    VPhysicalDevice::debugPrintPhysicalDeviceLimitsStructure( this->_physicalDeviceProperties.limits, buffer, std::string(prefix).append("\t\t").c_str() );
}

void engine::VPhysicalDevice::debugPrintPhysicalDeviceFeatures(std::ostream& buffer, const char* prefix) const noexcept {
    buffer << prefix << "\tFeatures : \n";
    VPhysicalDevice::debugPrintPhysicalDeviceFeaturesStructure( this->_physicalDeviceFeatures, buffer, std::string(prefix).append("\t\t").c_str() );
}

#endif

#ifndef NDEBUG

void engine::VPhysicalDevice::debugPrintAvailablePhysicalDevices(const VInstance & instance, std::ostream& buffer) noexcept {
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

void engine::VPhysicalDevice::debugPrintPhysicalDeviceBasicPropertiesStructure( const VulkanPhysicalDeviceProperties & properties, std::ostream & buffer, const char * prefix) noexcept {
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

void engine::VPhysicalDevice::debugPrintPhysicalDeviceSparsePropertiesStructure( const VulkanPhysicalDeviceSparseProperties & sparseProperties, std::ostream & buffer,const char * prefix) noexcept {
    /* VkBool32 */  buffer << prefix << "Residency Aligned MIP Size :                              " <<  engine::VStandardUtils::constexprBoolAlpha( sparseProperties.residencyAlignedMipSize )                     << '\n';
    /* VkBool32 */  buffer << prefix << "Residency Non Resident Strict :                           " <<  engine::VStandardUtils::constexprBoolAlpha( sparseProperties.residencyNonResidentStrict )                  << '\n';
    /* VkBool32 */  buffer << prefix << "Residency Standard 2D Block Shape :                       " <<  engine::VStandardUtils::constexprBoolAlpha( sparseProperties.residencyStandard2DBlockShape )               << '\n';
    /* VkBool32 */  buffer << prefix << "Residency Standard 3D Block Shape :                       " <<  engine::VStandardUtils::constexprBoolAlpha( sparseProperties.residencyStandard3DBlockShape )               << '\n';
    /* VkBool32 */  buffer << prefix << "Residency Standard 2D Multisample Block Shape :           " <<  engine::VStandardUtils::constexprBoolAlpha( sparseProperties.residencyStandard2DMultisampleBlockShape )    << '\n';
}

#endif

#ifndef NDEBUG

void engine::VPhysicalDevice::debugPrintPhysicalDeviceLimitsStructure( const VulkanPhysicalDeviceLimits & limits, std::ostream & buffer,const char * prefix) noexcept {

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

void engine::VPhysicalDevice::debugPrintPhysicalDeviceFeaturesStructure( const VulkanPhysicalDeviceFeatures & features, std::ostream & buffer, const char * prefix) noexcept {
    /* VkBool32 */  buffer << prefix << "Robust Buffer Access :                                    " << engine::VStandardUtils::constexprBoolAlpha( features.robustBufferAccess )                         << '\n';
    /* VkBool32 */  buffer << prefix << "Full Draw Index Unsigned Integer 32 :                     " << engine::VStandardUtils::constexprBoolAlpha( features.fullDrawIndexUint32 )                        << '\n';
    /* VkBool32 */  buffer << prefix << "Image Cube Array :                                        " << engine::VStandardUtils::constexprBoolAlpha( features.imageCubeArray )                             << '\n';
    /* VkBool32 */  buffer << prefix << "Implement Blend :                                         " << engine::VStandardUtils::constexprBoolAlpha( features.independentBlend )                           << '\n';
    /* VkBool32 */  buffer << prefix << "Geometry Shader :                                         " << engine::VStandardUtils::constexprBoolAlpha( features.geometryShader )                             << '\n';
    /* VkBool32 */  buffer << prefix << "Tesselation Shader :                                      " << engine::VStandardUtils::constexprBoolAlpha( features.tessellationShader )                         << '\n';
    /* VkBool32 */  buffer << prefix << "Sample Rate Shading :                                     " << engine::VStandardUtils::constexprBoolAlpha( features.sampleRateShading )                          << '\n';
    /* VkBool32 */  buffer << prefix << "Dual Source Blend :                                       " << engine::VStandardUtils::constexprBoolAlpha( features.dualSrcBlend )                               << '\n';
    /* VkBool32 */  buffer << prefix << "Logic Operations :                                        " << engine::VStandardUtils::constexprBoolAlpha( features.logicOp )                                    << '\n';
    /* VkBool32 */  buffer << prefix << "Multi Draw Indirect :                                     " << engine::VStandardUtils::constexprBoolAlpha( features.multiDrawIndirect )                          << '\n';
    /* VkBool32 */  buffer << prefix << "Draw Indirect First Instance :                            " << engine::VStandardUtils::constexprBoolAlpha( features.drawIndirectFirstInstance )                  << '\n';
    /* VkBool32 */  buffer << prefix << "Depth Clamp :                                             " << engine::VStandardUtils::constexprBoolAlpha( features.depthClamp )                                 << '\n';
    /* VkBool32 */  buffer << prefix << "Depth Bias Clamp :                                        " << engine::VStandardUtils::constexprBoolAlpha( features.depthBiasClamp )                             << '\n';
    /* VkBool32 */  buffer << prefix << "Fill Mode Non Solid :                                     " << engine::VStandardUtils::constexprBoolAlpha( features.fillModeNonSolid )                           << '\n';
    /* VkBool32 */  buffer << prefix << "Depth Bounds :                                            " << engine::VStandardUtils::constexprBoolAlpha( features.depthBounds )                                << '\n';
    /* VkBool32 */  buffer << prefix << "Wide Lines :                                              " << engine::VStandardUtils::constexprBoolAlpha( features.wideLines )                                  << '\n';
    /* VkBool32 */  buffer << prefix << "Large Points :                                            " << engine::VStandardUtils::constexprBoolAlpha( features.largePoints )                                << '\n';
    /* VkBool32 */  buffer << prefix << "Alpha to One :                                            " << engine::VStandardUtils::constexprBoolAlpha( features.alphaToOne )                                 << '\n';
    /* VkBool32 */  buffer << prefix << "Multiple Viewports :                                      " << engine::VStandardUtils::constexprBoolAlpha( features.multiViewport )                              << '\n';
    /* VkBool32 */  buffer << prefix << "Sampler Anisotropy :                                      " << engine::VStandardUtils::constexprBoolAlpha( features.samplerAnisotropy )                          << '\n';
    /* VkBool32 */  buffer << prefix << "Texture Compression ETC2 :                                " << engine::VStandardUtils::constexprBoolAlpha( features.textureCompressionETC2 )                     << '\n';
    /* VkBool32 */  buffer << prefix << "Texture Compression ATSC_LDR :                            " << engine::VStandardUtils::constexprBoolAlpha( features.textureCompressionASTC_LDR )                 << '\n';
    /* VkBool32 */  buffer << prefix << "Texture Compression BC :                                  " << engine::VStandardUtils::constexprBoolAlpha( features.textureCompressionBC )                       << '\n';
    /* VkBool32 */  buffer << prefix << "Occlusion Query Precise :                                 " << engine::VStandardUtils::constexprBoolAlpha( features.occlusionQueryPrecise )                      << '\n';
    /* VkBool32 */  buffer << prefix << "Pipeline Statistics Query :                               " << engine::VStandardUtils::constexprBoolAlpha( features.pipelineStatisticsQuery )                    << '\n';
    /* VkBool32 */  buffer << prefix << "Vertex Pipeline Stores And Atomics :                      " << engine::VStandardUtils::constexprBoolAlpha( features.vertexPipelineStoresAndAtomics )             << '\n';
    /* VkBool32 */  buffer << prefix << "Fragment Stores and Atomics :                             " << engine::VStandardUtils::constexprBoolAlpha( features.fragmentStoresAndAtomics )                   << '\n';
    /* VkBool32 */  buffer << prefix << "Shader Tesselation and Geometry Point Size :              " << engine::VStandardUtils::constexprBoolAlpha( features.shaderTessellationAndGeometryPointSize )     << '\n';
    /* VkBool32 */  buffer << prefix << "Shader Image Gather Extended :                            " << engine::VStandardUtils::constexprBoolAlpha( features.shaderImageGatherExtended )                  << '\n';
    /* VkBool32 */  buffer << prefix << "Shader Storage Image Extended Formats :                   " << engine::VStandardUtils::constexprBoolAlpha( features.shaderStorageImageExtendedFormats )          << '\n';
    /* VkBool32 */  buffer << prefix << "Shader Storage Image Multisample :                        " << engine::VStandardUtils::constexprBoolAlpha( features.shaderStorageImageMultisample )              << '\n';
    /* VkBool32 */  buffer << prefix << "Shader Storage Image Read Without Format :                " << engine::VStandardUtils::constexprBoolAlpha( features.shaderStorageImageReadWithoutFormat )        << '\n';
    /* VkBool32 */  buffer << prefix << "Shader Storage Image Write Without Format :               " << engine::VStandardUtils::constexprBoolAlpha( features.shaderStorageImageWriteWithoutFormat )       << '\n';
    /* VkBool32 */  buffer << prefix << "Shader Uniform Buffer Array Dynamic Indexing :            " << engine::VStandardUtils::constexprBoolAlpha( features.shaderUniformBufferArrayDynamicIndexing )    << '\n';
    /* VkBool32 */  buffer << prefix << "Shader Sampled Image Array Dynamic Indexing :             " << engine::VStandardUtils::constexprBoolAlpha( features.shaderSampledImageArrayDynamicIndexing )     << '\n';
    /* VkBool32 */  buffer << prefix << "Shader Storage Buffer Array Dynamic Indexing :            " << engine::VStandardUtils::constexprBoolAlpha( features.shaderStorageBufferArrayDynamicIndexing )    << '\n';
    /* VkBool32 */  buffer << prefix << "Shader Storage Image Array Dynamic Indexing :             " << engine::VStandardUtils::constexprBoolAlpha( features.shaderStorageImageArrayDynamicIndexing )     << '\n';
    /* VkBool32 */  buffer << prefix << "Shader Clip Distance :                                    " << engine::VStandardUtils::constexprBoolAlpha( features.shaderClipDistance )                         << '\n';
    /* VkBool32 */  buffer << prefix << "Shader Cull Distance :                                    " << engine::VStandardUtils::constexprBoolAlpha( features.shaderCullDistance )                         << '\n';
    /* VkBool32 */  buffer << prefix << "Shader Float 64 :                                         " << engine::VStandardUtils::constexprBoolAlpha( features.shaderFloat64 )                              << '\n';
    /* VkBool32 */  buffer << prefix << "Shader Int 64 :                                           " << engine::VStandardUtils::constexprBoolAlpha( features.shaderInt64 )                                << '\n';
    /* VkBool32 */  buffer << prefix << "Shader Int 16 :                                           " << engine::VStandardUtils::constexprBoolAlpha( features.shaderInt16 )                                << '\n';
    /* VkBool32 */  buffer << prefix << "Shader Resource Residency :                               " << engine::VStandardUtils::constexprBoolAlpha( features.shaderResourceResidency )                    << '\n';
    /* VkBool32 */  buffer << prefix << "Shader Resource Min LOD :                                 " << engine::VStandardUtils::constexprBoolAlpha( features.shaderResourceMinLod )                       << '\n';
    /* VkBool32 */  buffer << prefix << "Sparse Binding :                                          " << engine::VStandardUtils::constexprBoolAlpha( features.sparseBinding )                              << '\n';
    /* VkBool32 */  buffer << prefix << "Sparse Residency Buffer :                                 " << engine::VStandardUtils::constexprBoolAlpha( features.sparseResidencyBuffer )                      << '\n';
    /* VkBool32 */  buffer << prefix << "Sparse Residency Image 2D :                               " << engine::VStandardUtils::constexprBoolAlpha( features.sparseResidencyImage2D )                     << '\n';
    /* VkBool32 */  buffer << prefix << "Sparse Residency Image 3D :                               " << engine::VStandardUtils::constexprBoolAlpha( features.sparseResidencyImage3D )                     << '\n';
    /* VkBool32 */  buffer << prefix << "Sparse Residency 2 Samples :                              " << engine::VStandardUtils::constexprBoolAlpha( features.sparseResidency2Samples )                    << '\n';
    /* VkBool32 */  buffer << prefix << "Sparse Residency 4 Samples :                              " << engine::VStandardUtils::constexprBoolAlpha( features.sparseResidency4Samples )                    << '\n';
    /* VkBool32 */  buffer << prefix << "Sparse Residency 8 Samples :                              " << engine::VStandardUtils::constexprBoolAlpha( features.sparseResidency8Samples )                    << '\n';
    /* VkBool32 */  buffer << prefix << "Sparse Residency 16 Samples :                             " << engine::VStandardUtils::constexprBoolAlpha( features.sparseResidency16Samples )                   << '\n';
    /* VkBool32 */  buffer << prefix << "Sparse Residency Aliased :                                " << engine::VStandardUtils::constexprBoolAlpha( features.sparseResidencyAliased )                     << '\n';
    /* VkBool32 */  buffer << prefix << "Variable Multisample Rate :                               " << engine::VStandardUtils::constexprBoolAlpha( features.variableMultisampleRate )                    << '\n';
    /* VkBool32 */  buffer << prefix << "Inherited Queries :                                       " << engine::VStandardUtils::constexprBoolAlpha( features.inheritedQueries )                           << '\n';
}

#endif