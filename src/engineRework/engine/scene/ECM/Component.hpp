//
// Created by loghin on 4/6/22.
//

#ifndef C_ENG_COMPONENT_HPP
#define C_ENG_COMPONENT_HPP

#include <Preprocess.hpp>
#include <CDS/Object>
#include <Core.hpp>
#include <CDS/experimental/JSON>


#define C_ENG_MAP_START CLASS ( Component, ENGINE_PARENT ( EngineObject ) )
#include <ObjectMapping.hpp>

namespace engine {
    Class {
        ClassDefs

        Const ( TYPE ( cds :: String ), typeKey,    VALUE ( "type" ) )

    public:
        NoDiscard __CDS_cpplang_VirtualConstexpr virtual auto type () const noexcept -> Type ( ComponentTypeFlag ) = 0;
        virtual auto loadFrom ( cds :: json :: standard :: JsonObject const & ) noexcept -> Self & = 0;
        virtual auto dumpTo ( cds :: json :: standard :: JsonObject & ) noexcept -> Self & = 0;
        NoDiscard auto copy () const noexcept -> Self * override = 0;
        auto static instantiate ( cds :: json :: standard :: JsonObject const & ) noexcept (false) -> cds :: UniquePointer < Type ( Component ) >;
        auto static instantiate ( Type ( ComponentTypeFlag ) ) noexcept (false) -> cds :: UniquePointer < Type ( Component ) >;
        auto clear () noexcept -> Self & override = 0;

        template < Type ( ComponentTypeFlag ) flag >
        NoDiscard constexpr auto cast () noexcept -> Self * {
            if ( this->type() == flag ) {
                return this;
            }

            return nullptr;
        }

        template < Type ( ComponentTypeFlag ) flag >
        NoDiscard constexpr auto cast () const noexcept -> Self const * {
            if ( this->type() == flag ) {
                return this;
            }

            return nullptr;
        }
    };

}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#endif //C_ENG_COMPONENT_HPP
