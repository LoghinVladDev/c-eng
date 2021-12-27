//
// Created by loghin on 26.12.2021.
//

#include "VulkanCore.hpp"

using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)

auto vulkan :: toString (
        vulkan :: __C_ENG_TYPE ( Result ) result
) noexcept -> cds :: StringLiteral {

    cds :: StringLiteral asString = "";

    switch ( result ) {

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE

        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultSuccess:                                     { asString = "Success";                                                                                                                                                                                                        break; }
        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultNotReady:                                    { asString = "Fence or Query not yet completed";                                                                                                                                                                               break; }
        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultTimeout:                                     { asString = "Waiting Operation did not complete in specified time";                                                                                                                                                           break; }
        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultEventSet:                                    { asString = "Event Signalled";                                                                                                                                                                                                break; }
        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultEventReset:                                  { asString = "Event Unsignalled";                                                                                                                                                                                              break; }
        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultIncomplete:                                  { asString = "Result is Incomplete, return array too small";                                                                                                                                                                   break; }
        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultErrorOutOfHostMemory:                        { asString = "Host Memory Allocation Failed";                                                                                                                                                                                  break; }
        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultErrorOutOfDeviceMemory:                      { asString = "Device Memory Allocation Failed";                                                                                                                                                                                break; }
        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultErrorInitializationFailed:                   { asString = "Vulkan Object Initialization could not be completed";                                                                                                                                                            break; }
        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultErrorDeviceLost:                             { asString = "Physical/Logical Device Lost. See https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/vkspec.html#devsandqueues-lost-device";                                                                      break; }
        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultErrorMemoryMapFailed:                        { asString = "Mapping of a memory object has failed";                                                                                                                                                                          break; }
        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultErrorLayerNotPresent:                        { asString = "Requested layer is not present / could not be loaded";                                                                                                                                                           break; }
        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultErrorFeatureNotPresent:                      { asString = "Requested feature is not supported";                                                                                                                                                                             break; }
        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultErrorIncompatibleDriver:                     { asString = "Requested version of Vulkan is not supported by the driver";                                                                                                                                                     break; }
        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultErrorTooManyObjects:                         { asString = "Too many objects of this type have been already created";                                                                                                                                                        break; }
        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultErrorFormatNotSupported:                     { asString = "Requested format not supported";                                                                                                                                                                                 break; }
        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultErrorFragmentedPool:                         { asString = "Pool Allocation Failed due to Fragmentation of the pool's memory";                                                                                                                                               break; }
        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultErrorUnknown:                                { asString = "Unknown Error, invalid input or implementation failure";                                                                                                                                                         break; }

#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultErrorOutOfPoolMemory:                        { asString = "Pool Allocation Failed due to lack of memory";                                                                                                                                                                   break; }
        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultErrorInvalidExternalHandle:                  { asString = "External Handle is not a valid Handle of the specified type";                                                                                                                                                    break; }

#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE

        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultErrorFragmentation:                          { asString = "Descriptor Pool Creation Failed due to Fragmentation";                                                                                                                                                           break; }
        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultErrorInvalidOpaqueCaptureAddress:            { asString = "Buffer Creation or Memory Allocation Failed because the requested address is not available. A shader group handle assignment failed because the requested shader group handle information is no longer valid";   break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SURFACE_AVAILABLE

        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultErrorSurfaceLost:                            { asString = "Surface is no longer available";                                                                                                                                                                                 break; }
        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultErrorNativeWindowInUse:                      { asString = "Requested Window is already in use by Vulkan or another API.";                                                                                                                                                   break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DISPLAY_SWAP_CHAIN_AVAILABLE

        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultErrorIncompatibleDisplay:                    { asString = "Display used by a swapchain does not use the same presentable image layout, or is incompatible in a way that prevents image sharing";                                                                            break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DEFERRED_HOST_OPERATIONS_AVAILABLE

        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultThreadIdle:                                  { asString = "Deferred operation is not complete, but there is no work for this thread to do at the time of this call";                                                                                                        break; }
        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultThreadDone:                                  { asString = "Deferred operation is not complete, but there is no work remaining to assign to additional threads";                                                                                                             break; }
        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultOperationDeferred:                           { asString = "Deferred operation requested and at least some work was deferred";                                                                                                                                               break; }
        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultOperationNotDeferred:                        { asString = "Deferred operation requested and no operation was deferred";                                                                                                                                                     break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_GLSL_SHADER_AVAILABLE

        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultErrorInvalidShader:                          { asString = "One or more shaders failed to compile or link";                                                                                                                                                                  break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEBUG_REPORT_AVAILABLE

        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultErrorValidationFailed:                       { asString = "Validation Layer Attachment Failed";                                                                                                                                                                             break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_DRM_FORMAT_MODIFIER_AVAILABLE

        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultErrorInvalidDRMFormatModifierPlaneLayout:    { asString = "Tiling layout provided to application did not match external image layout";                                                                                                                                      break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GLOBAL_PRIORITY_AVAILABLE

        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultErrorNotPermitted:                           { asString = "Driver Denied Request due to System Resource Starvation";                                                                                                                                                        break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FULL_SCREEN_EXCLUSIVE_AVAILABLE

        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultErrorFullScreenExclusiveModeLost:            { asString = "Operation Failed due to not having exclusive full-screen access";                                                                                                                                                break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_CACHE_CONTROL_AVAILABLE

        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultPipelineCompileRequired:                     { asString = "Requested Pipeline Creation would have required compilation, but the application requested that compilation not be performed";                                                                                   break; }

#endif

        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultUnknown:                                     { asString = "Unknown/Not Documented Result";                                                                                                                                                                                  break; }
    }

    return asString;
}