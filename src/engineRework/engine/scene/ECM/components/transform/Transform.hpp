//
// Created by loghin on 4/30/22.
//

#ifndef __C_ENG_TRANSFORM_HPP__
#define __C_ENG_TRANSFORM_HPP__

#include <Preprocess.hpp>
#include <scene/ECM/Component.hpp>
#include <scene/ECM/components/transform/Rotor.hpp>

#define C_ENG_MAP_START CLASS ( Transform, ENGINE_PARENT ( Component ) )
#include <ObjectMapping.hpp>

namespace engine {

    Class {
        ClassDefs

        Const ( TYPE ( cds :: String ), locationKey,        VALUE ( "location" ) )
        Const ( TYPE ( cds :: String ), rotationKey,        VALUE ( "rotation" ) )
        Const ( TYPE ( cds :: String ), scaleKey,           VALUE ( "scale" ) )

        Const ( TYPE ( cds :: String ), locationXKey,       VALUE ( "x" ) )
        Const ( TYPE ( cds :: String ), locationYKey,       VALUE ( "y" ) )
        Const ( TYPE ( cds :: String ), locationZKey,       VALUE ( "z" ) )

        Const ( TYPE ( cds :: String ), rotationYawKey,     VALUE ( "x" ) )
        Const ( TYPE ( cds :: String ), rotationPitchKey,   VALUE ( "y" ) )
        Const ( TYPE ( cds :: String ), rotationRollKey,    VALUE ( "z" ) )

        Const ( TYPE ( cds :: String ), scaleXKey,          VALUE ( "x" ) )
        Const ( TYPE ( cds :: String ), scaleYKey,          VALUE ( "y" ) )
        Const ( TYPE ( cds :: String ), scaleZKey,          VALUE ( "z" ) )

        Field ( TYPE ( glm :: vec3 ),   location,   DEFAULT_VALUE ( 0.0F, 0.0F, 0.0F ), GET_DEFAULT, SET_DEFAULT )
        Field ( TYPE ( glm :: vec3 ),   scale,      DEFAULT_VALUE ( 0.0F, 0.0F, 0.0F ), GET_DEFAULT, SET_DEFAULT )
        Field ( ENGINE_TYPE ( Rotor ),  rotation,   NO_INIT,                            GET_DEFAULT, SET_DEFAULT )

    public:
        NoDiscard constexpr auto type () const noexcept -> Type ( ComponentTypeFlag ) override {
            return ComponentTypeFlagTransform;
        }

        constexpr Constructor () noexcept = default;
        constexpr Constructor ( Self const & ) noexcept = default;
        constexpr Constructor ( Self && ) noexcept = default;

        constexpr auto operator = ( Self const & transform ) noexcept -> Self & {
            if ( this == & transform ) {
                return * this;
            }

            this->_location = transform.location();
            this->_rotation = transform.rotation();
            this->_scale    = transform.scale();

            return * this;
        }

        constexpr auto operator = ( Self && transform ) noexcept -> Self & {
            if ( this == & transform ) {
                return * this;
            }

            this->_location = transform._location;
            this->_rotation = transform._rotation;
            this->_scale    = transform._scale;

            return * this;
        }

        constexpr Constructor (
                glm :: vec3 const & location,
                glm :: vec3 const & rotation,
                glm :: vec3 const & scale
        ) noexcept :
                _location ( location ),
                _rotation ( rotation ),
                _scale ( scale ) {

        }

        constexpr Constructor (
                glm :: vec3     const & location,
                Type ( Rotor )  const & rotation,
                glm :: vec3     const & scale
        ) noexcept :
                _location ( location ),
                _rotation ( rotation ),
                _scale ( scale ) {

        }

        constexpr auto setLocation ( glm :: vec3 const & location ) noexcept -> Self & {
            this->_location = location;
            return * this;
        }

        constexpr auto setRotation ( glm :: vec3 const & rotation ) noexcept -> Self & {
            this->_rotation = rotation;
            return * this;
        }

        constexpr auto setRotation ( Type ( Rotor ) const & rotation ) noexcept -> Self & {
            this->_rotation = rotation;
            return * this;
        }

        constexpr auto setScale ( glm :: vec3 const & scale ) noexcept -> Self & {
            this->_scale = scale;
            return * this;
        }

        auto loadFrom ( cds :: json :: standard :: JsonObject const & ) noexcept -> Self & override;
        auto dumpTo ( cds :: json :: standard :: JsonObject & ) noexcept -> Self & override;
        auto clear () noexcept -> Self & override;

        NoDiscard auto copy () const noexcept -> Self * override;
        NoDiscard auto toString () const noexcept -> cds :: String override;

        Destructor () noexcept override = default;
    };

}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif // __C_ENG_TRANSFORM_HPP__
