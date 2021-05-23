//
// Created by loghin on 23.05.2021.
//

#include "VObject.hpp"

#include <sstream>

auto engine::VObject::toString() const noexcept -> String {
    std::stringstream oss;

    oss << "VObject at 0x" << std::hex <<
        reinterpret_cast < AddressValueType > (this);

    return oss.str();
}