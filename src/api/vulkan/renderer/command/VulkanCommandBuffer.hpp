//
// Created by loghin on 8/23/25.
//

#pragma once

#include <cds/Expected>
#include <cds/collection/Vector>
#include <cds/functional/FunctionRef>
#include <cds/iterator/ProjectionIterator>
#include <core/VulkanBuilders.hpp>
#include <core/VulkanSubunits.hpp>
#include <generic/lang/Concepts.hpp>

namespace c_eng::api::vk::detail {
using cds::Expected;
using cds::Size;
using cds::Vector;
using cds::functional::FunctionRef;
using cds::iterator::ProjectionIterator;

class CommandBufferAllocator;
class CommandBufferVector;
class CommandPool;
class CommandRecorder;
class Image;
class Pipeline;

class CommandBufferRef :
    public VulkanObject<SubObject<CommandPool>, WrapsVulkanHandle<VkCommandBuffer>> {
  friend CommandBufferVector;

public:
  using Recorder = CommandRecorder;
  using VulkanObject::VulkanObject;
  using VulkanObject::operator=;

  ~CommandBufferRef() noexcept = default;

  [[nodiscard]] auto record(FunctionRef<void(Recorder&)> recordCallback) const noexcept
      -> Expected<CommandBufferRef, VkResult>;
};

struct ToCommandBufferRefProjector {
  auto operator()(VkCommandBuffer buffer) const noexcept -> CommandBufferRef {
    return CommandBufferRef{pool, buffer};
  }

  CommandPool const& pool;
};

class CommandBufferVector : public VulkanObject<SubObject<CommandPool>>, private Vector<VkCommandBuffer> {
private:
  using Vector::Vector;
  using Vector::operator=;

public:
  using Iterator = ProjectionIterator<Vector::ConstIterator, ToCommandBufferRefProjector>;
  using ConstIterator = Iterator;
  using ReverseIterator = ProjectionIterator<Vector::ConstReverseIterator, ToCommandBufferRefProjector>;
  using ConstReverseIterator = ReverseIterator;

  CommandBufferVector(CommandBufferVector&&) = default;
  explicit CommandBufferVector(CommandPool const& pool, Size count) noexcept :
      VulkanObject{pool},
      Vector(count) {}

  ~CommandBufferVector() noexcept;

  using Vector::data;
  using Vector::size;
  using Vector::empty;
  using Vector::operator bool;

  template <generic::concepts::Integer Number> auto operator[](Number number) const noexcept -> CommandBufferRef {
    return CommandBufferRef{pool(), Vector::operator[](number)};
  }

  [[nodiscard]] auto begin() const noexcept -> Iterator {
    return Iterator{Vector::begin(), ToCommandBufferRefProjector{pool()}};
  }

  [[nodiscard]] auto end() const noexcept -> Iterator {
    return Iterator{Vector::end(), ToCommandBufferRefProjector{pool()}};
  }

  [[nodiscard]] auto cbegin() const noexcept -> Iterator {
    return Iterator{Vector::begin(), ToCommandBufferRefProjector{pool()}};
  }

  [[nodiscard]] auto cend() const noexcept -> Iterator {
    return Iterator{Vector::end(), ToCommandBufferRefProjector{pool()}};
  }

  [[nodiscard]] auto rbegin() const noexcept -> ReverseIterator {
    return ReverseIterator{Vector::rbegin(), ToCommandBufferRefProjector{pool()}};
  }

  [[nodiscard]] auto rend() const noexcept -> ReverseIterator {
    return ReverseIterator{Vector::rend(), ToCommandBufferRefProjector{pool()}};
  }

  [[nodiscard]] auto crbegin() const noexcept -> ReverseIterator {
    return ReverseIterator{Vector::rbegin(), ToCommandBufferRefProjector{pool()}};
  }

  [[nodiscard]] auto crend() const noexcept -> ReverseIterator {
    return ReverseIterator{Vector::rend(), ToCommandBufferRefProjector{pool()}};
  }
};

class CommandBufferAllocator :
    public VulkanObjectBuilder<CommandBufferAllocator, Requiring<CommandPool>> {
public:
  using VulkanObjectBuilder::VulkanObjectBuilder;

  [[nodiscard]] auto allocatePrimary(Size count) const noexcept -> Expected<CommandBufferVector, VkResult>;
  [[nodiscard]] auto allocateSecondary(Size count) const noexcept -> Expected<CommandBufferVector, VkResult>;
};

class CommandRecorder {
public:
  explicit constexpr CommandRecorder(CommandBufferRef const& ref) noexcept : _buffer{ref} {}

  [[nodiscard]] constexpr auto const& buffer() const noexcept {
    return _buffer;
  }

  auto beginRendering(VkRenderingInfo const& renderingInfo) const noexcept -> void;
  auto endRendering() const noexcept -> void;

  auto bindPipeline(Pipeline const& pipeline) const noexcept -> void;
  auto setViewport(VkViewport const& viewport) const noexcept -> void;
  auto setScissor(VkRect2D const& scissor) const noexcept -> void;
  auto draw(Size vertexCount, Size instanceCount, Size firstVertex, Size firstInstance) const noexcept -> void;

  auto transitionImageLayout(
      Image const& image,
      VkImageLayout oldLayout,
      VkImageLayout newLayout,
      VkAccessFlags2 srcAccessMask,
      VkAccessFlags2 dstAccessMask,
      VkPipelineStageFlags2 srcStageMask,
      VkPipelineStageFlags2 dstStageMask
  ) const noexcept -> void;

private:
  CommandBufferRef _buffer;
};
} // namespace c_eng::api::vk::detail

namespace c_eng::api::vk {
using detail::CommandBufferAllocator;
using detail::CommandBufferRef;
using detail::CommandBufferVector;
using detail::CommandRecorder;
} // namespace c_eng::api::vk
