//
// Created by loghin on 23.05.2021.
//

#include "VRenderObject.hpp"

#include <sstream>

using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)

auto VRenderObject :: toString() const noexcept -> String {
    std::stringstream oss;

    oss << "VRenderObject at 0x" << std::hex <<
        reinterpret_cast < AddressValueType const > (this);

    return oss.str();
}