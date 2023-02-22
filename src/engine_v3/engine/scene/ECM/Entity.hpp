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
#include <KeyPressEvent.hpp>

#define C_ENG_MAP_START CLASS ( Entity, ENGINE_PARENT ( EngineObject ) )
#include <ObjectMapping.hpp>

namespace engine {

    __C_ENG_PRE_DECLARE_CLASS ( Scene );
    __C_ENG_PRE_DECLARE_CLASS ( Component );
    __C_ENG_PRE_DECLARE_CLASS ( Transform );
    __C_ENG_PRE_DECLARE_CLASS ( EntityEventAdapter );


    __C_ENG_PRE_DECLARE_CLASS ( ControllerAxisEvent );
    __C_ENG_PRE_DECLARE_CLASS ( ControllerButtonPressEvent );
    __C_ENG_PRE_DECLARE_CLASS ( ControllerButtonReleaseEvent );
    __C_ENG_PRE_DECLARE_CLASS ( ControllerHatEvent );

    __C_ENG_PRE_DECLARE_CLASS ( KeyPressEvent );
    __C_ENG_PRE_DECLARE_CLASS ( KeyReleaseEvent );

    __C_ENG_PRE_DECLARE_CLASS ( MouseMoveEvent );
    __C_ENG_PRE_DECLARE_CLASS ( MousePressEvent );
    __C_ENG_PRE_DECLARE_CLASS ( MouseReleaseEvent );
    __C_ENG_PRE_DECLARE_CLASS ( MouseScrollEvent );

    Class {
        Const ( TYPE ( cds :: String ),     typeKey,        VALUE ( "type" ) )
        Const ( TYPE ( cds :: String ),     nameKey,        VALUE ( "name" ) )
        Const ( TYPE ( cds :: String ),     childrenKey,    VALUE ( "children" ) )
        Const ( TYPE ( cds :: String ),     componentsKey,  VALUE ( "components" ) )

        ClassDefsNoPrefix

        friend class Type ( Scene );

        template < typename K >
        using ComponentTypeReducedFlagHasher = cds :: utility :: DefaultHashFunction < K, componentTypeReducedFlagMaxValue >;

        using ComponentMap = cds :: HashMap <
                ComponentTypeReducedFlag,
                Type ( Component )          *,
                ComponentTypeReducedFlagHasher < ComponentTypeReducedFlag >
        >;

        using OwnedEntities             = cds :: Array < cds :: UniquePointer < Type ( Entity ) > >;
        using ParentEntity              = Type ( Entity ) *;
        using ParentScene               = Type ( Scene ) *;

        using TransformType             = Type ( Transform ) *;
        using EntityEventAdapterType    = Type ( EntityEventAdapter ) *;

        Field ( PRIMITIVE_TYPE ( ParentEntity ),            parent,         DEFAULT_VALUE ( nullptr ),  GET_DEFAULT, SET_NONE )
        Field ( PRIMITIVE_TYPE ( ParentScene ),             scene,          DEFAULT_VALUE ( nullptr ),  GET_DEFAULT, SET_NONE )
        Field ( TYPE ( OwnedEntities ),                     children,       NO_INIT,                    GET_DEFAULT, SET_NONE )
        Field ( TYPE ( ComponentMap ),                      components,     NO_INIT,                    GET_NONE,    SET_NONE )
        Field ( TYPE ( cds :: String ),                     name,           NO_INIT,                    GET_DEFAULT, SET_DEFAULT )

        Field ( PRIMITIVE_TYPE ( TransformType ),           transform,      DEFAULT_VALUE ( nullptr ),  GET_DEFAULT, SET_NONE )
        Field ( PRIMITIVE_TYPE ( EntityEventAdapterType ),  eventAdapter,   DEFAULT_VALUE ( nullptr ),  GET_DEFAULT, SET_NONE )

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

        auto add ( Type ( Entity ) * ) noexcept -> Self &;
        virtual auto add ( Type ( Component ) * ) noexcept -> Self &;

        auto remove ( Type ( Entity ) * ) noexcept -> Self &;
        virtual auto remove ( Type ( Component ) * ) noexcept -> Self &;

        auto clear () noexcept -> Self & override;

        inline virtual auto controllerAxisEvent ( Type ( ControllerAxisEvent ) * ) noexcept -> void { /* empty, override in specific object if adding EventAdapter */ }
        inline virtual auto controllerButtonPressEvent ( Type ( ControllerButtonPressEvent ) * ) noexcept -> void { /* empty, override in specific object if adding EventAdapter */ }
        inline virtual auto controllerButtonReleaseEvent ( Type ( ControllerButtonReleaseEvent ) * ) noexcept -> void { /* empty, override in specific object if adding EventAdapter */ }
        inline virtual auto controllerHatEvent ( Type ( ControllerHatEvent ) * ) noexcept -> void { /* empty, override in specific object if adding EventAdapter */ }

        inline virtual auto keyPressEvent ( Type ( KeyPressEvent ) * pEvent ) noexcept -> void { /* empty, override in specific object if adding EventAdapter */ }

        inline virtual auto keyReleaseEvent ( Type ( KeyReleaseEvent ) * ) noexcept -> void { /* empty, override in specific object if adding EventAdapter */ }

        inline virtual auto mouseMoveEvent ( Type ( MouseMoveEvent ) * ) noexcept -> void { /* empty, override in specific object if adding EventAdapter */ }
        inline virtual auto mousePressEvent ( Type ( MousePressEvent ) * ) noexcept -> void { /* empty, override in specific object if adding EventAdapter */ }
        inline virtual auto mouseReleaseEvent ( Type ( MouseReleaseEvent ) * ) noexcept -> void { /* empty, override in specific object if adding EventAdapter */ }
        inline virtual auto mouseScrollEvent ( Type ( MouseScrollEvent ) * ) noexcept -> void { /* empty, override in specific object if adding EventAdapter */ }
    };

}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#endif // __C_ENG_ENTITY_HPP__
