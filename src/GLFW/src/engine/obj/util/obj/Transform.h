//
// Created by vladl on 05/07/2020.
//

#ifndef ENG1_TRANSFORM_H
#define ENG1_TRANSFORM_H

#include "../geom/Vector.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace engine {

    class Transform {
    private:
        constexpr static const float DEFAULT_X_AXIS_SPEED_CAPACITY = 12.0f;
        constexpr static const float DEFAULT_X_AXIS_SPEED_INCREASE = 0.25f;
        constexpr static const float DEFAULT_X_AXIS_SPEED_DECREASE = 0.15f;

        constexpr static const float DEFAULT_Y_AXIS_SPEED_CAPACITY = 12.0f;
        constexpr static const float DEFAULT_Y_AXIS_SPEED_INCREASE = 0.25f;
        constexpr static const float DEFAULT_Y_AXIS_SPEED_DECREASE = 0.15f;

        constexpr static const float DEFAULT_Z_AXIS_SPEED_CAPACITY = 12.0f;
        constexpr static const float DEFAULT_Z_AXIS_SPEED_INCREASE = 0.25f;
        constexpr static const float DEFAULT_Z_AXIS_SPEED_DECREASE = 0.15f;

        constexpr static const float DEFAULT_LOCATION_X = 0.0f;
        constexpr static const float DEFAULT_LOCATION_Y = 0.0f;
        constexpr static const float DEFAULT_LOCATION_Z = 0.0f;

        constexpr static const float DEFAULT_ROTATION_X = 0.0f;
        constexpr static const float DEFAULT_ROTATION_Y = 0.0f;
        constexpr static const float DEFAULT_ROTATION_Z = 0.0f;

        constexpr static const float DEFAULT_SCALE_X = 1.0f;
        constexpr static const float DEFAULT_SCALE_Y = 1.0f;
        constexpr static const float DEFAULT_SCALE_Z = 1.0f;

        constexpr static const float DEFAULT_VELOCITY_X = 0.0f;
        constexpr static const float DEFAULT_VELOCITY_Y = 0.0f;
        constexpr static const float DEFAULT_VELOCITY_Z = 0.0f;

        constexpr static const float DEFAULT_VELOCITY_TARGET_X = 0.0f;
        constexpr static const float DEFAULT_VELOCITY_TARGET_Y = 0.0f;
        constexpr static const float DEFAULT_VELOCITY_TARGET_Z = 0.0f;

        glm::vec3 _location {DEFAULT_LOCATION_X, DEFAULT_LOCATION_Y, DEFAULT_LOCATION_Z};
//        Vector _location{DEFAULT_LOCATION_X, DEFAULT_LOCATION_Y, DEFAULT_LOCATION_Z};
        Vector _rotation{DEFAULT_ROTATION_X, DEFAULT_ROTATION_Y, DEFAULT_ROTATION_Z}; // Maybe rotor not vector? TODO : definetly impelemnt rotor
//        Vector _scale{DEFAULT_SCALE_X, DEFAULT_SCALE_Y, DEFAULT_SCALE_Z};
        glm::vec3 _scale {DEFAULT_SCALE_X, DEFAULT_SCALE_Y, DEFAULT_SCALE_Z};

        Vector _velocity{DEFAULT_VELOCITY_X, DEFAULT_VELOCITY_Y, DEFAULT_VELOCITY_Z};
        Vector _velocityTarget{DEFAULT_VELOCITY_TARGET_X, DEFAULT_VELOCITY_TARGET_Y, DEFAULT_VELOCITY_TARGET_Z};
        Vector _velocityIncrease{DEFAULT_X_AXIS_SPEED_INCREASE, DEFAULT_Y_AXIS_SPEED_INCREASE,
                                 DEFAULT_Z_AXIS_SPEED_INCREASE};
        Vector _velocityDecrease{DEFAULT_X_AXIS_SPEED_DECREASE, DEFAULT_Y_AXIS_SPEED_DECREASE,
                                 DEFAULT_Z_AXIS_SPEED_DECREASE};
        Vector _velocityCapacity{DEFAULT_X_AXIS_SPEED_CAPACITY, DEFAULT_Y_AXIS_SPEED_CAPACITY,
                                 DEFAULT_Z_AXIS_SPEED_CAPACITY};

        bool _applyFriction{true};
        bool _scaleModified{false};

    public:
        [[maybe_unused]] Transform() noexcept;

        [[maybe_unused]] Transform(const Transform &) noexcept;

        [[maybe_unused]] void setApplyFriction(bool) noexcept;

        [[maybe_unused]] [[nodiscard]] bool isFrictionActive() const noexcept;

        [[maybe_unused]] [[nodiscard]] std::string toString() const noexcept {
            return "Transform { " //location = " +
//                   this->_location.toString() +
                   ", rotation = " +
                   this->_rotation.toString() +
                   ", velocity = " +
                   this->_velocity.toString() +
//                   ", scale = " +
//                   this->_scale.toString() +
                   " }";
        }

        [[maybe_unused]] [[nodiscard]] bool scaleModifiedRecently() {
            bool copy = this->_scaleModified;
            this->_scaleModified = false;
            return copy;
        }

        [[maybe_unused]] [[nodiscard]] glm::vec3 &getLocation() noexcept {
            return this->_location;
        }

        [[maybe_unused]] [[nodiscard]] Vector &getRotation() noexcept {
            return this->_rotation;
        }

        [[maybe_unused]] [[nodiscard]] Vector &getVelocity() noexcept;

        [[maybe_unused]] [[nodiscard]] glm::vec3 &getScale() noexcept {
            return this->_scale;
        }

        [[maybe_unused]] [[nodiscard]] Vector &getVelocityTarget() noexcept;
        [[maybe_unused]] [[nodiscard]] Vector &getVelocityIncrease() noexcept;
        [[maybe_unused]] [[nodiscard]] Vector &getVelocityDecrease() noexcept;
        [[maybe_unused]] [[nodiscard]] Vector &getVelocityCapacity() noexcept;

        [[maybe_unused]] Transform &setLocation(const Vector &location) noexcept {
            this->_location.x = location.getX();
            this->_location.y = location.getY();
            this->_location.z = location.getZ();
            return *this;
        }

        [[maybe_unused]] Transform &setLocation(const glm::vec3& location) noexcept {
            this->_location = location;
            return *this;
        }

        [[maybe_unused]] Transform &setRotation(const Vector &) noexcept;
        [[maybe_unused]] Transform &setVelocity(const Vector &) noexcept;
        [[maybe_unused]] Transform &setVelocityTarget(const Vector &) noexcept;
        [[maybe_unused]] Transform &setVelocityIncrease(const Vector &) noexcept;
        [[maybe_unused]] Transform &setVelocityDecrease(const Vector &) noexcept;
        [[maybe_unused]] Transform &setVelocityCapacity(const Vector &) noexcept;
        [[maybe_unused]] Transform &setScale(const Vector &) noexcept;
        [[maybe_unused]] Transform &setScale(const glm::vec3 &) noexcept;
    };

}

#endif //ENG1_TRANSFORM_H
