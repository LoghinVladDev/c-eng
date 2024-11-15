//
// Created by loghin on 11/14/24.
//

#pragma once

#include "VulkanTypes.hpp"
#include <sstream>
#include <cds/collection/Vector>
#include <generic/TypesToString.hpp>

namespace c_eng::generic::detail {
using std::hex;
using std::stringstream;

using cds::String;
using cds::Vector;
using cds::U32;
using cds::U64;
using cds::bitCast;

template <> struct ToString<VkLayerProperties> : True {
  auto operator()(VkLayerProperties const& properties) const noexcept {
    return R"(VkLayerProperties{{name="{}", targetSpecVersion={}, revision={}, description="{}"}})"_f(
      static_cast<char const*>(properties.layerName), toVersion(properties.specVersion),
      properties.implementationVersion, static_cast<char const*>(properties.description)
    );
  }
};

template <> struct ToString<VkStructureType> : True {
  constexpr auto operator()(VkStructureType type) const noexcept {
    switch (type) {
      case VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO: return "VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO";
      case VK_STRUCTURE_TYPE_APPLICATION_INFO: return "VK_STRUCTURE_TYPE_APPLICATION_INFO";
#ifdef VK_EXT_debug_utils
      case VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT:
        return "VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT";
      case VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CALLBACK_DATA_EXT:
        return "VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CALLBACK_DATA_EXT";
      case VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT:
        return "VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT";
      case VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT:
        return "VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT";
#endif
      default:
        assert(false && "Unhandled VkStructureType type");
        unreachable();
    }
  }
};

template <> struct ToString<VkObjectType> : True {
  constexpr auto operator()(VkObjectType type) const noexcept {
    switch (type) {
      case VK_OBJECT_TYPE_UNKNOWN: return "VK_OBJECT_TYPE_UNKNOWN";
      case VK_OBJECT_TYPE_INSTANCE: return "VK_OBJECT_TYPE_INSTANCE";
      case VK_OBJECT_TYPE_PHYSICAL_DEVICE: return "VK_OBJECT_TYPE_PHYSICAL_DEVICE";
      case VK_OBJECT_TYPE_DEVICE: return "VK_OBJECT_TYPE_DEVICE";
      case VK_OBJECT_TYPE_QUEUE: return "VK_OBJECT_TYPE_QUEUE";
      case VK_OBJECT_TYPE_SEMAPHORE: return "VK_OBJECT_TYPE_SEMAPHORE";
      case VK_OBJECT_TYPE_COMMAND_BUFFER: return "VK_OBJECT_TYPE_COMMAND_BUFFER";
      case VK_OBJECT_TYPE_FENCE: return "VK_OBJECT_TYPE_FENCE";
      case VK_OBJECT_TYPE_DEVICE_MEMORY: return "VK_OBJECT_TYPE_DEVICE_MEMORY";
      case VK_OBJECT_TYPE_BUFFER: return "VK_OBJECT_TYPE_BUFFER";
      case VK_OBJECT_TYPE_IMAGE: return "VK_OBJECT_TYPE_IMAGE";
      case VK_OBJECT_TYPE_EVENT: return "VK_OBJECT_TYPE_EVENT";
      case VK_OBJECT_TYPE_QUERY_POOL: return "VK_OBJECT_TYPE_QUERY_POOL";
      case VK_OBJECT_TYPE_BUFFER_VIEW: return "VK_OBJECT_TYPE_BUFFER_VIEW";
      case VK_OBJECT_TYPE_IMAGE_VIEW: return "VK_OBJECT_TYPE_IMAGE_VIEW";
      case VK_OBJECT_TYPE_SHADER_MODULE: return "VK_OBJECT_TYPE_SHADER_MODULE";
      case VK_OBJECT_TYPE_PIPELINE_CACHE: return "VK_OBJECT_TYPE_PIPELINE_CACHE";
      case VK_OBJECT_TYPE_PIPELINE_LAYOUT: return "VK_OBJECT_TYPE_PIPELINE_LAYOUT";
      case VK_OBJECT_TYPE_RENDER_PASS: return "VK_OBJECT_TYPE_RENDER_PASS";
      case VK_OBJECT_TYPE_PIPELINE: return "VK_OBJECT_TYPE_PIPELINE";
      case VK_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT: return "VK_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT";
      case VK_OBJECT_TYPE_SAMPLER: return "VK_OBJECT_TYPE_SAMPLER";
      case VK_OBJECT_TYPE_DESCRIPTOR_POOL: return "VK_OBJECT_TYPE_DESCRIPTOR_POOL";
      case VK_OBJECT_TYPE_DESCRIPTOR_SET: return "VK_OBJECT_TYPE_DESCRIPTOR_SET";
      case VK_OBJECT_TYPE_FRAMEBUFFER: return "VK_OBJECT_TYPE_FRAMEBUFFER";
      case VK_OBJECT_TYPE_COMMAND_POOL: return "VK_OBJECT_TYPE_COMMAND_POOL";
#ifdef VK_VERSION_1_1
      case VK_OBJECT_TYPE_SAMPLER_YCBCR_CONVERSION: return "VK_OBJECT_TYPE_SAMPLER_YCBCR_CONVERSION";
      case VK_OBJECT_TYPE_DESCRIPTOR_UPDATE_TEMPLATE: return "VK_OBJECT_TYPE_DESCRIPTOR_UPDATE_TEMPLATE";
#endif
#ifdef VK_VERSION_1_3
      case VK_OBJECT_TYPE_PRIVATE_DATA_SLOT: return "VK_OBJECT_TYPE_PRIVATE_DATA_SLOT";
#endif
#ifdef VK_KHR_surface
      case VK_OBJECT_TYPE_SURFACE_KHR: return "VK_OBJECT_TYPE_SURFACE_KHR";
#endif
#ifdef VK_KHR_swapchain
      case VK_OBJECT_TYPE_SWAPCHAIN_KHR: return "VK_OBJECT_TYPE_SWAPCHAIN_KHR";
#endif
#ifdef VK_KHR_display
      case VK_OBJECT_TYPE_DISPLAY_KHR: return "VK_OBJECT_TYPE_DISPLAY_KHR";
      case VK_OBJECT_TYPE_DISPLAY_MODE_KHR: return "VK_OBJECT_TYPE_DISPLAY_MODE_KHR";
#endif
#ifdef VK_EXT_debug_report
      case VK_OBJECT_TYPE_DEBUG_REPORT_CALLBACK_EXT: return "VK_OBJECT_TYPE_DEBUG_REPORT_CALLBACK_EXT";
#endif
#ifdef VK_KHR_video_queue
      case VK_OBJECT_TYPE_VIDEO_SESSION_KHR: return "VK_OBJECT_TYPE_VIDEO_SESSION_KHR";
      case VK_OBJECT_TYPE_VIDEO_SESSION_PARAMETERS_KHR: return "VK_OBJECT_TYPE_VIDEO_SESSION_PARAMETERS_KHR";
#endif
#ifdef VK_NVX_binary_import
      case VK_OBJECT_TYPE_CU_MODULE_NVX: return "VK_OBJECT_TYPE_CU_MODULE_NVX";
      case VK_OBJECT_TYPE_CU_FUNCTION_NVX: return "VK_OBJECT_TYPE_CU_FUNCTION_NVX";
#endif
#ifdef VK_EXT_debug_utils
      case VK_OBJECT_TYPE_DEBUG_UTILS_MESSENGER_EXT: return "VK_OBJECT_TYPE_DEBUG_UTILS_MESSENGER_EXT";
#endif
#ifdef VK_KHR_acceleration_structure
      case VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR: return "VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR";
#endif
#ifdef VK_EXT_validation_cache
      case VK_OBJECT_TYPE_VALIDATION_CACHE_EXT: return "VK_OBJECT_TYPE_VALIDATION_CACHE_EXT";
#endif
#ifdef VK_NV_ray_tracing
      case VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_NV: return "VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_NV";
#endif
#ifdef VK_INTEL_performance_query
      case VK_OBJECT_TYPE_PERFORMANCE_CONFIGURATION_INTEL: return "VK_OBJECT_TYPE_PERFORMANCE_CONFIGURATION_INTEL";
#endif
#ifdef VK_KHR_deferred_host_operations
      case VK_OBJECT_TYPE_DEFERRED_OPERATION_KHR: return "VK_OBJECT_TYPE_DEFERRED_OPERATION_KHR";
#endif
#ifdef VK_NV_device_generated_commands
      case VK_OBJECT_TYPE_INDIRECT_COMMANDS_LAYOUT_NV: return "VK_OBJECT_TYPE_INDIRECT_COMMANDS_LAYOUT_NV";
#endif
#ifdef VK_NV_cuda_kernel_launch
      case VK_OBJECT_TYPE_CUDA_MODULE_NV: return "VK_OBJECT_TYPE_CUDA_MODULE_NV";
      case VK_OBJECT_TYPE_CUDA_FUNCTION_NV: return "VK_OBJECT_TYPE_CUDA_FUNCTION_NV";
#endif
#ifdef VK_FUCHSIA_buffer_collection
      case VK_OBJECT_TYPE_BUFFER_COLLECTION_FUCHSIA: return "VK_OBJECT_TYPE_BUFFER_COLLECTION_FUCHSIA";
#endif
#ifdef VK_EXT_opacity_micromap
      case VK_OBJECT_TYPE_MICROMAP_EXT: return "VK_OBJECT_TYPE_MICROMAP_EXT";
#endif
#ifdef VK_NV_optical_flow
      case VK_OBJECT_TYPE_OPTICAL_FLOW_SESSION_NV: return "VK_OBJECT_TYPE_OPTICAL_FLOW_SESSION_NV";
#endif
#ifdef VK_EXT_shader_object
      case VK_OBJECT_TYPE_SHADER_EXT: return "VK_OBJECT_TYPE_SHADER_EXT";
#endif
#ifdef VK_KHR_pipeline_binary
      case VK_OBJECT_TYPE_PIPELINE_BINARY_KHR: return "VK_OBJECT_TYPE_PIPELINE_BINARY_KHR";
#endif
#ifdef VK_EXT_device_generated_commands
      case VK_OBJECT_TYPE_INDIRECT_COMMANDS_LAYOUT_EXT: return "VK_OBJECT_TYPE_INDIRECT_COMMANDS_LAYOUT_EXT";
      case VK_OBJECT_TYPE_INDIRECT_EXECUTION_SET_EXT: return "VK_OBJECT_TYPE_INDIRECT_EXECUTION_SET_EXT";
#endif
#if defined(VK_KHR_descriptor_update_template) && !defined(VK_VERSION_1_1)
      case VK_OBJECT_TYPE_DESCRIPTOR_UPDATE_TEMPLATE_KHR: return "VK_OBJECT_TYPE_DESCRIPTOR_UPDATE_TEMPLATE_KHR";
#endif
#if defined(VK_KHR_sampler_ycbcr_conversion) && !defined(VK_VERSION_1_1)
      case VK_OBJECT_TYPE_SAMPLER_YCBCR_CONVERSION_KHR: return "VK_OBJECT_TYPE_SAMPLER_YCBCR_CONVERSION_KHR";
#endif
#if defined(VK_EXT_private_data) && !defined(VK_VERSION_1_3)
      case VK_OBJECT_TYPE_PRIVATE_DATA_SLOT_EXT: return "VK_OBJECT_TYPE_PRIVATE_DATA_SLOT_EXT";
#endif
      default:
        assert(false && "Unhandled VkObjectType type");
        unreachable();
    }
  }
};

template <> struct ToString<VkInstanceCreateInfo> : True {
  auto operator()(VkInstanceCreateInfo const& info) const noexcept {
    auto const& [
        type, next, flags, applicationInfo,
        layerCount, layers,
        extensionCount, extensions
    ] = info;
    return "VkInstanceCreateInfo{{"
           "sType={}, next={}, flags={}, applicationInfo={}, enabledLayers={}, enabledExtensions={}"
           "}}"_f(type, addressAsString(next), flags, addressAsString(applicationInfo),
                  Vector<char const*>{layers, layers + layerCount},
                  Vector<char const*>{extensions, extensions + extensionCount});
  }
};

#ifdef VK_EXT_debug_utils
template <> struct ToString<VkDebugUtilsMessageTypeFlagBitsEXT> : True {
  constexpr auto operator()(VkDebugUtilsMessageTypeFlagBitsEXT type) const noexcept {
    switch (type) {
      case VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT: return "VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT";
      case VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT: return "VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT";
      case VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT: return "VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT";
#ifdef VK_EXT_device_address_binding_report
      case VK_DEBUG_UTILS_MESSAGE_TYPE_DEVICE_ADDRESS_BINDING_BIT_EXT:
        return "VK_DEBUG_UTILS_MESSAGE_TYPE_DEVICE_ADDRESS_BINDING_BIT_EXT";
#endif
      default:
        assert(false && "Unhandled VkDebugUtilsMessageTypeFlagBitsEXT case");
        unreachable();
    }
  }
};

template <> struct ToString<VkDebugUtilsMessageSeverityFlagBitsEXT> : True {
  constexpr auto operator()(VkDebugUtilsMessageSeverityFlagBitsEXT type) const noexcept {
    switch (type) {
      case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT: return "VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT";
      case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT: return "VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT";
      case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT: return "VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT";
      case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT: return "VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT";
      default:
        assert(false && "Unhandled VkDebugUtilsMessageSeverityFlagBitsEXT case");
        unreachable();
    }
  }
};

template <> struct ToString<VkDebugUtilsLabelEXT> : True {
  auto operator()(VkDebugUtilsLabelEXT const& label) const noexcept {
    auto const& [type, next, name, color] = label;
    return "VkDebugUtilsLabelEXT{{"
           R"(sType={}, pNext={}, labelName="{}", color={})"
           "}}"_f(label.sType, addressAsString(next), name, Vector<float>{cds::begin(color), cds::end(color)});
  }
};

template <> struct ToString<VkDebugUtilsObjectNameInfoEXT> : True {
  auto operator()(VkDebugUtilsObjectNameInfoEXT const& nameInfo) const noexcept {
    // TODO: cds/experimental/Format provide formatting literals support for number formatting(hex)
    auto const& [sType, next, oType, handle, name] = nameInfo;
    return "VkDebugUtilsObjectNameInfoEXT{{"
           R"(sType={}, pNext={}, objectType={}, objectHandle={}, objectName="{}")"
           "}}"_f(sType, addressAsString(next), oType, addressAsString(bitCast<void const*>(handle)), name);
  }
};

template <> struct ToString<VkDebugUtilsMessengerCallbackDataEXT> : True {
  auto operator()(VkDebugUtilsMessengerCallbackDataEXT const& data) const noexcept {
    auto const& [
        type, next, flags,
        messageIdName, messageIdNumber, message,
        queueLabelCount, queueLabels,
        cmdBufLabelCount, cmdBufLabels,
        objectCount, objects
    ] = data;

    // TODO: cds/collection/ContiguousView instead of Vector creation
    return "VkDebugUtilsMessengerCallbackDataEXT{{"
           R"(sType={}, pNext={}, flags={}, messageIdName="{}", messageIdNumber={}, )"
           R"(message="{}", queueLabels={}, cmdBufLabels={}, objects={})"
           "}}"_f(type, addressAsString(next), flags, messageIdName, messageIdNumber, message,
                  Vector<VkDebugUtilsLabelEXT>{queueLabels, queueLabels + queueLabelCount},
                  Vector<VkDebugUtilsLabelEXT>{cmdBufLabels, cmdBufLabels + cmdBufLabelCount},
                  Vector<VkDebugUtilsObjectNameInfoEXT>{objects, objects + objectCount});
  }
};
#endif

template <typename FlagType, typename Flags, typename FlagToString>
auto genericFlagsToString(Flags flags, FlagToString const& flagToString) noexcept -> String {
  String asStr;
  U32 maxFlag = 1u << 31u;
  for (U32 flagValue = 1u; flagValue != maxFlag; flagValue <<= 1u) {
    if ((flagValue & flags) != 0u) {
      asStr += flagToString(static_cast<FlagType>(flagValue));
      asStr += "|";
    }
  }

  if ((maxFlag & flags) != 0u) {
    asStr += flagToString(static_cast<FlagType>(maxFlag));
    asStr += "|";
  }
  return asStr.sub(0, asStr.length() - 1);
}

template <typename FlagType, typename Flags> auto flagsToString(Flags flags) noexcept -> String {
  return genericFlagsToString<FlagType>(flags, ToString<FlagType>{});
}
} // namespace c_eng::generic::detail

namespace c_eng::generic {
using detail::flagsToString;
} // namespace c_eng::generic
