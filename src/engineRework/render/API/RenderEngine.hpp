//
// Created by loghin on 28.12.2021.
//

#ifndef __C_ENG_RENDERAPI_HPP
#define __C_ENG_RENDERAPI_HPP

#include <Preprocess.hpp>
#include <CDS/Object>


#define C_ENG_MAP_START     CLASS ( RenderEngine, PARENT ( cds :: Object ) )
#include <ObjectMapping.hpp>

namespace engine {

    Class {
    public:
        __C_ENG_NO_DISCARD virtual auto name () const noexcept -> cds :: StringLiteral = 0;
        virtual auto init () noexcept (false) -> Self & = 0;
        Destructor () noexcept override = default;
    };

}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#endif //__C_ENG_RENDERAPI_HPP
