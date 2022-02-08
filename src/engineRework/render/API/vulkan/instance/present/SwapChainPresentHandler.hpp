//
// Created by loghin on 07.02.2022.
//

#ifndef C_ENG_SWAPCHAINPRESENTHANDLER_HPP
#define C_ENG_SWAPCHAINPRESENTHANDLER_HPP


#include <Preprocess.hpp>
#include <PresentHandler.hpp>
#include <SwapChain.hpp>

#define C_ENG_MAP_START     CLASS ( SwapChainPresentHandler, ENGINE_PARENT ( PresentHandler ) )
#include <ObjectMapping.hpp>

namespace engine { // NOLINT(modernize-concat-nested-namespaces)
    namespace vulkan {

        Class {
            Field ( ENGINE_PRIMITIVE_TYPE ( SurfaceHandle ),    surface,    DEFAULT_VALUE ( nullptr ),  GET_DEFAULT, SET_NONE )
            Field ( ENGINE_TYPE ( SwapChain ),                  swapChain,  NO_INIT,                    GET_DEFAULT, SET_NONE )

        private:
            __C_ENG_FRIEND_CLASS ( SwapChain );
            Field ( PRIMITIVE_TYPE ( Parent :: SurfaceProperties const * ), surfaceProperties, DEFAULT_VALUE ( nullptr ),   GET_DEFAULT,    SET_NONE )

        public:
            explicit Constructor ( Type ( SurfaceHandle ) ) noexcept;

            auto init ( Type ( Device ) const * ) noexcept (false) -> Self & override;
            auto clear () noexcept -> Self & override;
            Destructor () noexcept override;
        };

    }
}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#endif //C_ENG_SWAPCHAINPRESENTHANDLER_HPP
