#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-reserved-identifier"
//
// Created by vladl on 07/08/2020.
//

#ifndef ENG1_VSTDUTILSDEFS_H
#define ENG1_VSTDUTILSDEFS_H

/**
 * to_string ( VulkanResult ) defs
 */
#define __VK_SUCCESS_STR                                        "Vulkan : Success"
#define __VK_NOT_READY                                          "Vulkan : Not Ready"
#define __VK_TIMEOUT                                            "Vulkan : Timeout"
#define __VK_EVENT_SET                                          "Vulkan : Event Set"
#define __VK_EVENT_RESET                                        "Vulkan : Event Reset"
#define __VK_INCOMPLETE                                         "Vulkan : Incomplete"
#define __VK_ERROR_OUT_OF_HOST_MEMORY                           "Vulkan : Error : Out of Host Memory"
#define __VK_ERROR_OUT_OF_DEVICE_MEMORY                         "Vulkan : Error : Out of Device Memory"
#define __VK_ERROR_INITIALIZATION_FAILED                        "Vulkan : Error : Initialization Failed"
#define __VK_ERROR_DEVICE_LOST                                  "Vulkan : Error : Device Lost"
#define __VK_ERROR_MEMORY_MAP_FAILED                            "Vulkan : Error : Memory Map Failed"
#define __VK_ERROR_LAYER_NOT_PRESENT                            "Vulkan : Error : Layer not Present"
#define __VK_ERROR_EXTENSION_NOT_PRESENT                        "Vulkan : Error : Extension not Present"
#define __VK_ERROR_FEATURE_NOT_PRESENT                          "Vulkan : Error : Feature not Present"
#define __VK_ERROR_INCOMPATIBLE_DRIVER                          "Vulkan : Error : Incompatible Driver"
#define __VK_ERROR_TOO_MANY_OBJECTS                             "Vulkan : Error : Too Many Objects"
#define __VK_ERROR_FORMAT_NOT_SUPPORTED                         "Vulkan : Error : Format not Supported"
#define __VK_ERROR_FRAGMENTED_POOL                              "Vulkan : Error : Fragmented Pool"
#define __VK_ERROR_UNKNOWN                                      "Vulkan : Error : Unknown. Too Bad!"
#define __VK_ERROR_OUT_OF_POOL_MEMORY                           "Vulkan : Error : Out of Memory Pool"
#define __VK_ERROR_INVALID_EXTERNAL_HANDLE                      "Vulkan : Error : Invalid External Handle"
#define __VK_ERROR_FRAGMENTATION                                "Vulkan : Error : Fragmentation"
#define __VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS               "Vulkan : Error : Invalid Opaque Capture Address"
#define __VK_ERROR_SURFACE_LOST_KHR                             "Vulkan : Error : Khronos : Surface Lost"
#define __VK_ERROR_NATIVE_WINDOW_IN_USE_KHR                     "Vulkan : Error : Khronos : Native Window in Use"
#define __VK_SUBOPTIMAL_KHR                                     "Vulkan : Suboptimal : Khronos"
#define __VK_ERROR_OUT_OF_DATE_KHR                              "Vulkan : Error : Khronos : Out of Date Khronos"
#define __VK_ERROR_INCOMPATIBLE_DISPLAY_KHR                     "Vulkan : Error : Khronos : Incompatible Display"
#define __VK_ERROR_VALIDATION_FAILED_EXT                        "Vulkan : Error : Extension : Validation Failed"
#define __VK_ERROR_INVALID_SHADER_NV                            "Vulkan : Error : Nvidia : Invalid Shader"
#define __VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT "Vulkan : Error : Extension : Invalid DRM Format Modifier Plane Layout"
#define __VK_ERROR_NOT_PERMITTED_EXT                            "Vulkan : Error : Extension : Not Permitted"
#define __VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT          "Vulkan : Error : Extension : Fullscreen Exclusive Mode Lost"
#define __VK_RESULT_RANGE_SIZE                                  "Vulkan : Result Range Size"
#define __VK_RESULT_MAX_ENUM                                    "Vulkan : Result Max Enum Value"

/**
 * to_string ( VulkanPhysicalDeviceType ) defs
 */
#define __VK_PHYSICAL_DEVICE_OTHER                              "Vulkan Physical Device : Other"
#define __VK_PHYSICAL_DEVICE_INTEGRATED_GPU                     "Vulkan Physical Device : Integrated GPU"
#define __VK_PHYSICAL_DEVICE_DISCRETE_GPU                       "Vulkan Physical Device : Discrete GPU"
#define __VK_PHYSICAL_DEVICE_VIRTUAL_GPU                        "Vulkan Physical Device : Virtual GPU"
#define __VK_PHYSICAL_DEVICE_CPU                                "Vulkan Physical Device : CPU"
#define __VK_PHYSICAL_DEVICE_TYPE_RANGE_SIZE                    "Vulkan Physical Device Range Size"
#define __VK_PHYSICAL_DEVICE_TYPE_MAX_ENUM                      "Vulkan Physical Device Max Enum Value"
#define __VK_PHYSICAL_DEVICE_UNKNOWN                            "Vulkan Physical Device Unknown"

#define ENG_RETURN_IF_NOT_SUCCESS(_fCall) \
{ \
    VulkanResult result = _fCall; \
    if ( result != VulkanResult::VK_SUCCESS ) \
        return result;                  \
}

#define ENG_RETURN_IF_NOT_SUCCESS_2(_fCall, _beforeReturn) \
{ \
    VulkanResult result = _fCall; \
    if ( result != VulkanResult::VK_SUCCESS ) { \
        _beforeReturn;                                   \
        return result;                                   \
    }\
}

#define ENG_THROW_IF_NOT_SUCCESS(_fCall, _throw) \
{                                                   \
    if ( _fCall != VulkanResult::VK_SUCCESS )      \
        throw _throw;                              \
}

#endif //ENG1_VSTDUTILSDEFS_H

#pragma clang diagnostic pop