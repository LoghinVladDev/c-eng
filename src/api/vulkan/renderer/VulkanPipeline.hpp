//
// Created by loghin on 8/21/25.
//

#pragma once

#include <cds/Expected>
#include <cds/Optional>
#include <cds/StringView>
#include <cds/Tuple>
#include <cds/collection/Vector>

#include <generic/lang/Concepts.hpp>

#include <core/VulkanBuilders.hpp>
#include <core/VulkanSubunits.hpp>

namespace c_eng::api::vk::detail {
using cds::Expected;
using cds::Optional;
using cds::StringView;
using cds::Tuple;
using cds::Vector;
using cds::nullopt;

using generic::concepts::IterableOf;

class LogicalDevice;
class PipelineLayout;
class PipelineBuilder;
class ShaderModule;
class SwapChain;

class Pipeline :
    public VulkanObject<SubObject<LogicalDevice>, WithAllocationCallbacks, WrapsVulkanHandle<VkPipeline>> {
public:
  using VulkanObject::VulkanObject;
  Pipeline(Pipeline&&) = default;
  ~Pipeline() noexcept;

  [[nodiscard]] static constexpr auto builder(LogicalDevice const& device) noexcept -> PipelineBuilder;
};

class PipelineBuilder :
    public VulkanObjectBuilder<PipelineBuilder, Requiring<LogicalDevice>, WithAllocationCallbacks> {
public:
  using VulkanObjectBuilder::VulkanObjectBuilder;

  constexpr auto& renderOn(SwapChain const& swapChain) noexcept {
    _renderTarget = &swapChain;
    return *this;
  }

  auto withShader(ShaderModule const& module, VkShaderStageFlagBits stage, StringView entrypoint) noexcept
      -> PipelineBuilder&;

  template <IterableOf<VkDynamicState> States = std::initializer_list<VkDynamicState>>
  auto& withDynamicStates(States&& states) noexcept {
    _dynamicStates = fwd<States>(states);
    return *this;
  }

  constexpr auto& withPipelineLayout(PipelineLayout const& layout) noexcept {
    _pipelineLayout = &layout;
    return *this;
  }

  [[nodiscard]] auto build() const noexcept -> Expected<Pipeline, VkResult>;

private:
  SwapChain const* _renderTarget{nullptr};
  PipelineLayout const* _pipelineLayout{nullptr};
  Vector<Tuple<VkShaderModule, VkShaderStageFlagBits, StringView>> _shaderStages{};
  Vector<VkDynamicState> _dynamicStates{};
};

constexpr auto Pipeline::builder(LogicalDevice const& device) noexcept -> PipelineBuilder {
  return PipelineBuilder{device};
}
} // namespace c_eng::api::vk::detail

namespace c_eng::api::vk {
using detail::Pipeline;
using detail::PipelineBuilder;
} // namespace c_eng::api::vk
