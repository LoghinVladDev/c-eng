//
// Created by loghin on 8/21/25.
//

#pragma once

#include <cds/Expected>
#include <cds/Optional>
#include <cds/filesystem/Path>
#include <cds/collection/VectorView>
#include <core/VulkanSubunits.hpp>

namespace c_eng::api::vk::detail {
using cds::Expected;
using cds::Optional;
using cds::VectorView;
using cds::filesystem::Path;
using cds::nullopt;

class LogicalDevice;
class ShaderModuleBuilder;

class ShaderModule :
    public VulkanObject<SubObject<LogicalDevice>, WithAllocationCallbacks, WrapsVulkanHandle<VkShaderModule>> {
public:
  using VulkanObject::VulkanObject;
  ShaderModule(ShaderModule&&) = default;
  ~ShaderModule() noexcept;

  [[nodiscard]] constexpr static auto builder(LogicalDevice const& device) noexcept -> ShaderModuleBuilder;
};

class ShaderModuleBuilder {
public:
  explicit constexpr ShaderModuleBuilder(LogicalDevice const& device) noexcept : _device{device} {}

  auto buildFromPrecompiledShaderAt(Path const& path) const noexcept -> Expected<ShaderModule, VkResult>;
  auto buildFromByteCode(VectorView<char> code) const noexcept -> Expected<ShaderModule, VkResult>;

private:
  LogicalDevice const& _device;
  Optional<VkAllocationCallbacks const*> _allocationCallbacks{nullopt};
};

constexpr auto ShaderModule::builder(LogicalDevice const& device) noexcept -> ShaderModuleBuilder {
  return ShaderModuleBuilder{device};
}
} // namespace c_eng::api::vk::detail

namespace c_eng::api::vk {
using detail::ShaderModule;
} // namespace c_eng::api::vk
