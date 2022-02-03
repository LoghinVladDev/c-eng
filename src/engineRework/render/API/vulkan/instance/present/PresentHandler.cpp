//
// Created by loghin on 03.02.2022.
//

#include "PresentHandler.hpp"

using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace vulkan; // NOLINT(clion-misra-cpp2008-7-3-4)

#define C_ENG_MAP_START     CLASS ( PresentHandler, ENGINE_PARENT ( VulkanRenderObject ) )
#include <ObjectMapping.hpp>

auto Self :: clear () noexcept -> Self & {
    return * this;
}

Self :: Destructor () noexcept {
    (void) this-> Self :: clear();
}