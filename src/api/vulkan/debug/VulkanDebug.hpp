//
// Created by loghin on 18.04.2025.
//

#pragma once

#include <cds/Expected>
#include <cds/meta/Semantics>
#include <core/VulkanSubunits.hpp>
#include <generic/log/Logger.hpp>

namespace c_eng::api::vk::detail {
using cds::Expected;
using cds::Optional;
using cds::impl::xch;
using cds::nullopt;

using generic::LoggerRef;

#ifndef VK_EXT_debug_utils
VK_DEFINE_HANDLE(VkDebugUtilsMessengerEXT)
#endif

class Instance;
class DebugMessengerBuilder;

class DebugMessenger :
    public VulkanObject<SubObject<Instance>, WithAllocationCallbacks, WrapsVulkanHandle<VkDebugUtilsMessengerEXT>> {
public:
  using VulkanObject::VulkanObject;
  DebugMessenger(DebugMessenger&&) = default;
  ~DebugMessenger() noexcept;

  [[nodiscard]] static auto builder(Instance const& instance) noexcept -> DebugMessengerBuilder;
};

class DebugMessengerBuilder {
public:
  explicit DebugMessengerBuilder(Instance const& instance) noexcept : _instance{instance} {}

  [[nodiscard]] auto build(LoggerRef logger) const noexcept -> Expected<DebugMessenger, VkResult>;

private:
  Instance const& _instance;

  Optional<VkAllocationCallbacks const*> _pAllocationCallbacks{nullopt};
  LoggerRef _logger{};
};

inline auto DebugMessenger::builder(Instance const& instance) noexcept -> DebugMessengerBuilder {
  return DebugMessengerBuilder{instance};
}
} // namespace c_eng::api::vk::detail

namespace c_eng::api::vk {
using detail::DebugMessenger;
using detail::DebugMessengerBuilder;
} // namespace c_eng::api::vk
