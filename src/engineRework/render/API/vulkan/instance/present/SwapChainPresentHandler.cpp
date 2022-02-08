//
// Created by loghin on 07.02.2022.
//

#include "SwapChainPresentHandler.hpp"
#include <Device.hpp>
#include <PhysicalDevice.hpp>

using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace vulkan; // NOLINT(clion-misra-cpp2008-7-3-4)

#define C_ENG_MAP_START     CLASS ( SwapChainPresentHandler, ENGINE_PARENT ( PresentHandler ) )
#include <ObjectMapping.hpp>

auto Self :: init (
        Type ( Device ) const * pDevice
) noexcept (false) -> Self & {

    (void) this->_swapChain.init ( pDevice, this->_surface );

    return * this;
}

auto Self :: clear () noexcept -> Self & {
    (void) this->_swapChain.clear();
    return * this;
}

Self :: Destructor () noexcept {
    (void) this->Self :: clear();
}

Self :: Constructor (
        Type ( SurfaceHandle ) handle
) noexcept :
        _surface ( handle ) {

}
