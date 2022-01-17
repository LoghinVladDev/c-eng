//
// Created by loghin on 28.12.2021.
//

#ifndef __C_ENG_RENDER_ENGINE_TYPES_HPP__
#define __C_ENG_RENDER_ENGINE_TYPES_HPP__


#include <CDS/Exception>


#define C_ENG_MAP_START     CLASS ( RenderEngineAPIException, PARENT ( cds :: Exception ) )
#include <ObjectMapping.hpp>

namespace engine {

    Class {
    public:
        explicit Constructor ( cds :: String const & message = "" ) :
                Parent ( "Render Engine Exception : " + message ) {

        }
    };

}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#endif //__C_ENG_RENDER_ENGINE_TYPES_HPP__
