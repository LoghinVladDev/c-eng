//
// Created by loghin on 11/14/24.
//

#pragma once

#include <cds/meta/Compiler>
#include <generic/Types.hpp>
#include <vulkan/vulkan_core.h>

namespace c_eng::api::vk::detail {
using cds::U32;
using generic::Version;

inline auto toVersion(U32 id) noexcept -> Version {
  return {
    .variant = VK_API_VERSION_VARIANT(id),
    .major = VK_API_VERSION_MAJOR(id),
    .minor = VK_API_VERSION_MINOR(id),
    .patch = VK_API_VERSION_PATCH(id)
  };
}

inline auto fromVersion(Version const& version) noexcept -> U32 {
  return VK_MAKE_API_VERSION(version.variant, version.major, version.minor, version.patch);
}

template <typename> struct VulkanTypeTraits {
  using Type = void;
};

template <typename T, VkStructureType type> struct VulkanTypeTraitsInstance {
  using Type = T;
  static constexpr auto sType = type;
};

#ifdef VK_VERSION_1_1
template <> struct VulkanTypeTraits<VkPhysicalDeviceFeatures2> :
    VulkanTypeTraitsInstance<VkPhysicalDeviceFeatures2, VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2> {};
#endif

#ifdef VK_VERSION_1_2
template <> struct VulkanTypeTraits<VkPhysicalDeviceTimelineSemaphoreFeatures> : VulkanTypeTraitsInstance<
    VkPhysicalDeviceTimelineSemaphoreFeatures,
    VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TIMELINE_SEMAPHORE_FEATURES
> {};

template <> struct VulkanTypeTraits<VkPhysicalDeviceVulkanMemoryModelFeatures> : VulkanTypeTraitsInstance<
    VkPhysicalDeviceVulkanMemoryModelFeatures,
    VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_MEMORY_MODEL_FEATURES
> {};

template <> struct VulkanTypeTraits<VkPhysicalDeviceBufferDeviceAddressFeatures> : VulkanTypeTraitsInstance<
    VkPhysicalDeviceBufferDeviceAddressFeatures,
    VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BUFFER_DEVICE_ADDRESS_FEATURES
> {};

template <> struct VulkanTypeTraits<VkPhysicalDevice8BitStorageFeatures> : VulkanTypeTraitsInstance<
    VkPhysicalDevice8BitStorageFeatures,
    VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_8BIT_STORAGE_FEATURES
> {};
#endif

#ifdef VK_KHR_ray_query
template <> struct VulkanTypeTraits<VkPhysicalDeviceRayQueryFeaturesKHR> : VulkanTypeTraitsInstance<
    VkPhysicalDeviceRayQueryFeaturesKHR,
    VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_QUERY_FEATURES_KHR
> {};
#endif

#ifdef VK_NV_ray_tracing_validation
template <> struct VulkanTypeTraits<VkPhysicalDeviceRayTracingValidationFeaturesNV> : VulkanTypeTraitsInstance<
    VkPhysicalDeviceRayTracingValidationFeaturesNV,
    VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_VALIDATION_FEATURES_NV
> {};
#endif
} // namespace c_eng::api::vk::detail

namespace c_eng::api::vk {
using detail::fromVersion;
using detail::toVersion;
}
