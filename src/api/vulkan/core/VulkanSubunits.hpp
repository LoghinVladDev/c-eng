//
// Created by loghin on 5/27/25.
//

#pragma once

#include <cds/meta/Semantics>
#include <vulkan/vulkan_core.h>

namespace c_eng::api::vk::detail {
class Vulkan;
class CommandPool;
class Image;
class Instance;
class LogicalDevice;
class PhysicalDevice;
class QueueFamily;

using cds::xch;

template <typename O> class GenericSub {
public:
  explicit constexpr GenericSub(O const& obj) noexcept : _data{&obj} {}
  GenericSub(GenericSub const&) = default;
  GenericSub(GenericSub&&) = default;
  auto operator=(GenericSub const&) -> GenericSub& = default;
  auto operator=(GenericSub&&) -> GenericSub& = default;

protected:
  ~GenericSub() = default;

  [[nodiscard]] constexpr auto const& data() const noexcept {
    return *_data;
  }

private:
  O const* _data;
};

template <typename...> class SubObject;

template <> class SubObject<Vulkan> : public GenericSub<Vulkan> {
public:
  using GenericSub::GenericSub;
  using GenericSub::operator=;
  [[nodiscard]] constexpr auto const& vulkan() const noexcept {
    return data();
  }
};

template <> class SubObject<Instance> : public GenericSub<Instance> {
public:
  using GenericSub::GenericSub;
  using GenericSub::operator=;
  [[nodiscard]] constexpr auto const& instance() const noexcept {
    return data();
  }
};

template <> class SubObject<PhysicalDevice> : public GenericSub<PhysicalDevice> {
public:
  using GenericSub::GenericSub;
  using GenericSub::operator=;
  [[nodiscard]] constexpr auto const& device() const noexcept {
    return data();
  }
};

template <> class SubObject<LogicalDevice> : public GenericSub<LogicalDevice> {
public:
  using GenericSub::GenericSub;
  using GenericSub::operator=;
  [[nodiscard]] constexpr auto const& device() const noexcept {
    return data();
  }
};

template <> class SubObject<QueueFamily> : public GenericSub<QueueFamily> {
public:
  using GenericSub::GenericSub;
  using GenericSub::operator=;
  [[nodiscard]] constexpr auto const& family() const noexcept {
    return data();
  }
};

template <> class SubObject<Image> : public GenericSub<Image> {
public:
  using GenericSub::GenericSub;
  using GenericSub::operator=;
  [[nodiscard]] constexpr auto const& image() const noexcept {
    return data();
  }
};

template <> class SubObject<CommandPool> : public GenericSub<CommandPool> {
public:
  using GenericSub::GenericSub;
  using GenericSub::operator=;
  [[nodiscard]] constexpr auto const& pool() const noexcept {
    return data();
  }
};

class WithAllocationCallbacks {
public:
  explicit constexpr WithAllocationCallbacks(VkAllocationCallbacks const* pAllocationCallbacks) noexcept :
      _pAllocationCallbacks{pAllocationCallbacks} {}
  WithAllocationCallbacks(WithAllocationCallbacks const&) = delete;
  WithAllocationCallbacks(WithAllocationCallbacks&&) = default;

  [[nodiscard]] constexpr auto allocationCallbacks() const noexcept {
    return _pAllocationCallbacks;
  }

protected:
  ~WithAllocationCallbacks() = default;

private:
  VkAllocationCallbacks const* _pAllocationCallbacks{nullptr};
};

template <typename VkHandle> class WrapsVulkanHandle {
public:
  explicit constexpr WrapsVulkanHandle(VkHandle handle) : _handle {handle} {}
  WrapsVulkanHandle(WrapsVulkanHandle const&) = default;
  constexpr WrapsVulkanHandle(WrapsVulkanHandle&& wrapper) noexcept :
      _handle{xch(wrapper._handle, VK_NULL_HANDLE)} {}
  auto operator=(WrapsVulkanHandle const&) -> WrapsVulkanHandle& = default;
  constexpr auto operator=(WrapsVulkanHandle&& obj) noexcept -> WrapsVulkanHandle& {
    if (this == &obj) {
      return *this;
    }

    _handle = xch(obj._handle, VK_NULL_HANDLE);
    return *this;
  }

  [[nodiscard]] constexpr auto handle() const noexcept {
    return _handle;
  }

protected:
  ~WrapsVulkanHandle() = default;

private:
  VkHandle _handle{VK_NULL_HANDLE};
};

template <typename...> class VulkanObject;

template <typename... SuperObjects> class SubObject : public SubObject<SuperObjects>... {
public:
  explicit constexpr SubObject(SuperObjects const&... objects) noexcept : SubObject<SuperObjects>{objects}... {}
  SubObject(SubObject const&) = default;
  SubObject(SubObject&&) = default;

protected:
  ~SubObject() noexcept = default;
};

template <typename... Obj> class VulkanObject<SubObject<Obj...>> : public SubObject<Obj...> {
public:
  explicit constexpr VulkanObject(Obj const&... objects) noexcept : SubObject<Obj...>{objects...} {}
  VulkanObject(VulkanObject const&) = default;
  VulkanObject(VulkanObject&&) = default;

protected:
  ~VulkanObject() = default;
};

template <typename... Obj, typename VkHandle> class VulkanObject<SubObject<Obj...>, WrapsVulkanHandle<VkHandle>> :
    public SubObject<Obj...>, public WrapsVulkanHandle<VkHandle> {
public:
  explicit constexpr VulkanObject(Obj const&... objects, VkHandle handle) noexcept :
      SubObject<Obj...>{objects...}, WrapsVulkanHandle<VkHandle>{handle} {}

  VulkanObject(VulkanObject const&) = default;
  VulkanObject(VulkanObject&&) = default;
  auto operator=(VulkanObject const&) -> VulkanObject& = default;
  auto operator=(VulkanObject&&) -> VulkanObject& = default;

protected:
  ~VulkanObject() = default;
};

template <typename... Obj, typename VkHandle>
class VulkanObject<SubObject<Obj...>, WithAllocationCallbacks, WrapsVulkanHandle<VkHandle>> :
    public SubObject<Obj...>, public WithAllocationCallbacks, public WrapsVulkanHandle<VkHandle> {
public:
  constexpr VulkanObject(
      Obj const&... objects,
      VkAllocationCallbacks const* pAllocationCallbacks,
      VkHandle handle
  ) noexcept :
      SubObject<Obj...>{objects...},
      WithAllocationCallbacks{pAllocationCallbacks},
      WrapsVulkanHandle<VkHandle>{handle} {}

  VulkanObject(VulkanObject const&) = default;
  VulkanObject(VulkanObject&&) = default;
  auto operator=(VulkanObject const&) -> VulkanObject& = default;
  auto operator=(VulkanObject&&) -> VulkanObject& = default;

protected:
  ~VulkanObject() = default;
};
} // namespace c_eng::api::vk::detail
