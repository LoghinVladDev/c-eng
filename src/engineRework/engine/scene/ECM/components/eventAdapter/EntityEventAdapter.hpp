//
// Created by loghin on 5/2/22.
//

#ifndef __C_ENG_ENTITY_EVENT_ADAPTER_HPP__
#define __C_ENG_ENTITY_EVENT_ADAPTER_HPP__

#include <Preprocess.hpp>
#include <scene/ECM/Component.hpp>
#include <scene/ECM/components/eventAdapter/component/EntityEventAdapterControllerComponent.hpp>
#include <scene/ECM/components/eventAdapter/component/EntityEventAdapterKeyComponent.hpp>
#include <scene/ECM/components/eventAdapter/component/EntityEventAdapterMouseComponent.hpp>

#define C_ENG_MAP_START CLASS ( EntityEventAdapter, ENGINE_PARENT ( Component ) )
#include <ObjectMapping.hpp>

namespace engine {

    Class {
        ClassDefs

        Const ( TYPE ( cds :: String ), controllerAdapterKey,   VALUE ( "controllerEventAdapter" ) )
        Const ( TYPE ( cds :: String ), keyAdapterKey,          VALUE ( "keyEventAdapter" ) )
        Const ( TYPE ( cds :: String ), mouseAdapterKey,        VALUE ( "mouseEventAdapter" ) )

        using MouseEventAdapterComponentType        = Type ( EntityEventAdapterMouseComponent ) *;
        using KeyEventAdapterComponentType          = Type ( EntityEventAdapterKeyComponent ) *;
        using ControllerEventAdapterComponentType   = Type ( EntityEventAdapterControllerComponent ) *;

        Field ( PRIMITIVE_TYPE ( MouseEventAdapterComponentType ),      mouseEventAdapter,      DEFAULT_VALUE ( nullptr ),  GET_DEFAULT,   SET_NONE )
        Field ( PRIMITIVE_TYPE ( KeyEventAdapterComponentType ),        keyEventAdapter,        DEFAULT_VALUE ( nullptr ),  GET_DEFAULT,   SET_NONE )
        Field ( PRIMITIVE_TYPE ( ControllerEventAdapterComponentType ), controllerEventAdapter, DEFAULT_VALUE ( nullptr ),  GET_DEFAULT,   SET_NONE )

    public:
        NoDiscard constexpr auto type () const noexcept -> Type ( ComponentTypeFlag ) override {
            return ComponentTypeFlagEntityEventAdapter;
        }

        auto loadFrom ( cds :: json :: standard :: JsonObject const & ) noexcept -> Self & override;
        auto dumpTo ( cds :: json :: standard :: JsonObject & ) noexcept -> Self & override;

        NoDiscard auto copy () const noexcept -> Self * override;

        auto clear () noexcept -> Self & override;

        auto setMouseComponent ( MouseEventAdapterComponentType ) noexcept -> Self &;
        auto setKeyComponent ( KeyEventAdapterComponentType ) noexcept -> Self &;
        auto setControllerComponent ( ControllerEventAdapterComponentType ) noexcept -> Self &;

        Constructor () noexcept = default;
        Constructor ( Self const & ) noexcept;
        Constructor ( Self && ) noexcept;

        auto operator = ( Self const & ) noexcept -> Self &;
        auto operator = ( Self && ) noexcept -> Self &;

        Destructor () noexcept override;
    };

}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#endif // __C_ENG_ENTITY_EVENT_ADAPTER_HPP__
