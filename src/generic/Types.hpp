//
// Created by loghin on 10/27/24.
//

#pragma once

#include <cds/Optional>
#include <cds/StringView>

namespace c_eng::generic::detail {
using cds::Optional;
using cds::StringView;
using cds::U32;
using cds::Size;
using cds::SSize;

enum class LicenceType {
  Proprietary,
  Zlib,
  Apache2_0
};

struct Version {
  U32 variant;
  U32 major;
  U32 minor;
  U32 patch;

  static constexpr U32 baselineVariant = 0u;
};

struct ApiInfo {
  StringView name;
  Optional<StringView> description;
  Optional<StringView> vendor;
  Optional<U32> vendorId;
  Optional<LicenceType> licenceType;
};

struct Point2D {
  SSize x;
  SSize y;
};

struct Area2D {
  Size width;
  Size height;
};

struct Rect2D {
  Point2D position;
  Area2D area;
};

struct ColorChannelsDepth {
  Size redBitDepth;
  Size greenBitDepth;
  Size blueBitDepth;
};

struct DisplayVideoMode {
  Area2D area;
  ColorChannelsDepth colorDepth;
  Size refreshRate;
};

struct Scale2DF {
  float x;
  float y;
};
} // namespace c_eng::generic::detail

namespace c_eng::generic {
using detail::LicenceType;
using detail::Version;
using detail::ApiInfo;
using detail::DisplayVideoMode;
using detail::Scale2DF;
using detail::Area2D;
using detail::Rect2D;
using detail::Point2D;
using detail::ColorChannelsDepth;
} // namespace c_eng::generic
