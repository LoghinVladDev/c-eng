//
// Created by loghin on 28.12.2021.
//

#ifndef C_ENG_RENDERENGINETYPES_HPP
#define C_ENG_RENDERENGINETYPES_HPP


#include <CDS/Exception>


#define C_ENG_MAP_START     CLASS ( RenderEngineAPIException, EXTERNAL_PARENT ( cds :: Exception ) )
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


#endif //C_ENG_RENDERENGINETYPES_HPP
