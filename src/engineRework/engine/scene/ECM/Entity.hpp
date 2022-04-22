//
// Created by loghin on 4/6/22.
//

#ifndef __C_ENG_ENTITY_HPP__
#define __C_ENG_ENTITY_HPP__

#include <Preprocess.hpp>
#include <Core.hpp>
#include <CDS/Array>
#include <CDS/HashMap>
#include <CDS/experimental/JSON>

#define C_ENG_MAP_START CLASS ( Entity, ENGINE_PARENT ( EngineObject ) )
#include <ObjectMapping.hpp>

namespace engine {

    __C_ENG_PRE_DECLARE_CLASS ( Scene );
    __C_ENG_PRE_DECLARE_CLASS ( Component );

    Class {
        ClassDefs

        Const ( TYPE ( cds :: String ),     typeKey,        VALUE ( "type" ) )
        Const ( TYPE ( cds :: String ),     nameKey,        VALUE ( "name" ) )
        Const ( TYPE ( cds :: String ),     childrenKey,    VALUE ( "children" ) )
        Const ( TYPE ( cds :: String ),     componentsKey,  VALUE ( "components" ) )

    private:
        friend class Type ( Scene );

        template < typename K >
        using ComponentTypeReducedFlagHasher = cds :: utility :: DefaultHashFunction < K, componentTypeReducedFlagMaxValue >;

        using ComponentMap = cds :: HashMap <
                ComponentTypeReducedFlag,
                Type ( Component )          *,
                ComponentTypeReducedFlagHasher < ComponentTypeReducedFlag >
        >;

        using OwnedEntities = cds :: Array < cds :: UniquePointer < Type ( Entity ) > >;
        using ParentEntity  = cds :: ForeignPointer < Type ( Entity ) >;
        using ParentScene   = cds :: ForeignPointer < Type ( Scene ) >;

        Field ( TYPE ( ParentEntity ),              parent,     DEFAULT_VALUE ( nullptr ),  GET_DEFAULT, SET_NONE )
        Field ( TYPE ( ParentScene ),               scene,      DEFAULT_VALUE ( nullptr ),  GET_DEFAULT, SET_NONE )
        Field ( TYPE ( OwnedEntities ),             children,   NO_INIT,                    GET_DEFAULT, SET_NONE )
        Field ( TYPE ( ComponentMap ),              components, NO_INIT,                    GET_NONE,    SET_NONE )
        Field ( TYPE ( cds :: String ),             name,       NO_INIT,                    GET_DEFAULT, SET_DEFAULT )

    public:
        Constructor () noexcept = default;
        Constructor ( Self const & ) noexcept;
        Constructor ( Self && ) noexcept;
        Destructor () noexcept;

        auto operator = ( Self const & ) noexcept -> Self &;
        auto operator = ( Self && ) noexcept -> Self &;

        virtual auto loadFrom ( cds :: json :: standard :: JsonObject const & ) noexcept -> Self &;
        virtual auto dumpTo ( cds :: json :: standard :: JsonObject & json ) noexcept -> Self const &;

        auto static instantiateByClassName ( cds :: String const & ) noexcept (false) -> cds :: UniquePointer < Type ( Entity ) >;

        auto addChild ( cds :: UniquePointer < Type ( Entity ) > && ) noexcept -> Self &;

        auto clear () noexcept -> Self & override;
    };

}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#endif // __C_ENG_ENTITY_HPP__
