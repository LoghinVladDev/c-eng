//
// Created by loghin on 19.04.2025.
//

#pragma once

#include <cds/Format>
#include "VulkanString.hpp"
#include "VulkanTypes.hpp"
#include "generic/TypesFormatters.hpp"

struct AlternatePresentationFormatter {
  template <typename Ctx> constexpr auto parse(Ctx& ctx) noexcept(false) -> typename Ctx::Iterator {
    auto it = ctx.begin();
    auto end = ctx.end();
    if (it == end || *it == '}') {
      return it;
    }

    if (*it == 'a') {
      alternate = true;
      ++it;
    }

    if (it == end || *it == '}') {
      return it;
    }

    throw cds::FormatException("Unexpected token in format string");
  }

  bool alternate {false};
};

template <typename /* FlagBits */> struct VulkanFormattedFlags {
  VkFlags flags;
};

template <typename C, typename F> struct cds::Formatter<VulkanFormattedFlags<F>, C> : AlternatePresentationFormatter {
  template <typename Ctx> auto format(VulkanFormattedFlags<F> const wrappedFlags, Ctx& ctx) const noexcept
      -> typename Ctx::Iterator {
    auto const flags = wrappedFlags.flags;
    auto maxFlag = 1u << 31u;
    auto first = true;
    auto out = ctx.out();
    constexpr auto sep = StringView{" | "};
    for (auto flagValue = 1u; flagValue != maxFlag; flagValue <<= 1u) {
      if ((flagValue & flags) != 0u) {
        if (!first) {
          out = impl::copy(sep.begin(), sep.end(), out);
        }

        auto const asStr = vk::toString(static_cast<F>(flagValue), alternate);
        out = impl::copy(asStr.begin(), asStr.end(), out);
        first = false;
      }
    }

    if ((maxFlag & flags) != 0u) {
      if (!first) {
        out = impl::copy(sep.begin(), sep.end(), out);
      }

      auto const asStr = vk::toString(static_cast<F>(maxFlag), alternate);
      out = impl::copy(asStr.begin(), asStr.end(), out);
    }
    return out;
  }
};

#ifdef VK_VERSION_1_0
template <typename C> struct cds::Formatter<VkResult, C> {
  template <typename Ctx> auto format(VkResult const result, Ctx& ctx) const noexcept -> typename Ctx::Iterator {
    auto const asStr = vk::toString(result);
    return impl::copy(asStr.begin(), asStr.end(), ctx.out());
  }
};

template <typename C> struct cds::Formatter<VkSystemAllocationScope, C> {
  template <typename Ctx> auto format(VkSystemAllocationScope const result, Ctx& ctx) const noexcept -> typename Ctx::Iterator {
    auto const asStr = vk::toString(result);
    return impl::copy(asStr.begin(), asStr.end(), ctx.out());
  }
};

template <typename C> struct cds::Formatter<VkInternalAllocationType, C> {
  template <typename Ctx> auto format(VkInternalAllocationType const result, Ctx& ctx) const noexcept -> typename Ctx::Iterator {
    auto const asStr = vk::toString(result);
    return impl::copy(asStr.begin(), asStr.end(), ctx.out());
  }
};

template <typename C> struct cds::Formatter<VkLayerProperties, C> {
  template <typename Ctx> auto format(VkLayerProperties const& properties, Ctx& ctx) const noexcept -> typename Ctx::Iterator {
    auto out = ctx.out();

    auto constexpr b0 = StringView{R"(VkLayerProperties{name=")"};
    auto constexpr b1 = StringView{R"(", targetSpecVersion=)"};
    auto constexpr b2 = StringView{R"(", revision=)"};
    auto constexpr b3 = StringView{R"(", description"=)"};
    auto constexpr b4 = StringView{R"("})"};

    auto const name = StringView{static_cast<char const*>(properties.layerName)};
    auto const specVersion = c_eng::api::vk::toVersion(properties.specVersion);
    auto const implVersion = properties.implementationVersion;
    auto const description = StringView{static_cast<char const*>(properties.description)};

    Formatter<c_eng::generic::Version> versionFormatter;
    Formatter<meta::RemoveCVRef<decltype(implVersion)>> implFormatter;

    impl::fmt::FormatParseContext<C, impl::StringUtils<C, impl::StringTraits<C>>> pCtx{""};
    implFormatter.parse(pCtx);

    out = impl::copy(b0.begin(), b0.end(), out);
    out = impl::copy(name.begin(), name.end(), out);
    out = impl::copy(b1.begin(), b1.end(), out);
    auto ctx1 = ctx.from(out);
    out = versionFormatter.format(specVersion, ctx1);
    out = impl::copy(b2.begin(), b2.end(), out);
    auto ctx2 = ctx1.from(out);
    out = implFormatter.format(implVersion, ctx2);
    out = impl::copy(b3.begin(), b3.end(), out);
    out = impl::copy(description.begin(), description.end(), out);
    return impl::copy(b4.begin(), b4.end(), out);
  }
};

