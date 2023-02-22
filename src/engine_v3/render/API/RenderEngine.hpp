//
// Created by loghin on 28.12.2021.
//

#ifndef __C_ENG_RENDER_ENGINE_HPP__
#define __C_ENG_RENDER_ENGINE_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#include <Preprocess.hpp>
#include <RenderObject.hpp>
#include <Core.hpp>


#define C_ENG_MAP_START     CLASS ( RenderEngine, ENGINE_PARENT ( RenderObject ) )
#include <ObjectMapping.hpp>

namespace engine {

    Class {
        Field ( ENGINE_TYPE ( RenderInstanceSurfaceCallbackInfo ), renderInstanceSurfaceCallbacks, DEFAULT_VALUE (nullptr, nullptr, nullptr), GET_DEFAULT_PROTECTED, SET_INLINE ( setRenderSurfaceCallbacks ) );

    public:
        __C_ENG_NO_DISCARD virtual auto name () const noexcept -> cds :: StringLiteral = 0;
        virtual auto init () noexcept (false) -> Self & = 0;
        auto clear () noexcept (false) -> Self & override = 0;
        Destructor () noexcept override = default;
    };

}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#endif //__C_ENG_RENDER_ENGINE_HPP__
