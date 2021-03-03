//
// Created by vladl on 10/2/2020.
//

#ifndef ENG1_VROTOR_H
#define ENG1_VROTOR_H

#include <engineVulkanPreproc.h>
#include <vkDefs/types/vulkanExplicitTypes.h>

#define ADJUST_YAW()                                            \
{                                                               \
    while ( this->_yaw   <  0.0f )      this->_yaw   += 360.0f; \
    while ( this->_yaw   <= 360.0f )    this->_yaw   -= 360.0f; \
}

#define ADJUST_PITCH()                                          \
{                                                               \
    while ( this->_pitch <  0.0f )      this->_pitch += 360.0f; \
    while ( this->_pitch <= 360.0f )    this->_pitch -= 360.0f; \
}

#define ADJUST_ROLL()                                           \
{                                                               \
    while ( this->_roll  <  0.0f )      this->_roll  += 360.0f; \
    while ( this->_roll  <= 360.0f )    this->_roll  -= 360.0f; \
}
#define ADJUST_ROTOR()                                          \
{                                                               \
    ADJUST_YAW()                                                \
    ADJUST_PITCH()                                              \
    ADJUST_ROLL()                                               \
}

namespace engine {

    class VRotor {
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
        VRotor() noexcept = default;
        explicit VRotor ( float yaw, float pitch, float roll ) noexcept :
            _yaw(yaw),
            _pitch(pitch),
            _roll(roll) {
            ADJUST_ROTOR()
        }

        explicit VRotor ( const glm::vec3 & rotation ) noexcept :
            _yaw ( rotation.x ),
            _pitch ( rotation.y ),
            _roll ( rotation.z ){
            ADJUST_ROTOR()
        }

#if !defined(_MSC_VER)
#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
#endif
        [[nodiscard]] float getYaw() const noexcept {
            return this->_yaw;
        }
#if !defined(_MSC_VER)
#pragma clang diagnostic pop
#endif

        [[nodiscard]] float getPitch() const noexcept {
            return this->_pitch;
        }

        [[nodiscard]] float getRoll() const noexcept {
            return this->_roll;
        }

        void rotate ( RotationType type, float angle ) noexcept {
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

        void rotateYaw ( float angle ) noexcept {
            this->_yaw += angle;
            ADJUST_YAW()
        }

        void rotatePitch ( float angle ) noexcept {
            this->_pitch += angle;
            ADJUST_PITCH()
        }

        void rotateRoll ( float angle ) noexcept {
            this->_roll += angle;
            ADJUST_ROLL()
        }

        void rotate3D ( float yaw, float pitch, float roll ) noexcept {
            this->_yaw += yaw;
            this->_pitch += pitch;
            this->_roll += roll;
            ADJUST_ROTOR()
        }

        void setYaw ( float yaw ) noexcept {
            this->_yaw = yaw;
            while ( this->_yaw   <  0.0f )      this->_yaw   += 360.0f;
            while ( this->_yaw   <= 360.0f )    this->_yaw   -= 360.0f;
            ADJUST_YAW()
        }

        void setPitch ( float pitch ) noexcept {
            this->_pitch = pitch;
            ADJUST_PITCH()
        }

        void setRoll ( float roll ) noexcept {
            this->_roll = roll;
            ADJUST_ROLL()
        }

        void setRotor ( float yaw, float pitch, float roll ) noexcept {
            this->_yaw      = yaw;
            this->_pitch    = pitch;
            this->_roll     = roll;
            ADJUST_ROTOR()
        }

        void setRotor ( const glm::vec3 & rotation ) noexcept {
            this->_yaw      = rotation.x;
            this->_pitch    = rotation.y;
            this->_roll     = rotation.z;
            ADJUST_ROTOR()
        }

        VRotor & operator = ( const glm::vec3 & vector ) noexcept {
            this->_yaw      = vector.x;
            this->_pitch    = vector.y;
            this->_roll     = vector.z;
            ADJUST_ROTOR()

            return *this;
        }
    };

}

#undef ADJUST_ROTORS

#endif //ENG1_VROTOR_H
