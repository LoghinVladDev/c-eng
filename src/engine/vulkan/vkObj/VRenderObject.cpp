//
// Created by loghin on 23.05.2021.
//

#include "VRenderObject.hpp"

#include <sstream>

auto engine::VRenderObject::toString() const noexcept -> String {
    std::stringstream oss;

    oss << "VRenderObject at 0x" << std::hex <<
        reinterpret_cast < AddressValueType > (this);

    return oss.str();
}