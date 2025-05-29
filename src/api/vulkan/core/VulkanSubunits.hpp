//
// Created by loghin on 5/27/25.
//

#pragma once

#include <vulkan/vulkan_core.h>

namespace c_eng::api::vk::detail {
class Vulkan;
class Instance;
class LogicalDevice;
class PhysicalDevice;

class VulkanSubObject {
public:
  explicit constexpr VulkanSubObject(Vulkan const& vulkan) noexcept : _vulkan{vulkan} {}
  VulkanSubObject(VulkanSubObject const&) = default;
  VulkanSubObject(VulkanSubObject&&) = default;

  [[nodiscard]] constexpr auto const& vulkan() const noexcept {
    return _vulkan;
  }

protected:
  ~VulkanSubObject() = default;

private:
  Vulkan const& _vulkan;
};

class InstanceSubObject {
public:
  explicit constexpr InstanceSubObject(Instance const& instance) noexcept : _instance{instance} {}
  InstanceSubObject(InstanceSubObject const&) = default;
  InstanceSubObject(InstanceSubObject&&) = default;

  [[nodiscard]] constexpr auto const& instance() const noexcept {
    return _instance;
  }

protected:
  ~InstanceSubObject() = default;

private:
  Instance const& _instance;
};

template <typename Device> class DeviceSubObject {
public:
  explicit constexpr DeviceSubObject(Device const& device) noexcept : _device{device} {}
  DeviceSubObject(DeviceSubObject const&) = default;
  DeviceSubObject(DeviceSubObject&&) = default;

  [[nodiscard]] constexpr auto const& device() const noexcept {
    return _device;
  }

protected:
  ~DeviceSubObject() = default;

private:
  Device const& _device;
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
  WrapsVulkanHandle(WrapsVulkanHandle&&) = default;

  [[nodiscard]] constexpr auto handle() const noexcept {
    return _handle;
  }

protected:
  ~WrapsVulkanHandle() = default;

private:
  VkHandle _handle{VK_NULL_HANDLE};
};

template <typename...> class VulkanObject;
template <typename...> struct SubObject;

template <> struct SubObject<Vulkan> {
  using Type = VulkanSubObject;
};

template <> struct SubObject<Instance> {
  using Type = InstanceSubObject;
};

template <> struct SubObject<PhysicalDevice> {
  using Type = DeviceSubObject<PhysicalDevice>;
};

template <> struct SubObject<LogicalDevice> {
  using Type = DeviceSubObject<LogicalDevice>;
};

template <typename... SuperObjects> struct SubObject {
  class Type : public SubObject<SuperObjects>::Type... {
  public:
    explicit constexpr Type(SuperObjects const&... objects) noexcept :
        SubObject<SuperObjects>::Type{objects}... {}
  protected:
    ~Type() = default;
  };
};

template <typename... Obj> class VulkanObject<SubObject<Obj...>> : public SubObject<Obj...>::Type {
public:
  explicit constexpr VulkanObject(Obj const&... objects) noexcept : SubObject<Obj...>::Type{objects...} {}
  VulkanObject(VulkanObject const&) = default;
  VulkanObject(VulkanObject&&) = default;

protected:
  ~VulkanObject() = default;
};

template <typename... Obj, typename VkHandle> class VulkanObject<SubObject<Obj...>, WrapsVulkanHandle<VkHandle>> :
    public SubObject<Obj...>::Type, public WrapsVulkanHandle<VkHandle> {
public:
  explicit constexpr VulkanObject(Obj const&... objects, VkHandle handle) noexcept :
      SubObject<Obj...>::Type{objects...}, WrapsVulkanHandle<VkHandle>{handle} {}

  VulkanObject(VulkanObject const&) = default;
  VulkanObject(VulkanObject&&) = default;

protected:
  ~VulkanObject() = default;
};

template <typename... Obj, typename VkHandle>
class VulkanObject<SubObject<Obj...>, WithAllocationCallbacks, WrapsVulkanHandle<VkHandle>> :
    public SubObject<Obj...>::Type, public WithAllocationCallbacks, public WrapsVulkanHandle<VkHandle> {
public:
  constexpr VulkanObject(
      Obj const&... objects,
      VkAllocationCallbacks const* pAllocationCallbacks,
      VkHandle handle
  ) noexcept :
      SubObject<Obj...>::Type{objects...},
      WithAllocationCallbacks{pAllocationCallbacks},
      WrapsVulkanHandle<VkHandle>{handle} {}

  VulkanObject(VulkanObject const&) = default;
  VulkanObject(VulkanObject&&) = default;

protected:
  ~VulkanObject() = default;
};
} // namespace c_eng::api::vk::detail
