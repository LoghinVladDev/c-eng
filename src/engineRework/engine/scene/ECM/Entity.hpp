//
// Created by loghin on 4/6/22.
//

#ifndef __C_ENG_ENTITY_HPP__
#define __C_ENG_ENTITY_HPP__

#include <Preprocess.hpp>
#include <CDS/Array>
#include <CDS/HashMap>
#include <CDS/experimental/JSON>
#include <scene/ECM/Component.hpp>

#define C_ENG_MAP_START CLASS ( Entity, ENGINE_PARENT ( EngineObject ) )
#include <ObjectMapping.hpp>

namespace engine {

    __C_ENG_PRE_DECLARE_CLASS ( Scene );

    Class {
        ClassDefs

        using ComponentTypeReducedFlag = cds :: uint32;

        using ComponentMap = cds :: HashMap <
                ComponentTypeReducedFlag,
                Type ( Component )          *,
                cds :: utility :: HighCollisionDefaultHashFunction < ComponentTypeReducedFlag >
        >;

        Field ( ENGINE_PRIMITIVE_TYPE ( Entity * ),             parent,     DEFAULT_VALUE ( nullptr ),  GET_DEFAULT, SET_NONE )
        Field ( TYPE ( cds :: Array < Type ( Entity ) * > ),    children,   NO_INIT,                    GET_DEFAULT, SET_NONE )
        Field ( TYPE ( ComponentMap ),                          components, NO_INIT,                    GET_NONE,    SET_NONE )

    public:
        auto loadFrom ( cds :: json :: standard :: JsonObject const & ) noexcept -> Self &;
        auto dumpTo ( cds :: json :: standard :: JsonObject & json ) noexcept -> Self &;
    };

}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#endif // __C_ENG_ENTITY_HPP__
