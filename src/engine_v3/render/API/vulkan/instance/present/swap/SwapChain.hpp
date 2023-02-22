//
// Created by loghin on 03.02.2022.
//

#ifndef __C_ENG_SWAP_CHAIN_HPP__
#define __C_ENG_SWAP_CHAIN_HPP__


#include <Preprocess.hpp>
#include <VulkanRenderObject.hpp>
#include <VulkanCore.hpp>


#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SWAP_CHAIN_AVAILABLE
#define C_ENG_MAP_START     CLASS ( SwapChain,  ENGINE_PARENT ( VulkanRenderObject ) )
#include <ObjectMapping.hpp>

namespace engine { // NOLINT(modernize-concat-nested-namespaces)
    namespace vulkan {

        __C_ENG_PRE_DECLARE_CLASS ( Device );

        Class {
        public:
            struct Images {
                Type ( ImageHandle )  * pImages;
                cds :: uint32           count;
            };

            struct Properties {
                Type ( Extent2D )   imageExtent;
                Type ( Format )     imageFormat;
            };

            Field ( ENGINE_PRIMITIVE_TYPE ( SwapChainHandle ),  handle,     DEFAULT_VALUE ( nullptr ),  GET_DEFAULT,    SET_NONE )
            Field ( ENGINE_PRIMITIVE_TYPE ( Device const * ),   device,     DEFAULT_VALUE ( nullptr ),  GET_DEFAULT,    SET_NONE )
            Field ( TYPE ( Images ),                            images,     DEFAULT_VALUE ( nullptr, 0U ),  GET_DEFAULT,    SET_NONE )
            Field ( TYPE ( Properties ),                        properties, DEFAULT_VALUE ( { 0U, 0U }, FormatUndefined ),     GET_DEFAULT,    SET_NONE )

        private:
            auto reserveAndAcquireImages () noexcept (false) -> Self &;
            auto freeImages () noexcept -> Self &;

        public:
            auto init ( Type ( Device ) const *, Type ( SurfaceHandle ) ) noexcept (false) -> Self &;
            auto clear () noexcept -> Self & override;
            Destructor () noexcept override;
        };

    }
}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#endif //__C_ENG_SWAP_CHAIN_HPP__