template <typename C> struct cds::Formatter<VkExtent3D, C> {
  template <typename Ctx> auto format(VkExtent3D const& extent, Ctx& ctx) const noexcept -> typename Ctx::Iterator {
    auto out = ctx.out();

    auto constexpr b0 = StringView{R"(VkExtent3D{width=)"};
    auto constexpr b1 = StringView{R"(, height=)"};
    auto constexpr b2 = StringView{R"(, depth=)"};
    auto constexpr b3 = StringView{R"(})"};

    out = impl::copy(b0.begin(), b0.end(), out);
    auto ctx1 = ctx.from(out);
    out = underlyingU32Formatter.format({extent.width}, ctx1);
    out = impl::copy(b1.begin(), b1.end(), out);
    auto ctx2 = ctx1.from(out);
    out = underlyingU32Formatter.format(extent.height, ctx2);
    out = impl::copy(b2.begin(), b2.end(), out);
    auto ctx3 = ctx2.from(out);
    out = underlyingU32Formatter.format(extent.depth, ctx3);
    return impl::copy(b3.begin(), b3.end(), out);
  }

  Formatter<std::uint32_t> underlyingU32Formatter;
};

template <typename C> struct cds::Formatter<VkQueueFamilyProperties, C> : AlternatePresentationFormatter {
  template <typename Ctx> constexpr auto parse(Ctx& in) noexcept(false) -> typename Ctx::Iterator {
    auto it = AlternatePresentationFormatter::parse(in);
    underlyingFormatter.alternate = alternate;
    return it;
  }

  template <typename Ctx> auto format(VkQueueFamilyProperties const& properties, Ctx& ctx) const noexcept -> typename Ctx::Iterator {
    auto out = ctx.out();

    auto constexpr b0 = StringView{R"(VkQueueFamilyProperties{flags=)"};
    auto constexpr b1 = StringView{R"(, count=)"};
    auto constexpr b2 = StringView{R"(, timestampValidBits=)"};
    auto constexpr b3 = StringView{R"(, transferGranularity"=)"};
    auto constexpr b4 = StringView{R"(})"};

    out = impl::copy(b0.begin(), b0.end(), out);
    auto ctx1 = ctx.from(out);
    out = underlyingFormatter.format({properties.queueFlags}, ctx1);
    out = impl::copy(b1.begin(), b1.end(), out);
    auto ctx2 = ctx1.from(out);
    out = underlyingU32Formatter.format(properties.queueCount, ctx2);
    out = impl::copy(b2.begin(), b2.end(), out);
    auto ctx3 = ctx2.from(out);
    out = underlyingU32Formatter.format(properties.timestampValidBits, ctx3);
    out = impl::copy(b3.begin(), b3.end(), out);
    auto ctx4 = ctx3.from(out);
    out = underlyingExtent3DFormatter.format(properties.minImageTransferGranularity, ctx4);
    return impl::copy(b4.begin(), b4.end(), out);
  }

  Formatter<VulkanFormattedFlags<VkQueueFlagBits>> underlyingFormatter;
  Formatter<std::uint32_t> underlyingU32Formatter;
  Formatter<VkExtent3D> underlyingExtent3DFormatter;
};
#endif
