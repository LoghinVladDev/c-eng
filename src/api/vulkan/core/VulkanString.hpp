//
// Created by loghin on 19.04.2025.
//

#pragma once

#include <cds/StringView>

namespace vk {
#ifdef VK_VERSION_1_0
constexpr auto toString(VkResult const result) noexcept -> cds::StringView {
  switch (result) {
    case VK_SUCCESS: return "VK_SUCCESS";
    case VK_NOT_READY: return "VK_NOT_READY";
    case VK_TIMEOUT: return "VK_TIMEOUT";
    case VK_EVENT_SET: return "VK_EVENT_SET";
    case VK_EVENT_RESET: return "VK_EVENT_RESET";
    case VK_INCOMPLETE: return "VK_INCOMPLETE";
    case VK_ERROR_OUT_OF_HOST_MEMORY: return "VK_ERROR_OUT_OF_HOST_MEMORY";
    case VK_ERROR_OUT_OF_DEVICE_MEMORY: return "VK_ERROR_OUT_OF_DEVICE_MEMORY";
    case VK_ERROR_INITIALIZATION_FAILED: return "VK_ERROR_INITIALIZATION_FAILED";
    case VK_ERROR_DEVICE_LOST: return "VK_ERROR_DEVICE_LOST";
    case VK_ERROR_MEMORY_MAP_FAILED: return "VK_ERROR_MEMORY_MAP_FAILED";
    case VK_ERROR_LAYER_NOT_PRESENT: return "VK_ERROR_LAYER_NOT_PRESENT";
    case VK_ERROR_EXTENSION_NOT_PRESENT: return "VK_ERROR_EXTENSION_NOT_PRESENT";
    case VK_ERROR_FEATURE_NOT_PRESENT: return "VK_ERROR_FEATURE_NOT_PRESENT";
    case VK_ERROR_INCOMPATIBLE_DRIVER: return "VK_ERROR_INCOMPATIBLE_DRIVER";
    case VK_ERROR_TOO_MANY_OBJECTS: return "VK_ERROR_TOO_MANY_OBJECTS";
    case VK_ERROR_FORMAT_NOT_SUPPORTED: return "VK_ERROR_FORMAT_NOT_SUPPORTED";
    case VK_ERROR_FRAGMENTED_POOL: return "VK_ERROR_FRAGMENTED_POOL";
    case VK_ERROR_UNKNOWN: return "VK_ERROR_UNKNOWN";
#ifdef VK_VERSION_1_1
    case VK_ERROR_OUT_OF_POOL_MEMORY: return "VK_ERROR_OUT_OF_POOL_MEMORY";
    case VK_ERROR_INVALID_EXTERNAL_HANDLE: return "VK_ERROR_INVALID_EXTERNAL_HANDLE";
#endif
#ifdef VK_VERSION_1_2
    case VK_ERROR_FRAGMENTATION: return "VK_ERROR_FRAGMENTATION";
    case VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS: return "VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS";
#endif
#ifdef VK_VERSION_1_3
    case VK_PIPELINE_COMPILE_REQUIRED: return "VK_PIPELINE_COMPILE_REQUIRED";
#endif
#ifdef VK_VERSION_1_4
    case VK_ERROR_NOT_PERMITTED: return "VK_ERROR_NOT_PERMITTED";
#endif
#ifdef VK_KHR_surface
    case VK_ERROR_SURFACE_LOST_KHR: return "VK_ERROR_SURFACE_LOST_KHR";
    case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR: return "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR";
#endif
#ifdef VK_KHR_swapchain
    case VK_SUBOPTIMAL_KHR: return "VK_SUBOPTIMAL_KHR";
    case VK_ERROR_OUT_OF_DATE_KHR: return "VK_ERROR_OUT_OF_DATE_KHR";
#endif
#ifdef VK_KHR_display_swapchain
    case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR: return "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR";
#endif
#ifdef VK_EXT_debug_report
    case VK_ERROR_VALIDATION_FAILED_EXT: return "VK_ERROR_VALIDATION_FAILED_EXT";
#endif
#ifdef VK_NV_glsl_shader
    case VK_ERROR_INVALID_SHADER_NV: return "VK_ERROR_INVALID_SHADER_NV";
#endif
#ifdef VK_KHR_video_queue
    case VK_ERROR_IMAGE_USAGE_NOT_SUPPORTED_KHR: return "VK_ERROR_IMAGE_USAGE_NOT_SUPPORTED_KHR";
    case VK_ERROR_VIDEO_PICTURE_LAYOUT_NOT_SUPPORTED_KHR: return "VK_ERROR_VIDEO_PICTURE_LAYOUT_NOT_SUPPORTED_KHR";
    case VK_ERROR_VIDEO_PROFILE_OPERATION_NOT_SUPPORTED_KHR: return "VK_ERROR_VIDEO_PROFILE_OPERATION_NOT_SUPPORTED_KHR";
    case VK_ERROR_VIDEO_PROFILE_FORMAT_NOT_SUPPORTED_KHR: return "VK_ERROR_VIDEO_PROFILE_FORMAT_NOT_SUPPORTED_KHR";
    case VK_ERROR_VIDEO_PROFILE_CODEC_NOT_SUPPORTED_KHR: return "VK_ERROR_VIDEO_PROFILE_CODEC_NOT_SUPPORTED_KHR";
    case VK_ERROR_VIDEO_STD_VERSION_NOT_SUPPORTED_KHR: return "VK_ERROR_VIDEO_STD_VERSION_NOT_SUPPORTED_KHR";
#endif
#ifdef VK_EXT_image_drm_format_modifier
      case VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT: return "VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT";
#endif
#ifdef VK_EXT_full_screen_exclusive
    case VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT: return "VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT";
#endif
#ifdef VK_KHR_deferred_host_operations
    case VK_THREAD_IDLE_KHR: return "VK_THREAD_IDLE_KHR";
    case VK_THREAD_DONE_KHR: return "VK_THREAD_DONE_KHR";
    case VK_OPERATION_NOT_DEFERRED_KHR: return "VK_OPERATION_NOT_DEFERRED_KHR";
#endif
#ifdef VK_KHR_video_encode_queue
    case VK_ERROR_INVALID_VIDEO_STD_PARAMETERS_KHR: return "VK_ERROR_INVALID_VIDEO_STD_PARAMETERS_KHR";
#endif
#ifdef VK_EXT_image_compression_control
    case VK_ERROR_COMPRESSION_EXHAUSTED_EXT: return "VK_ERROR_COMPRESSION_EXHAUSTED_EXT";
#endif
#ifdef VK_EXT_shader_object
    case VK_INCOMPATIBLE_SHADER_BINARY_EXT: return "VK_INCOMPATIBLE_SHADER_BINARY_EXT";
#endif
#ifdef VK_KHR_pipeline_binary
    case VK_PIPELINE_BINARY_MISSING_KHR: return "VK_PIPELINE_BINARY_MISSING_KHR";
    case VK_ERROR_NOT_ENOUGH_SPACE_KHR: return "VK_ERROR_NOT_ENOUGH_SPACE_KHR";
#endif
#if !defined(VK_VERSION_1_1) && defined(VK_KHR_maintenance1)
    case VK_ERROR_OUT_OF_POOL_MEMORY_KHR: return "VK_ERROR_OUT_OF_POOL_MEMORY_KHR";
#endif
#if !defined(VK_VERSION_1_1) && defined(VK_KHR_external_memory)
    case VK_ERROR_OUT_OF_POOL_MEMORY_KHR: return "VK_ERROR_OUT_OF_POOL_MEMORY_KHR";
#endif
#if !defined(VK_VERSION_1_2) && defined(VK_EXT_descriptor_indexing)
    case VK_ERROR_FRAGMENTATION_EXT: return "VK_ERROR_FRAGMENTATION_EXT";
#endif
#if !defined(VK_VERSION_1_2) && defined(VK_EXT_buffer_device_address)
    case VK_ERROR_INVALID_DEVICE_ADDRESS_EXT: return "VK_ERROR_INVALID_DEVICE_ADDRESS_EXT";
#endif
#if !defined(VK_VERSION_1_2) && defined(VK_KHR_buffer_device_address)
    case VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS_KHR: return "VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS_KHR";
#endif
#if !defined(VK_VERSION_1_3) && defined(VK_EXT_pipeline_creation_cache_control)
    case VK_PIPELINE_COMPILE_REQUIRED_EXT: return "VK_PIPELINE_COMPILE_REQUIRED_EXT";
    case VK_ERROR_PIPELINE_COMPILE_REQUIRED_EXT: return "VK_ERROR_PIPELINE_COMPILE_REQUIRED_EXT";
#endif
#if !defined(VK_VERSION_1_4) && defined(VK_EXT_global_priority)
    case VK_ERROR_NOT_PERMITTED_EXT: return "VK_ERROR_NOT_PERMITTED_EXT";
#endif
#if !defined(VK_VERSION_1_4) && defined(VK_KHR_global_priority)
    case VK_ERROR_NOT_PERMITTED_KHR: return "VK_ERROR_NOT_PERMITTED_KHR";
#endif
    default:
      assert(false && "Unhandled VkResult case");
      cds::impl::unreachable();
  }
}

constexpr auto toString(VkSystemAllocationScope const scope) noexcept -> cds::StringView {
  switch (scope) {
    case VK_SYSTEM_ALLOCATION_SCOPE_COMMAND: return "VK_SYSTEM_ALLOCATION_SCOPE_COMMAND";
    case VK_SYSTEM_ALLOCATION_SCOPE_OBJECT: return "VK_SYSTEM_ALLOCATION_SCOPE_OBJECT";
    case VK_SYSTEM_ALLOCATION_SCOPE_CACHE: return "VK_SYSTEM_ALLOCATION_SCOPE_CACHE";
    case VK_SYSTEM_ALLOCATION_SCOPE_DEVICE: return "VK_SYSTEM_ALLOCATION_SCOPE_DEVICE";
    case VK_SYSTEM_ALLOCATION_SCOPE_INSTANCE: return "VK_SYSTEM_ALLOCATION_SCOPE_INSTANCE";
    default:
      assert(false && "Unhandled VkSystemAllocationScope case");
      cds::impl::unreachable();
  }
}

constexpr auto toString(VkInternalAllocationType const scope) noexcept -> cds::StringView {
  switch (scope) {
    case VK_INTERNAL_ALLOCATION_TYPE_EXECUTABLE: return "VK_INTERNAL_ALLOCATION_TYPE_EXECUTABLE";
    default:
      assert(false && "Unhandled VkInternalAllocationType case");
      cds::impl::unreachable();
  }
}

constexpr auto toString(VkQueueFlagBits const flag, bool const alternate = false) noexcept -> cds::StringView {
  if (alternate) {
    switch (flag) {
      case VK_QUEUE_GRAPHICS_BIT: return "Graphics";
      case VK_QUEUE_COMPUTE_BIT: return "Compute";
      case VK_QUEUE_TRANSFER_BIT: return "Transfer";
      case VK_QUEUE_SPARSE_BINDING_BIT: return "Sparse Binding";

#ifdef VK_VERSION_1_1
      case VK_QUEUE_PROTECTED_BIT: return "Protected";
#endif

#ifdef VK_KHR_video_decode_queue
      case VK_QUEUE_VIDEO_DECODE_BIT_KHR: return "Video Decode";
#endif

#ifdef VK_KHR_video_encode_queue
      case VK_QUEUE_VIDEO_ENCODE_BIT_KHR: return "Video Encode";
#endif

#ifdef VK_NV_optical_flow
      case VK_QUEUE_OPTICAL_FLOW_BIT_NV: return "Optical Flow";
#endif

      default:
        assert(false && "Unhandled VkQueueFlagBits case");
        cds::impl::unreachable();
    }
  }

  switch (flag) {
    case VK_QUEUE_GRAPHICS_BIT: return "VK_QUEUE_GRAPHICS_BIT";
    case VK_QUEUE_COMPUTE_BIT: return "VK_QUEUE_COMPUTE_BIT";
    case VK_QUEUE_TRANSFER_BIT: return "VK_QUEUE_TRANSFER_BIT";
    case VK_QUEUE_SPARSE_BINDING_BIT: return "VK_QUEUE_SPARSE_BINDING_BIT";

#ifdef VK_VERSION_1_1
    case VK_QUEUE_PROTECTED_BIT: return "VK_QUEUE_PROTECTED_BIT";
#endif

#ifdef VK_KHR_video_decode_queue
    case VK_QUEUE_VIDEO_DECODE_BIT_KHR: return "VK_QUEUE_VIDEO_DECODE_BIT_KHR";
#endif

#ifdef VK_KHR_video_encode_queue
    case VK_QUEUE_VIDEO_ENCODE_BIT_KHR: return "VK_QUEUE_VIDEO_ENCODE_BIT_KHR";
#endif

#ifdef VK_NV_optical_flow
    case VK_QUEUE_OPTICAL_FLOW_BIT_NV: return "VK_QUEUE_OPTICAL_FLOW_BIT_NV";
#endif

    default:
      assert(false && "Unhandled VkQueueFlagBits case");
      cds::impl::unreachable();
  }
}
#endif // #ifdef VK_VERSION_1_0

#ifdef VK_EXT_debug_utils
constexpr auto toString(VkDebugUtilsMessageSeverityFlagBitsEXT const flag, bool const alternate = false) noexcept
    -> cds::StringView {
  if (alternate) {
    switch (flag) {
      case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT: return "Verbose";
      case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:    return "Info";
      case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT: return "Warning";
      case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:   return "Error";
      default:
        assert(false && "Unhandled VkDebugUtilsMessageSeverityFlagBitsEXT case");
        cds::impl::unreachable();
    }
  }

  switch (flag) {
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT: return "VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT";
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:    return "VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT";
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT: return "VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT";
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:   return "VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT";
    default:
      assert(false && "Unhandled VkDebugUtilsMessageSeverityFlagBitsEXT case");
      cds::impl::unreachable();
  }
}

constexpr auto toString(VkDebugUtilsMessageTypeFlagBitsEXT const flag, bool const alternate = false) noexcept
    -> cds::StringView {
  if (alternate) {
    switch (flag) {
      case VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT: return "General";
      case VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT: return "Validation";
      case VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT: return "Performance";
#ifdef VK_EXT_device_address_binding_report
      case VK_DEBUG_UTILS_MESSAGE_TYPE_DEVICE_ADDRESS_BINDING_BIT_EXT: return "Device Address Binding";
#endif
      default:
        assert(false && "Unhandled VkDebugUtilsMessageTypeFlagBitsEXT case");
        cds::impl::unreachable();
    }
  }

  switch (flag) {
    case VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT: return "VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT";
    case VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT: return "VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT";
    case VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT: return "VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT";
#ifdef VK_EXT_device_address_binding_report
    case VK_DEBUG_UTILS_MESSAGE_TYPE_DEVICE_ADDRESS_BINDING_BIT_EXT: return "VK_DEBUG_UTILS_MESSAGE_TYPE_DEVICE_ADDRESS_BINDING_BIT_EXT";
#endif
    default:
      assert(false && "Unhandled VkDebugUtilsMessageTypeFlagBitsEXT case");
      cds::impl::unreachable();
  }
}
#endif
} // namespace vk
