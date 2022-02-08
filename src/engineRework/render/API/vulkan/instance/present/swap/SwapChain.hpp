//
// Created by loghin on 03.02.2022.
//

#ifndef __C_ENG_SWAP_CHAIN_HPP__
#define __C_ENG_SWAP_CHAIN_HPP__


#include <Preprocess.hpp>
#include <VulkanRenderObject.hpp>
#include <VulkanCore.hpp>


#define C_ENG_MAP_START     CLASS ( SwapChain,  ENGINE_PARENT ( VulkanRenderObject ) )
#include <ObjectMapping.hpp>

namespace engine { // NOLINT(modernize-concat-nested-namespaces)
    namespace vulkan {

        __C_ENG_PRE_DECLARE_CLASS ( Device );

        Class {
        private:
            Field ( ENGINE_PRIMITIVE_TYPE ( SwapChainHandle ),  handle, DEFAULT_VALUE ( nullptr ),  GET_DEFAULT,    SET_NONE )
            Field ( ENGINE_PRIMITIVE_TYPE ( Device const * ),   device, DEFAULT_VALUE ( nullptr ),  GET_DEFAULT,    SET_NONE )

        public:
            auto init ( Type ( Device ) const *, Type ( SurfaceHandle ) ) noexcept (false) -> Self &;
            auto clear () noexcept -> Self & override;
            Destructor () noexcept override;
        };

    }
}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#endif //__C_ENG_SWAP_CHAIN_HPP__
