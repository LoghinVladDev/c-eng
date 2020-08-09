//
// Created by vladl on 07/08/2020.
//

#include "VStdUtils.h"
#include "VStdUtilsDefs.h"

std::string engine::VStandardUtils::to_string(VulkanResult result) noexcept {
    switch (result) {

        case VK_SUCCESS:                                            return std::string (__VK_SUCCESS_STR);
        case VK_NOT_READY:                                          return std::string (__VK_NOT_READY);
        case VK_TIMEOUT:                                            return std::string (__VK_TIMEOUT);
        case VK_EVENT_SET:                                          return std::string (__VK_EVENT_SET);
        case VK_EVENT_RESET:                                        return std::string (__VK_EVENT_RESET);
        case VK_INCOMPLETE:                                         return std::string (__VK_INCOMPLETE);
        case VK_ERROR_OUT_OF_HOST_MEMORY:                           return std::string (__VK_ERROR_OUT_OF_HOST_MEMORY);
        case VK_ERROR_OUT_OF_DEVICE_MEMORY:                         return std::string (__VK_ERROR_OUT_OF_DEVICE_MEMORY);
        case VK_ERROR_INITIALIZATION_FAILED:                        return std::string (__VK_ERROR_INITIALIZATION_FAILED);
        case VK_ERROR_DEVICE_LOST:                                  return std::string (__VK_ERROR_DEVICE_LOST);
        case VK_ERROR_MEMORY_MAP_FAILED:                            return std::string (__VK_ERROR_MEMORY_MAP_FAILED);
        case VK_ERROR_LAYER_NOT_PRESENT:                            return std::string (__VK_ERROR_LAYER_NOT_PRESENT);
        case VK_ERROR_EXTENSION_NOT_PRESENT:                        return std::string (__VK_ERROR_EXTENSION_NOT_PRESENT);
        case VK_ERROR_FEATURE_NOT_PRESENT:                          return std::string (__VK_ERROR_FEATURE_NOT_PRESENT);
        case VK_ERROR_INCOMPATIBLE_DRIVER:                          return std::string (__VK_ERROR_INCOMPATIBLE_DRIVER);
        case VK_ERROR_TOO_MANY_OBJECTS:                             return std::string (__VK_ERROR_TOO_MANY_OBJECTS);
        case VK_ERROR_FORMAT_NOT_SUPPORTED:                         return std::string (__VK_ERROR_FORMAT_NOT_SUPPORTED);
        case VK_ERROR_FRAGMENTED_POOL:                              return std::string (__VK_ERROR_FRAGMENTED_POOL);
        case VK_ERROR_OUT_OF_POOL_MEMORY:                           return std::string (__VK_ERROR_OUT_OF_POOL_MEMORY);
        case VK_ERROR_INVALID_EXTERNAL_HANDLE:                      return std::string (__VK_ERROR_INVALID_EXTERNAL_HANDLE);
        case VK_ERROR_FRAGMENTATION:                                return std::string (__VK_ERROR_FRAGMENTATION);
        case VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS:               return std::string (__VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS);
        case VK_ERROR_SURFACE_LOST_KHR:                             return std::string (__VK_ERROR_SURFACE_LOST_KHR);
        case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:                     return std::string (__VK_ERROR_NATIVE_WINDOW_IN_USE_KHR);
        case VK_SUBOPTIMAL_KHR:                                     return std::string (__VK_SUBOPTIMAL_KHR);
        case VK_ERROR_OUT_OF_DATE_KHR:                              return std::string (__VK_ERROR_OUT_OF_DATE_KHR);
        case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:                     return std::string (__VK_ERROR_INCOMPATIBLE_DISPLAY_KHR);
        case VK_ERROR_VALIDATION_FAILED_EXT:                        return std::string (__VK_ERROR_VALIDATION_FAILED_EXT);
        case VK_ERROR_INVALID_SHADER_NV:                            return std::string (__VK_ERROR_INVALID_SHADER_NV);
        case VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT: return std::string (__VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT);
        case VK_ERROR_NOT_PERMITTED_EXT:                            return std::string (__VK_ERROR_NOT_PERMITTED_EXT);
        case VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT:          return std::string (__VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT);
//        case VK_RESULT_RANGE_SIZE:                                  return std::string (__VK_RESULT_RANGE_SIZE); not on all platforms
        case VK_RESULT_MAX_ENUM:                                    return std::string (__VK_RESULT_MAX_ENUM);

        case VK_ERROR_UNKNOWN:
        default:                                                    return std::string (__VK_ERROR_UNKNOWN);
            
    }
}

std::string engine::VStandardUtils::to_string(VulkanPhysicalDeviceType deviceType) noexcept {
    switch ( deviceType ) {

        case VK_PHYSICAL_DEVICE_TYPE_OTHER:                         return std::string(__VK_PHYSICAL_DEVICE_OTHER);
        case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:                return std::string(__VK_PHYSICAL_DEVICE_INTEGRATED_GPU);
        case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:                  return std::string(__VK_PHYSICAL_DEVICE_DISCRETE_GPU);
        case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:                   return std::string(__VK_PHYSICAL_DEVICE_VIRTUAL_GPU);
        case VK_PHYSICAL_DEVICE_TYPE_CPU:                           return std::string(__VK_PHYSICAL_DEVICE_CPU);
//        case VK_PHYSICAL_DEVICE_TYPE_RANGE_SIZE:                    return std::string(__VK_PHYSICAL_DEVICE_TYPE_RANGE_SIZE); not on all platforms
        case VK_PHYSICAL_DEVICE_TYPE_MAX_ENUM:                      return std::string(__VK_PHYSICAL_DEVICE_TYPE_MAX_ENUM);

        default :                                                   return std::string(__VK_PHYSICAL_DEVICE_UNKNOWN);
    }
}
