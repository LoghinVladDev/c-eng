//
// Created by loghin on 5/30/25.
//

#pragma once

#include <cds/Tuple>

#include "core/VulkanTypes.hpp"

#ifdef VK_VERSION_1_1
namespace c_eng::api::vk::detail {
using cds::meta::Conditional;
using cds::meta::IsSame;
using cds::ignore;
using cds::Tuple;

template <int index, typename Feature, typename... Features> struct PhysicalDeviceExtendedFeatureIndex;

template <int index, typename Feature> struct PhysicalDeviceExtendedFeatureIndex<index, Feature> {
  using Next = void;
  using Type = void;
  using FeatureType = void;

  static constexpr auto featureIndex = index;
};

template <int index, typename Feature, typename CurrentFeature, typename... Features>
struct PhysicalDeviceExtendedFeatureIndex<index, Feature, CurrentFeature, Features...> {
  using Next = PhysicalDeviceExtendedFeatureIndex<index + 1, Feature, Features...>;
  using Type = CurrentFeature;
  using Match = IsSame<Feature, CurrentFeature>;
  using FeatureType = Conditional<Match, Type, typename Next::FeatureType>;

  static constexpr auto featureIndex = Match::value
      ? index
      : Next::featureIndex;
};

template <typename... Features> struct PhysicalDeviceExtendedFeatures {
  constexpr PhysicalDeviceExtendedFeatures() {
    link();
    initStructureTypes<VkPhysicalDeviceFeatures2, Features...>(*this);
  }

  constexpr PhysicalDeviceExtendedFeatures(PhysicalDeviceExtendedFeatures const& features) noexcept :
      _features{features._features} {
    link();
  }

  constexpr PhysicalDeviceExtendedFeatures(PhysicalDeviceExtendedFeatures&& features) noexcept :
      _features{mv(features._features)} {
    link();
  }

  template <typename Feature> [[nodiscard]] constexpr auto const& get() const noexcept {
    return get<Feature>(*this);
  }

  template <typename Feature> [[nodiscard]] constexpr auto& get() noexcept {
    return get<Feature>(*this);
  }

  constexpr auto link() noexcept {
    link<VkPhysicalDeviceFeatures2, Features...>(*this);
  }

  [[nodiscard]] explicit constexpr operator VkPhysicalDeviceFeatures2&() noexcept {
    return cds::get<0>(_features);
  }

  [[nodiscard]] explicit constexpr operator VkPhysicalDeviceFeatures2 const&() const noexcept {
    return cds::get<0>(_features);
  }

  Tuple<VkPhysicalDeviceFeatures2, Features...> _features;
};

constexpr auto initStructureTypes(auto& structures) noexcept {
  // nothing to initialize
}

template <typename Type, typename... Rest> constexpr auto initStructureTypes(auto& structures) noexcept {
  get<Type>(structures).sType = VulkanTypeTraits<Type>::sType;
  initStructureTypes<Rest...>(structures);
}

template <
    typename Feature, typename... Features,
    typename I = PhysicalDeviceExtendedFeatureIndex<0u, Feature, VkPhysicalDeviceFeatures2, Features...>,
    typename T = typename I::FeatureType
> constexpr auto get(PhysicalDeviceExtendedFeatures<Features...>& features) noexcept
    -> T& {
  static_assert(!IsSame<T, void>::value, "Invalid use of 'get'. Must provide a structure present in the requested structures");
  return get<I::featureIndex>(features._features);
}

template <
    typename Feature, typename... Features,
    typename I = PhysicalDeviceExtendedFeatureIndex<0u, Feature, VkPhysicalDeviceFeatures2, Features...>,
    typename T = typename I::FeatureType
> constexpr auto get(PhysicalDeviceExtendedFeatures<Features...> const& features) noexcept
    -> T const& {
  static_assert(!IsSame<T, void>::value, "Invalid use of 'get'. Must provide a structure present in the requested structures");
  return get<I::featureIndex>(features._features);
}

template <typename LastFeature> constexpr auto link(auto& features) noexcept {
  auto& lastFeature = get<LastFeature>(features);
  lastFeature.pNext = nullptr;
}

template <typename Feature, typename NextFeature, typename... RemainingFeatures>
constexpr auto link(auto& features) noexcept {
  auto& feature = get<Feature>(features);
  auto& nextFeature = get<NextFeature>(features);
  feature.pNext = &nextFeature;
  link<NextFeature, RemainingFeatures...>(features);
}
} // namespace c_eng::api::vk::detail
#endif
