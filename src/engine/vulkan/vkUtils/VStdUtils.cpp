//
// Created by vladl on 07/08/2020.
//

#include "VStdUtils.hpp"
#include "VStdUtilsDefs.h"

using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)

__CDS_MaybeUnused constexpr static auto constexprVulkanVersionCheck (
        int version,
        int required
) noexcept -> bool {

    return version >= required;
}

auto VStandardUtils :: toString(
        VulkanResult result
) noexcept -> String {

    switch (result) {
        case VK_SUCCESS:                                            return __VK_SUCCESS_STR;                                            // NOLINT(clion-misra-cpp2008-6-4-5)
        case VK_NOT_READY:                                          return __VK_NOT_READY;                                              // NOLINT(clion-misra-cpp2008-6-4-5)
        case VK_TIMEOUT:                                            return __VK_TIMEOUT;                                                // NOLINT(clion-misra-cpp2008-6-4-5)
        case VK_EVENT_SET:                                          return __VK_EVENT_SET;                                              // NOLINT(clion-misra-cpp2008-6-4-5)
        case VK_EVENT_RESET:                                        return __VK_EVENT_RESET;                                            // NOLINT(clion-misra-cpp2008-6-4-5)
        case VK_INCOMPLETE:                                         return __VK_INCOMPLETE;                                             // NOLINT(clion-misra-cpp2008-6-4-5)
        case VK_ERROR_OUT_OF_HOST_MEMORY:                           return __VK_ERROR_OUT_OF_HOST_MEMORY;                               // NOLINT(clion-misra-cpp2008-6-4-5)
        case VK_ERROR_OUT_OF_DEVICE_MEMORY:                         return __VK_ERROR_OUT_OF_DEVICE_MEMORY;                             // NOLINT(clion-misra-cpp2008-6-4-5)
        case VK_ERROR_INITIALIZATION_FAILED:                        return __VK_ERROR_INITIALIZATION_FAILED;                            // NOLINT(clion-misra-cpp2008-6-4-5)
        case VK_ERROR_DEVICE_LOST:                                  return __VK_ERROR_DEVICE_LOST;                                      // NOLINT(clion-misra-cpp2008-6-4-5)
        case VK_ERROR_MEMORY_MAP_FAILED:                            return __VK_ERROR_MEMORY_MAP_FAILED;                                // NOLINT(clion-misra-cpp2008-6-4-5)
        case VK_ERROR_LAYER_NOT_PRESENT:                            return __VK_ERROR_LAYER_NOT_PRESENT;                                // NOLINT(clion-misra-cpp2008-6-4-5)
        case VK_ERROR_EXTENSION_NOT_PRESENT:                        return __VK_ERROR_EXTENSION_NOT_PRESENT;                            // NOLINT(clion-misra-cpp2008-6-4-5)
        case VK_ERROR_FEATURE_NOT_PRESENT:                          return __VK_ERROR_FEATURE_NOT_PRESENT;                              // NOLINT(clion-misra-cpp2008-6-4-5)
        case VK_ERROR_INCOMPATIBLE_DRIVER:                          return __VK_ERROR_INCOMPATIBLE_DRIVER;                              // NOLINT(clion-misra-cpp2008-6-4-5)
        case VK_ERROR_TOO_MANY_OBJECTS:                             return __VK_ERROR_TOO_MANY_OBJECTS;                                 // NOLINT(clion-misra-cpp2008-6-4-5)
        case VK_ERROR_FORMAT_NOT_SUPPORTED:                         return __VK_ERROR_FORMAT_NOT_SUPPORTED;                             // NOLINT(clion-misra-cpp2008-6-4-5)
        case VK_ERROR_FRAGMENTED_POOL:                              return __VK_ERROR_FRAGMENTED_POOL;                                  // NOLINT(clion-misra-cpp2008-6-4-5)
        case VK_ERROR_OUT_OF_POOL_MEMORY:                           return __VK_ERROR_OUT_OF_POOL_MEMORY;                               // NOLINT(clion-misra-cpp2008-6-4-5)
        case VK_ERROR_INVALID_EXTERNAL_HANDLE:                      return __VK_ERROR_INVALID_EXTERNAL_HANDLE;                          // NOLINT(clion-misra-cpp2008-6-4-5)
#if VK_HEADER_VERSION >= 131
        case VK_ERROR_FRAGMENTATION:                                return __VK_ERROR_FRAGMENTATION;                                    // NOLINT(clion-misra-cpp2008-6-4-5)
#else
        case VK_ERROR_FRAGMENTATION_EXT:                            return __VK_ERROR_FRAGMENTATION;                                    // NOLINT(clion-misra-cpp2008-6-4-5)
#endif
#if VK_HEADER_VERSION >= 131
        case VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS:               return __VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS;                   // NOLINT(clion-misra-cpp2008-6-4-5)
#endif                                                                                                                                  // NOLINT(clion-misra-cpp2008-6-4-5)
        case VK_ERROR_SURFACE_LOST_KHR:                             return __VK_ERROR_SURFACE_LOST_KHR;                                 // NOLINT(clion-misra-cpp2008-6-4-5)
        case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:                     return __VK_ERROR_NATIVE_WINDOW_IN_USE_KHR;                         // NOLINT(clion-misra-cpp2008-6-4-5)
        case VK_SUBOPTIMAL_KHR:                                     return __VK_SUBOPTIMAL_KHR;                                         // NOLINT(clion-misra-cpp2008-6-4-5)
        case VK_ERROR_OUT_OF_DATE_KHR:                              return __VK_ERROR_OUT_OF_DATE_KHR;                                  // NOLINT(clion-misra-cpp2008-6-4-5)
        case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:                     return __VK_ERROR_INCOMPATIBLE_DISPLAY_KHR;                         // NOLINT(clion-misra-cpp2008-6-4-5)
        case VK_ERROR_VALIDATION_FAILED_EXT:                        return __VK_ERROR_VALIDATION_FAILED_EXT;                            // NOLINT(clion-misra-cpp2008-6-4-5)
        case VK_ERROR_INVALID_SHADER_NV:                            return __VK_ERROR_INVALID_SHADER_NV;                                // NOLINT(clion-misra-cpp2008-6-4-5)
        case VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT: return __VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT;     // NOLINT(clion-misra-cpp2008-6-4-5)
        case VK_ERROR_NOT_PERMITTED_EXT:                            return __VK_ERROR_NOT_PERMITTED_EXT;                                // NOLINT(clion-misra-cpp2008-6-4-5)
        case VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT:          return __VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT;              // NOLINT(clion-misra-cpp2008-6-4-5)
//        case VK_RESULT_RANGE_SIZE:                                  return std::string (__VK_RESULT_RANGE_SIZE); not on all platforms
        case VK_RESULT_MAX_ENUM:                                    return __VK_RESULT_MAX_ENUM;                                        // NOLINT(clion-misra-cpp2008-6-4-5)
#if VK_HEADER_VERSION >= 131
        case VK_ERROR_UNKNOWN:
#endif
        default:                                                    return __VK_ERROR_UNKNOWN;                                          // NOLINT(clion-misra-cpp2008-6-4-5)
            
    }
}

