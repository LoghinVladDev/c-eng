//
// Created by loghin on 28.12.2021.
//

#ifndef __C_ENG_RENDERAPI_HPP
#define __C_ENG_RENDERAPI_HPP

#include <Preprocess.hpp>
#include <CDS/Object>
#include <Core.hpp>


#define C_ENG_MAP_START     CLASS ( RenderEngine, PARENT ( cds :: Object ) )
#include <ObjectMapping.hpp>

namespace engine {

    Class {
        Field ( ENGINE_TYPE ( RenderInstanceSurfaceCallbackInfo ), renderInstanceSurfaceCallbacks, DEFAULT_VALUE (nullptr, nullptr, nullptr), GET_DEFAULT_PROTECTED, SET_INLINE ( setRenderSurfaceCallbacks ) );

    public:
        __C_ENG_NO_DISCARD virtual auto name () const noexcept -> cds :: StringLiteral = 0;
        virtual auto init () noexcept (false) -> Self & = 0;
        virtual auto clear () noexcept (false) -> Self & = 0;
        Destructor () noexcept override = default;
    };

}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#endif //__C_ENG_RENDERAPI_HPP
