//
// Created by loghin on 23.05.2021.
//

#include "VObject.hpp"

#include <sstream>

using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)

auto engine::VObject::toString() const noexcept -> String {
    std::stringstream oss;

    oss << "VObject at 0x" << std::hex <<
        reinterpret_cast < AddressValueType const > (this);

    return oss.str();
}