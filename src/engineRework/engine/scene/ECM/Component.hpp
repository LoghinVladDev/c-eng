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

    public:
        Const ( TYPE ( cds :: String ), typeKey,    VALUE ( "type" ) )

        NoDiscard __CDS_cpplang_VirtualConstexpr virtual auto type () const noexcept -> Type ( ComponentTypeFlag ) = 0;
        virtual auto loadFrom ( cds :: json :: standard :: JsonObject const & ) noexcept -> Self & = 0;
        virtual auto dumpTo ( cds :: json :: standard :: JsonObject & ) noexcept -> Self & = 0;
        NoDiscard auto copy () const noexcept -> Self * override = 0;
        auto static instantiate ( cds :: json :: standard :: JsonObject const & ) noexcept (false) -> cds :: UniquePointer < Type ( Component ) >;
        auto static instantiate ( Type ( ComponentTypeFlag ) ) noexcept (false) -> cds :: UniquePointer < Type ( Component ) >;
        auto clear () noexcept -> Self & override = 0;
    };

}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#endif //C_ENG_COMPONENT_HPP
