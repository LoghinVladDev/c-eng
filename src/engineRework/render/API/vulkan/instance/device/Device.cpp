//
// Created by loghin on 30.01.2022.
//

#include "Device.hpp"


using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)


#define C_ENG_MAP_START     NESTED_CLASS ( Builder, ENGINE_TYPE ( Device ), PARENT ( cds :: Object ) )
#include <ObjectMapping.hpp>

auto vulkan :: Self :: build () noexcept (false) -> Nester {
    return {};
}