auto VStandardUtils :: toString (
        VulkanPhysicalDeviceType deviceType
) noexcept -> String {

    switch ( deviceType ) {

        case VK_PHYSICAL_DEVICE_TYPE_OTHER:                         return __VK_PHYSICAL_DEVICE_OTHER;                                  // NOLINT(clion-misra-cpp2008-6-4-5)
        case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:                return __VK_PHYSICAL_DEVICE_INTEGRATED_GPU;                         // NOLINT(clion-misra-cpp2008-6-4-5)
        case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:                  return __VK_PHYSICAL_DEVICE_DISCRETE_GPU;                           // NOLINT(clion-misra-cpp2008-6-4-5)
        case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:                   return __VK_PHYSICAL_DEVICE_VIRTUAL_GPU;                            // NOLINT(clion-misra-cpp2008-6-4-5)
        case VK_PHYSICAL_DEVICE_TYPE_CPU:                           return __VK_PHYSICAL_DEVICE_CPU;                                    // NOLINT(clion-misra-cpp2008-6-4-5)
//        case VK_PHYSICAL_DEVICE_TYPE_RANGE_SIZE:                    return std::string(__VK_PHYSICAL_DEVICE_TYPE_RANGE_SIZE); not on all platforms
        case VK_PHYSICAL_DEVICE_TYPE_MAX_ENUM:                      return __VK_PHYSICAL_DEVICE_TYPE_MAX_ENUM;                          // NOLINT(clion-misra-cpp2008-6-4-5)

        default :                                                   return __VK_PHYSICAL_DEVICE_UNKNOWN;                                // NOLINT(clion-misra-cpp2008-6-4-5)
    }
}

auto VStandardUtils :: getGLFWRequiredExtensions (
        bool enableValidationLayers
) noexcept -> std :: vector < GLFWExtensionLiteral > {

    cds :: uint32               glfwExtensionsCount = 0U;
    GLFWExtensionLiteralArray   glfwExtensions;

    glfwExtensions = glfwGetRequiredInstanceExtensions( & glfwExtensionsCount );
    std::vector < GLFWExtensionLiteral > extensions ( glfwExtensions, glfwExtensions + glfwExtensionsCount );

    if( enableValidationLayers ) {
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    return extensions;
}
