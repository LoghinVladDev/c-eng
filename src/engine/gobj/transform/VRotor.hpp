//
// Created by vladl on 10/2/2020.
//

#ifndef ENG1_VROTOR_H
#define ENG1_VROTOR_H

#include <engineVulkanPreproc.hpp>
#include <vkDefs/types/vulkanExplicitTypes.h>
#include <CDS/Object>

#if !defined(VROTOR_NO_ADJUST)
#define ADJUST_YAW()                                            \
{                                                               \
    while ( this->_yaw   <  0.0f )      this->_yaw   += 360.0f; \
    while ( this->_yaw   >= 360.0f )    this->_yaw   -= 360.0f; \
}

#define ADJUST_PITCH()                                          \
{                                                               \
    while ( this->_pitch <  0.0f )      this->_pitch += 360.0f; \
    while ( this->_pitch >= 360.0f )    this->_pitch -= 360.0f; \
}

#define ADJUST_ROLL()                                           \
{                                                               \
    while ( this->_roll  <  0.0f )      this->_roll  += 360.0f; \
    while ( this->_roll  >= 360.0f )    this->_roll  -= 360.0f; \
}
#define ADJUST_ROTOR()                                          \
{                                                               \
    ADJUST_YAW()                                                \
    ADJUST_PITCH()                                              \
    ADJUST_ROLL()                                               \
}
#else
#define ADJUST_YAW()
#define ADJUST_PITCH()
#define ADJUST_ROLL()
#define ADJUST_ROTOR()
#endif

namespace engine {

    class VRotor : public Object {
    private:
        //// private variables
        float _yaw      {0.0f};
        float _pitch    {0.0f};
        float _roll     {0.0f};

        //// private functions

    public:
        //// public variables
        typedef enum {
            YAW,
            PITCH,
            ROLL
        } RotationType;

        //// public functions
        constexpr VRotor() noexcept = default;
        constexpr explicit VRotor ( float yaw, float pitch, float roll ) noexcept :
            _yaw(yaw),
            _pitch(pitch),
            _roll(roll) {
            ADJUST_ROTOR()
        }

        constexpr explicit VRotor ( const glm::vec3 & rotation ) noexcept :
            _yaw ( rotation.x ),
            _pitch ( rotation.y ),
            _roll ( rotation.z ){
            ADJUST_ROTOR()
        }

        constexpr VRotor (VRotor const &) noexcept = default;

#if !defined(_MSC_VER)
#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
#endif
        [[nodiscard]] constexpr auto yaw() const noexcept -> float { return this->_yaw; }
        [[nodiscard]] constexpr auto pitch() const noexcept -> float { return this->_pitch; }
        [[nodiscard]] constexpr auto roll() const noexcept -> float { return this->_roll; }
#if !defined(_MSC_VER)
#pragma clang diagnostic pop
#endif

        constexpr auto yaw () noexcept -> float & { return this->_yaw; }
        constexpr auto pitch () noexcept -> float & { return this->_pitch; }
        constexpr auto roll () noexcept -> float & { return this->_roll; }

        constexpr auto rotate ( RotationType type, float angle ) noexcept -> void {
            switch ( type ) {
                case YAW:
                    this->_yaw += angle;
                    ADJUST_YAW()
                    break;
                case PITCH:
                    this->_pitch += angle;
                    ADJUST_PITCH()
                    break;
                case ROLL:
                    this->_roll += angle;
                    ADJUST_ROLL()
                    break;
            }
        }

        constexpr auto rotateYaw ( float angle ) noexcept -> void {
            this->_yaw += angle;
            ADJUST_YAW()
        }

        constexpr auto rotatePitch ( float angle ) noexcept -> void {
            this->_pitch += angle;
            ADJUST_PITCH()
        }

        constexpr auto rotateRoll ( float angle ) noexcept -> void {
            this->_roll += angle;
            ADJUST_ROLL()
        }

        constexpr auto rotate3D ( float yaw, float pitch, float roll ) noexcept -> void {
            this->_yaw += yaw;
            this->_pitch += pitch;
            this->_roll += roll;
            ADJUST_ROTOR()
        }

        constexpr auto setYaw ( float yaw ) noexcept -> void {
            this->_yaw = yaw;
            while ( this->_yaw   <  0.0f )      this->_yaw   += 360.0f;
            while ( this->_yaw   <= 360.0f )    this->_yaw   -= 360.0f;
            ADJUST_YAW()
        }

        constexpr auto setPitch ( float pitch ) noexcept -> void {
            this->_pitch = pitch;
            ADJUST_PITCH()
        }

        constexpr auto setRoll ( float roll ) noexcept -> void {
            this->_roll = roll;
            ADJUST_ROLL()
        }

        constexpr auto setRotor ( float yaw, float pitch, float roll ) noexcept -> void {
            this->_yaw      = yaw;
            this->_pitch    = pitch;
            this->_roll     = roll;
            ADJUST_ROTOR()
        }

        constexpr auto setRotor ( const glm::vec3 & rotation ) noexcept -> void {
            this->_yaw      = rotation.x;
            this->_pitch    = rotation.y;
            this->_roll     = rotation.z;
            ADJUST_ROTOR()
        }

        constexpr VRotor & operator = ( const glm::vec3 & vector ) noexcept {
            this->_yaw      = vector.x;
            this->_pitch    = vector.y;
            this->_roll     = vector.z;
            ADJUST_ROTOR()

            return *this;
        }

        constexpr auto operator + (VRotor const & o) const noexcept -> VRotor {
            return VRotor(this->_yaw + o._yaw, this->_pitch + o._pitch, this->_roll + o._roll);
        }

        constexpr auto operator - (VRotor const & o) const noexcept -> VRotor {
            return VRotor(this->_yaw - o._yaw, this->_pitch - o._pitch, this->_roll - o._roll);
        }

        constexpr auto operator += (VRotor const & o) noexcept -> VRotor & {
            this->_yaw += o._yaw;
            this->_pitch += o._pitch;
            this->_roll += o._roll;
            return * this;
        }

        constexpr auto operator -= (VRotor const & o) noexcept -> VRotor & {
            this->_yaw -= o._yaw;
            this->_pitch -= o._pitch;
            this->_roll -= o._roll;
            return * this ;
        }

        [[nodiscard]] auto toString () const noexcept -> String override {
            return String("VRotor { ") +
                "roll = " + this->_roll +
                ", yaw = " + this->_yaw +
                ", pitch = " + this->_pitch + " }";
        }

        [[nodiscard]] auto hash () const noexcept -> Index override { return
            static_cast < int > (this->_yaw) % 360 * 360 * 360 +
            static_cast < int > (this->_roll) % 360 * 360 +
            static_cast < int > (this->_pitch) % 360;
        }

        [[nodiscard]] auto copy () const noexcept -> VRotor * override { return new VRotor(* this); }

        template < typename Mapper >
        auto apply ( Mapper const & m ) const noexcept -> glm::vec3 {
            return glm::vec3 ( m(this->_roll), m(this->_yaw), m(this->_pitch) );
        }
    };

}

#undef ADJUST_ROTORS

#endif //ENG1_VROTOR_H
