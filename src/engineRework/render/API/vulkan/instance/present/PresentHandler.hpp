//
// Created by loghin on 03.02.2022.
//

#ifndef __C_ENG_PRESENT_HANDLER_HPP__
#define __C_ENG_PRESENT_HANDLER_HPP__


#include <Preprocess.hpp>
#include <VulkanRenderObject.hpp>
#include <VulkanCore.hpp>


#define C_ENG_MAP_START     CLASS ( PresentHandler, ENGINE_PARENT ( VulkanRenderObject ) )
#include <ObjectMapping.hpp>

namespace engine { // NOLINT(modernize-concat-nested-namespaces)
    namespace vulkan {

        __C_ENG_PRE_DECLARE_CLASS ( Device );

        Class {
            Field ( ENGINE_PRIMITIVE_TYPE ( SurfaceHandle const * ),    surface,    DEFAULT_VALUE ( nullptr ),  GET_DEFAULT, SET_NONE )

        public:
            auto init ( Type ( Device ) const * );
            auto clear () noexcept -> Self & override;
            Destructor () noexcept override;
        };

    }
}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#endif //__C_ENG_PRESENT_HANDLER_HPP__
