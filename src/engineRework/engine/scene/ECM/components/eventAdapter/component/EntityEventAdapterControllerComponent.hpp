//
// Created by loghin on 5/2/22.
//

#ifndef __C_ENG_ENTITY_EVENT_ADAPTER_CONTROLLER_COMPONENT_HPP__
#define __C_ENG_ENTITY_EVENT_ADAPTER_CONTROLLER_COMPONENT_HPP__

#include <Preprocess.hpp>
#include <Core.hpp>
#include <CDS/experimental/JSON>
#include <CDS/pointer/UniquePointer>
#include <scene/ECM/components/eventAdapter/EntityEventAdapterComponent.hpp>

#define C_ENG_MAP_START CLASS ( EntityEventAdapterControllerComponent, ENGINE_PARENT ( EntityEventAdapterComponent ) )
#include <ObjectMapping.hpp>

namespace engine {

    __C_ENG_PRE_DECLARE_CLASS ( ControllerAxisEvent );
    __C_ENG_PRE_DECLARE_CLASS ( ControllerButtonPressEvent );
    __C_ENG_PRE_DECLARE_CLASS ( ControllerButtonReleaseEvent );
    __C_ENG_PRE_DECLARE_CLASS ( ControllerHatEvent );

    __C_ENG_PRE_DECLARE_CLASS ( RawControllerInputEntityEventAdapterComponent );

    Class {
    ClassDefs

    public:
        template < Type ( EntityEventAdapterControllerComponentType ) type, typename = void >
        struct Properties {
            using AdapterType = void;
        };

        template < >
        struct Properties < EntityEventAdapterControllerComponentTypeRawInput > {
            using AdapterType = Type ( RawControllerInputEntityEventAdapterComponent );
        };

        NoDiscard __CDS_cpplang_VirtualConstexpr virtual auto type () const noexcept -> Type ( EntityEventAdapterControllerComponentType ) {
            return EntityEventAdapterControllerComponentTypeCustom;
        }

        auto loadFrom ( cds :: json :: standard :: JsonObject const & ) noexcept -> Self & override = 0;
        auto dumpTo ( cds :: json :: standard :: JsonObject & ) noexcept -> Self & override;

        auto static instantiate ( cds :: json :: standard :: JsonObject const & ) noexcept (false) -> cds :: UniquePointer < Self >;
        auto static instantiate ( Type ( EntityEventAdapterControllerComponentType ) ) noexcept (false) -> cds :: UniquePointer < Self >;

        auto clear () noexcept -> Self & override = 0;

        NoDiscard auto copy () const noexcept -> Self * override = 0;

        virtual auto controllerAxisEvent ( Type ( ControllerAxisEvent ) * ) noexcept -> void = 0;
        virtual auto controllerButtonPressEvent ( Type ( ControllerButtonPressEvent ) * ) noexcept -> void = 0;
        virtual auto controllerButtonReleaseEvent ( Type ( ControllerButtonReleaseEvent ) * ) noexcept -> void = 0;
        virtual auto controllerHatEvent ( Type ( ControllerHatEvent ) * ) noexcept -> void = 0;

        template < Type ( EntityEventAdapterControllerComponentType ) type >
        NoDiscard constexpr auto cast () const noexcept -> typename Properties < type > :: AdapterType const * {
            if ( this->type() != type ) {
                return nullptr;
            }

            return reinterpret_cast < typename Properties < type > :: AdapterType const * > ( this );
        }

        template < Type ( EntityEventAdapterControllerComponentType ) type >
        NoDiscard constexpr auto cast () noexcept -> typename Properties < type > :: AdapterType * {
            if ( this->type() != type ) {
                return nullptr;
            }

            return reinterpret_cast < typename Properties < type > :: AdapterType * > ( this );
        }
    };

}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif // __C_ENG_ENTITY_EVENT_ADAPTER_CONTROLLER_COMPONENT_HPP__
