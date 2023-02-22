//
// Created by loghin on 5/2/22.
//

#ifndef __C_ENG_ENTITY_EVENT_ADAPTER_MOUSE_COMPONENT_HPP__
#define __C_ENG_ENTITY_EVENT_ADAPTER_MOUSE_COMPONENT_HPP__

#include <Preprocess.hpp>
#include <Core.hpp>
#include <CDS/experimental/JSON>
#include <CDS/smartPointers/UniquePointer>
#include <scene/ECM/components/eventAdapter/EntityEventAdapterComponent.hpp>

#define C_ENG_MAP_START CLASS ( EntityEventAdapterMouseComponent, ENGINE_PARENT ( EntityEventAdapterComponent ) )
#include <ObjectMapping.hpp>

namespace engine {

    __C_ENG_PRE_DECLARE_CLASS ( MouseMoveEvent );
    __C_ENG_PRE_DECLARE_CLASS ( MousePressEvent );
    __C_ENG_PRE_DECLARE_CLASS ( MouseReleaseEvent );
    __C_ENG_PRE_DECLARE_CLASS ( MouseScrollEvent );

    __C_ENG_PRE_DECLARE_CLASS ( RawMouseInputEntityEventAdapterComponent );

    Class {
    ClassDefs

    public:
        template < Type ( EntityEventAdapterMouseComponentType ) type, typename = void >
        struct Properties {
            using AdapterType = void;
        };

        template < >
        struct Properties < EntityEventAdapterMouseComponentTypeRawInput > {
            using AdapterType = Type ( RawMouseInputEntityEventAdapterComponent );
        };

        NoDiscard __CDS_cpplang_VirtualConstexpr virtual auto type () const noexcept -> Type ( EntityEventAdapterMouseComponentType ) {
            return EntityEventAdapterMouseComponentTypeCustom;
        }

        auto loadFrom ( cds :: json :: standard :: JsonObject const & ) noexcept -> Self & override = 0;
        auto dumpTo ( cds :: json :: standard :: JsonObject & ) noexcept -> Self & override;

        auto static instantiate ( cds :: json :: standard :: JsonObject const & ) noexcept (false) -> cds :: UniquePointer < Self >;
        auto static instantiate ( Type ( EntityEventAdapterMouseComponentType ) ) noexcept (false) -> cds :: UniquePointer < Self >;

        auto clear () noexcept -> Self & override = 0;

        NoDiscard auto copy () const noexcept -> Self * override = 0;

        virtual auto mouseMoveEvent ( Type ( MouseMoveEvent ) * ) noexcept -> void = 0;
        virtual auto mousePressEvent ( Type ( MousePressEvent ) * ) noexcept -> void = 0;
        virtual auto mouseReleaseEvent ( Type ( MouseReleaseEvent ) * ) noexcept -> void = 0;
        virtual auto mouseScrollEvent ( Type ( MouseScrollEvent ) * ) noexcept -> void = 0;

        template < Type ( EntityEventAdapterMouseComponentType ) type >
        NoDiscard constexpr auto cast () const noexcept -> typename Properties < type > :: AdapterType const * {
            if ( this->type() != type ) {
                return nullptr;
            }

            return reinterpret_cast < typename Properties < type > :: AdapterType const * > ( this );
        }

        template < Type ( EntityEventAdapterMouseComponentType ) type >
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

#endif // __C_ENG_ENTITY_EVENT_ADAPTER_MOUSE_COMPONENT_HPP__
