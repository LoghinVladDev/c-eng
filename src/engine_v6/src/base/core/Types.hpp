//
// Created by Vlad-Andrei Loghin on 14.06.23.
//

#ifndef C_ENG_TYPES_HPP
#define C_ENG_TYPES_HPP

#include <CDS/Types>
#include <CDS/Limits>

namespace engine {
struct Version {
  cds::uint32 variant;
  cds::uint32 major;
  cds::uint32 minor;
  cds::uint32 patch;
};

namespace variant {
constexpr static cds::uint32 const original = 0;
constexpr static cds::uint32 const forked = 1;
}

namespace version {
constexpr static cds::uint32 const unspecified = cds::limits::U32_MAX;
}
} // namespace engine

#endif //C_ENG_TYPES_HPP
