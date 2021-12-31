//
// Created by loghin on 31.12.2021.
//

#include "Allocator.hpp"


using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)


#define C_ENG_MAP_START     CLASS ( Allocator,  PARENT ( cds :: Object ) )
#include <ObjectMapping.hpp>

auto vulkan :: Self :: instance () noexcept -> Self & {
    static Self instance;
    return instance;
}