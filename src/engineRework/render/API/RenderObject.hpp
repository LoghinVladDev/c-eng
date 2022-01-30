//
// Created by loghin on 30.01.2022.
//

#ifndef __C_ENG_RENDER_OBJECT_HPP__
#define __C_ENG_RENDER_OBJECT_HPP__

#include <Preprocess.hpp>
#include <CDS/Object>

#define C_ENG_MAP_START     CLASS ( RenderObject, PARENT ( cds :: Object ) )
#include <ObjectMapping.hpp>


namespace engine {

    Class {
    public:
        virtual auto clear () noexcept (false) -> Self & = 0;
        Destructor () noexcept override = default;
    };

}


#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif //__C_ENG_RENDER_OBJECT_HPP__
