//
// Created by loghin on 4/30/22.
//

#ifndef __C_ENG_ROTOR_HPP__
#define __C_ENG_ROTOR_HPP__

#include <Preprocess.hpp>
#include <Core.hpp>
#include <glm/trigonometric.hpp>

#define C_ENG_MAP_START CLASS ( Rotor, NO_PARENT )
#include <ObjectMapping.hpp>

namespace engine {

    Class {
        Field ( PRIMITIVE_TYPE ( float ),   yaw,    DEFAULT_VALUE ( 0.0f ), GET_DEFAULT,    SET_NONE )
        Field ( PRIMITIVE_TYPE ( float ),   pitch,  DEFAULT_VALUE ( 0.0f ), GET_DEFAULT,    SET_NONE )
        Field ( PRIMITIVE_TYPE ( float ),   roll,   DEFAULT_VALUE ( 0.0f ), GET_DEFAULT,    SET_NONE )

        constexpr static auto normalize ( float value ) noexcept -> float {
            constexpr float min = 0.0f;
            constexpr float max = glm :: radians ( 360.0f );

            while ( value < min ) { value += max; }
            while ( value >= max ) { value -= max; }

            return value;
        }

    public:
        enum class RotationType {
            Yaw,
            Pitch,
            Roll
        };

        constexpr Constructor () noexcept = default;
        constexpr Constructor ( float yaw, float pitch, float roll ) noexcept :
                _yaw ( normalize ( glm :: radians ( yaw ) ) ),
                _pitch ( normalize ( glm :: radians ( pitch ) ) ),
                _roll ( normalize ( glm :: radians ( roll ) ) ) {

        }

        constexpr Constructor ( glm :: vec3 const & rotation ) noexcept :
                _yaw ( normalize ( glm :: radians ( rotation.x ) ) ),
                _pitch ( normalize ( glm :: radians ( rotation.y ) ) ),
                _roll ( normalize ( glm :: radians ( rotation.z ) ) ) {

        }

        constexpr Constructor ( Self const & ) noexcept = default;
        constexpr Constructor ( Self && ) noexcept = default;

        constexpr auto rotate ( RotationType type, float angle ) noexcept -> Self & {
            switch ( type ) {
                case RotationType :: Yaw:   return this->rotateYaw ( angle );
                case RotationType :: Pitch: return this->rotatePitch ( angle );
                case RotationType :: Roll:  return this->rotateRoll ( angle );
            }
        }

    private:
        constexpr auto rotateAngle ( float & angle, float offset ) noexcept -> Self & {
            angle = normalize ( angle + glm :: radians ( offset ) );
            return * this;
        }

    public:
        constexpr auto rotateYaw ( float angle ) noexcept -> Self & {
            return this->rotateAngle ( this->_yaw, angle );
        }

        constexpr auto rotatePitch ( float angle ) noexcept -> Self & {
            return this->rotateAngle ( this->_pitch, angle );
        }

        constexpr auto rotateRoll ( float angle ) noexcept -> Self & {
            return this->rotateAngle ( this->_roll, angle );
        }

        constexpr auto rotate ( float yaw, float pitch, float roll ) noexcept -> Self & {
            return this->rotateYaw ( yaw ).rotatePitch ( pitch ).rotateRoll ( roll );
        }

        constexpr auto rotate ( glm :: vec3 const & rotor ) noexcept -> Self & {
            return this->rotate ( rotor.x, rotor.y, rotor.z );
        }

        constexpr auto rotate ( Type ( Rotor ) const & rotor ) noexcept -> Self & {
            this->_yaw      = normalize ( this->yaw() + rotor.yaw() );
            this->_pitch    = normalize ( this->pitch() + rotor.pitch() );
            this->_roll     = normalize ( this->roll() + rotor.roll() );

            return * this;
        }

    private:
        constexpr auto setAngle ( float & angle, float offset ) noexcept -> Self & {
            angle = normalize ( glm :: radians ( offset ) );
            return * this;
        }

    public:
        constexpr auto setYaw ( float angle ) noexcept -> Self & {
            return this->setAngle ( this->_yaw, angle );
        }

        constexpr auto setPitch ( float angle ) noexcept -> Self & {
            return this->setAngle ( this->_pitch, angle );
        }

        constexpr auto setRoll ( float angle ) noexcept -> Self & {
            return this->setAngle ( this->_roll, angle );
        }

        constexpr auto set ( float yaw, float pitch, float roll ) noexcept -> Self & {
            return this->setYaw ( yaw ).setPitch ( pitch ).setRoll ( roll );
        }

        constexpr auto set ( glm :: vec3 const & rotor ) noexcept -> Self & {
            return this->setYaw ( rotor.x ).setPitch ( rotor.y ).setRoll ( rotor.z );
        }

        constexpr auto set ( Type ( Rotor ) const & rotor ) noexcept -> Self & {
            if ( this == & rotor ) {
                return * this;
            }

            this->_yaw      = rotor.yaw();
            this->_pitch    = rotor.pitch();
            this->_roll     = rotor.roll();

            return * this;
        }

        constexpr auto operator = ( glm :: vec3 const & rotor ) noexcept -> Self & {
            return this->set ( rotor );
        }

        constexpr auto operator = ( Type ( Rotor ) const & rotor ) noexcept -> Self & {
            return this->set ( rotor );
        }

        constexpr auto operator + ( Type ( Rotor ) const & rotor ) const noexcept -> Type ( Rotor ) {
            return Type ( Rotor ) ( * this ).rotate ( rotor );
        }

        constexpr auto operator + ( glm :: vec3 const & rotor ) const noexcept -> Type ( Rotor ) {
            return Type ( Rotor ) ( * this ).rotate ( rotor );
        }

        constexpr auto operator += ( Type ( Rotor ) const & rotor ) noexcept -> Self & {
            return this->rotate ( rotor );
        }

        constexpr auto operator += ( glm :: vec3 const & rotor ) noexcept -> Self & {
            return this->rotate ( rotor );
        }

        constexpr auto operator == ( Type ( Rotor ) const & rotor ) const noexcept -> bool {
            return
                    this            == & rotor      ||
                    this->_yaw      == rotor._yaw   &&
                    this->_pitch    == rotor._pitch &&
                    this->_roll     == rotor._roll;
        }
    };

}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif // __C_ENG_ROTOR_HPP__
