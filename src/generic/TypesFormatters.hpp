//
// Created by loghin on 10/27/24.
//

#pragma once

#include <cds/Format>
#include <cds/StringView>
#include "Types.hpp"

namespace c_eng {
constexpr auto toString(generic::LicenceType const type) noexcept -> cds::StringView {
  switch (type) {
    case generic::LicenceType::Apache2_0: return "Apache2_0";
    case generic::LicenceType::Proprietary: return "Proprietary";
    case generic::LicenceType::Zlib: return "Zlib";
    default:
      assert(false && "Unhandled generic::LicenceType type");
      return "<<Unhandled generic::LicenceType>>";
  }
}
}

template <typename C> struct cds::Formatter<c_eng::generic::LicenceType, C> {
  template <typename Ctx> auto format(c_eng::generic::LicenceType const type, Ctx& ctx) const noexcept -> typename Ctx::Iterator {
    auto const asStr = c_eng::toString(type);
    return impl::copy(asStr.begin(), asStr.end(), ctx.out());
  }
};

template <typename C> struct cds::Formatter<c_eng::generic::Version, C> {
  template <typename Ctx> auto format(c_eng::generic::Version const& version, Ctx& ctx) const noexcept -> typename Ctx::Iterator {
    Formatter<U32, C> u32Formatter;

    impl::fmt::FormatParseContext<C, impl::StringUtils<C, impl::StringTraits<C>>> pCtx{""};
    u32Formatter.parse(pCtx);

    auto constexpr b0 = StringView{R"(Version{variant=")"};
    auto constexpr b1 = StringView{R"(", major=)"};
    auto constexpr b2 = StringView{R"(", minor=)"};
    auto constexpr b3 = StringView{R"(", patch"=)"};
    auto constexpr b4 = StringView{R"("})"};
    auto out = impl::copy(b0.begin(), b0.end(), ctx.out());
    auto ctx1 = ctx.from(out);
    out = u32Formatter.format(version.variant, ctx1);
    out = impl::copy(b1.begin(), b1.end(), out);
    auto ctx2 = ctx1.from(out);
    out = u32Formatter.format(version.major, ctx2);
    out = impl::copy(b2.begin(), b2.end(), out);
    auto ctx3 = ctx2.from(out);
    out = u32Formatter.format(version.minor, ctx3);
    out = impl::copy(b3.begin(), b3.end(), out);
    auto ctx4 = ctx3.from(out);
    out = u32Formatter.format(version.patch, ctx4);
    return impl::copy(b4.begin(), b4.end(), out);
  }
};
