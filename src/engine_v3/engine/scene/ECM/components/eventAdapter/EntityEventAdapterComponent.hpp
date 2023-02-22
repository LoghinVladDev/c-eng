//
// Created by loghin on 5/2/22.
//

#ifndef __C_ENG_ENTITY_EVENT_ADAPTER_COMPONENT_HPP__
#define __C_ENG_ENTITY_EVENT_ADAPTER_COMPONENT_HPP__

#include <Preprocess.hpp>
#include <Core.hpp>
#include <CDS/experimental/JSON>

#define C_ENG_MAP_START CLASS ( EntityEventAdapterComponent, ENGINE_PARENT ( EngineObject ) )
#include <ObjectMapping.hpp>

namespace engine {

    __C_ENG_PRE_DECLARE_CLASS ( EntityEventAdapter );

    Class {
        ClassDefs

        Const ( TYPE ( cds :: String ), typeKey, VALUE ( "type" ) )

        Field ( ENGINE_PRIMITIVE_TYPE ( EntityEventAdapter * ), adapter,    DEFAULT_VALUE ( nullptr ),  GET_DEFAULT,    SET_DEFAULT )

    public:
        virtual auto loadFrom ( cds :: json :: standard :: JsonObject const & ) noexcept -> Self & = 0;
        virtual auto dumpTo ( cds :: json :: standard :: JsonObject & ) noexcept -> Self & = 0;

        auto clear () noexcept -> Self & override = 0;

        NoDiscard auto copy () const noexcept -> Self * override = 0;
    };

}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif // __C_ENG_ENTITY_EVENT_ADAPTER_COMPONENT_HPP__
