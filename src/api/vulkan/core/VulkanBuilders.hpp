//
// Created by loghin on 8/22/25.
//

#pragma once

#include <cds/Optional>
#include <cds/Tuple>

#include "VulkanSubunits.hpp"

namespace c_eng::api::vk::detail {
using cds::Optional;
using cds::Tuple;
using cds::nullopt;

template <typename, typename> class VulkanObjectBuilderSpec;

template <typename B, typename... Specs> class VulkanObjectBuilder :
    public VulkanObjectBuilderSpec<B, Specs>... {
  using VulkanObjectBuilderSpec<B, Specs>::VulkanObjectBuilderSpec...;
};

template <typename B> class VulkanObjectBuilderSpec<B, WithAllocationCallbacks> {
public:
  auto withAllocationCallbacks(VkAllocationCallbacks const* pAllocationCallbacks) noexcept -> B& {
    _allocationCallbacks = pAllocationCallbacks;
    return static_cast<B&>(*this);
  }

protected:
  [[nodiscard]] auto& allocationCallbacks() noexcept {
    return _allocationCallbacks;
  }

  [[nodiscard]] auto const& allocationCallbacks() const noexcept {
    return _allocationCallbacks;
  }

private:
  Optional<VkAllocationCallbacks const*> _allocationCallbacks{nullopt};
};

template <typename...> struct Requiring;

template <typename B, typename... Objects> class VulkanObjectBuilderSpec<B, Requiring<Objects...>> :
    public VulkanObjectBuilderSpec<B, Objects>... {
public:
  explicit constexpr VulkanObjectBuilderSpec(Objects const&... objects) noexcept :
      VulkanObjectBuilderSpec<B, Objects>{objects}... {}
};

class LogicalDevice;

template <typename B> class VulkanObjectBuilderSpec<B, LogicalDevice> {
public:
  explicit constexpr VulkanObjectBuilderSpec(LogicalDevice const& device) noexcept : _device{device} {}

protected:
  [[nodiscard]] auto const& device() const noexcept {
    return _device;
  }

private:
  LogicalDevice const& _device;
};
} // namespace detail
