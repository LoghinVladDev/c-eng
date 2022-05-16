//
// Created by loghin on 5/2/22.
//

#ifndef __C_ENG_ENTITY_EVENT_ADAPTER_KEY_COMPONENT_HPP__
#define __C_ENG_ENTITY_EVENT_ADAPTER_KEY_COMPONENT_HPP__

#include <Preprocess.hpp>
#include <Core.hpp>
#include <CDS/experimental/JSON>
#include <CDS/smartPointers/UniquePointer>
#include <scene/ECM/components/eventAdapter/EntityEventAdapterComponent.hpp>

#define C_ENG_MAP_START CLASS ( EntityEventAdapterKeyComponent, ENGINE_PARENT ( EntityEventAdapterComponent ) )
#include <ObjectMapping.hpp>

namespace engine {

    __C_ENG_PRE_DECLARE_CLASS ( KeyPressEvent );
    __C_ENG_PRE_DECLARE_CLASS ( KeyReleaseEvent );

    __C_ENG_PRE_DECLARE_CLASS ( RawKeyInputEntityEventAdapterComponent );

    Class {
    ClassDefs

    public:
        template < Type ( EntityEventAdapterKeyComponentType ) type, typename = void >
        struct Properties {
            using AdapterType = void;
        };

        template < >
        struct Properties < EntityEventAdapterKeyComponentTypeRawInput > {
            using AdapterType = Type ( RawKeyInputEntityEventAdapterComponent );
        };

        NoDiscard __CDS_cpplang_VirtualConstexpr virtual auto type () const noexcept -> Type ( EntityEventAdapterKeyComponentType ) {
            return EntityEventAdapterKeyComponentTypeCustom;
        }

        auto loadFrom ( cds :: json :: standard :: JsonObject const & ) noexcept -> Self & override = 0;
        auto dumpTo ( cds :: json :: standard :: JsonObject & ) noexcept -> Self & override;

        auto static instantiate ( cds :: json :: standard :: JsonObject const & ) noexcept (false) -> cds :: UniquePointer < Self >;
        auto static instantiate ( Type ( EntityEventAdapterKeyComponentType ) ) noexcept (false) -> cds :: UniquePointer < Self >;

        auto clear () noexcept -> Self & override = 0;

        NoDiscard auto copy () const noexcept -> Self * override = 0;

        virtual auto keyPressEvent ( Type ( KeyPressEvent ) * ) noexcept -> void = 0;
        virtual auto keyReleaseEvent ( Type ( KeyReleaseEvent ) * ) noexcept -> void = 0;

        template < Type ( EntityEventAdapterKeyComponentType ) type >
        NoDiscard constexpr auto cast () const noexcept -> typename Properties < type > :: AdapterType const * {
            if ( this->type() != type ) {
                return nullptr;
            }

            return reinterpret_cast < typename Properties < type > :: AdapterType const * > ( this );
        }

        template < Type ( EntityEventAdapterKeyComponentType ) type >
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

#endif // __C_ENG_ENTITY_EVENT_ADAPTER_KEY_COMPONENT_HPP__
