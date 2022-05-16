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

    __C_ENG_PRE_DECLARE_CLASS ( Transform );
    __C_ENG_PRE_DECLARE_CLASS ( Mesh );
    __C_ENG_PRE_DECLARE_CLASS ( MeshRenderer );
    __C_ENG_PRE_DECLARE_CLASS ( EntityEventAdapter );

    __C_ENG_PRE_DECLARE_CLASS ( Entity );

    Class {
        friend class Type ( Entity );

        ClassDefs

        Const ( TYPE ( cds :: String ), typeKey,    VALUE ( "type" ) )

        Field ( ENGINE_PRIMITIVE_TYPE ( Entity * ), entity, DEFAULT_VALUE ( nullptr ),  GET_DEFAULT, SET_NONE )

        template < Type ( ComponentTypeFlag ) flag, typename = void >
        struct ComponentTypeProperties {
            using ComponentType = void;
        };

        template < >
        struct ComponentTypeProperties < ComponentTypeFlagTransform > {
            using ComponentType = Type ( Transform );
        };

        template < >
        struct ComponentTypeProperties < ComponentTypeFlagMesh > {
            using ComponentType = Type ( Mesh );
        };

        template < >
        struct ComponentTypeProperties < ComponentTypeFlagMeshRenderer > {
            using ComponentType = Type ( MeshRenderer );
        };

        template < >
        struct ComponentTypeProperties < ComponentTypeFlagEntityEventAdapter > {
            using ComponentType = Type ( EntityEventAdapter );
        };

    public:
        NoDiscard __CDS_cpplang_VirtualConstexpr virtual auto type () const noexcept -> Type ( ComponentTypeFlag ) = 0;
        virtual auto loadFrom ( cds :: json :: standard :: JsonObject const & ) noexcept (false) -> Self & = 0;
        virtual auto dumpTo ( cds :: json :: standard :: JsonObject & ) noexcept -> Self & = 0;
        NoDiscard auto copy () const noexcept -> Self * override = 0;
        auto static instantiate ( cds :: json :: standard :: JsonObject const & ) noexcept (false) -> cds :: UniquePointer < Type ( Component ) >;
        auto static instantiate ( Type ( ComponentTypeFlag ) ) noexcept (false) -> cds :: UniquePointer < Type ( Component ) >;
        auto clear () noexcept -> Self & override = 0;

        template < Type ( ComponentTypeFlag ) flag >
        NoDiscard constexpr auto cast () noexcept -> typename ComponentTypeProperties < flag > :: ComponentType * {
            if ( this->type() != flag ) {
                return nullptr;
            }

            return reinterpret_cast < typename ComponentTypeProperties < flag > :: ComponentType * > ( this );
        }

        template < Type ( ComponentTypeFlag ) flag >
        NoDiscard constexpr auto cast () const noexcept -> typename ComponentTypeProperties < flag > :: ComponentType const * {
            if ( this->type() != flag ) {
                return nullptr;
            }

            return reinterpret_cast < typename ComponentTypeProperties < flag > :: ComponentType const * > ( this );
        }
    };

}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#endif //C_ENG_COMPONENT_HPP
