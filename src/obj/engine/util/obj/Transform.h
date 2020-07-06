//
// Created by vladl on 05/07/2020.
//

#ifndef ENG1_TRANSFORM_H
#define ENG1_TRANSFORM_H

#include "../geom/Vector.h"

class Transform {
private:
    constexpr static const float DEFAULT_X_AXIS_SPEED_CAPACITY  = 12.0f;
    constexpr static const float DEFAULT_X_AXIS_SPEED_INCREASE  = 0.25f;
    constexpr static const float DEFAULT_X_AXIS_SPEED_DECREASE  = 0.15f;

    constexpr static const float DEFAULT_Y_AXIS_SPEED_CAPACITY  = 12.0f;
    constexpr static const float DEFAULT_Y_AXIS_SPEED_INCREASE  = 0.25f;
    constexpr static const float DEFAULT_Y_AXIS_SPEED_DECREASE  = 0.15f;

    constexpr static const float DEFAULT_Z_AXIS_SPEED_CAPACITY  = 12.0f;
    constexpr static const float DEFAULT_Z_AXIS_SPEED_INCREASE  = 0.25f;
    constexpr static const float DEFAULT_Z_AXIS_SPEED_DECREASE  = 0.15f;

    Vector _location {0.0f, 0.0f, 0.0f};
    Vector _rotation {0.0f, 0.0f, 0.0f}; // Maybe rotor not vector?
    Vector _scale {0.0f, 0.0f, 0.0f};

    Vector _velocity {0.0f, 0.0f, 0.0f};
    Vector _velocityTarget {0.0f, 0.0f, 0.0f};
    Vector _velocityIncrease {DEFAULT_X_AXIS_SPEED_INCREASE, DEFAULT_Y_AXIS_SPEED_INCREASE, DEFAULT_Z_AXIS_SPEED_INCREASE};
    Vector _velocityDecrease {DEFAULT_X_AXIS_SPEED_DECREASE, DEFAULT_Y_AXIS_SPEED_DECREASE, DEFAULT_Z_AXIS_SPEED_DECREASE};
    Vector _velocityCapacity {DEFAULT_X_AXIS_SPEED_CAPACITY, DEFAULT_Y_AXIS_SPEED_CAPACITY, DEFAULT_Z_AXIS_SPEED_CAPACITY};

    bool _applyFriction { true };

public:
    [[maybe_unused]] Transform() noexcept;
    [[maybe_unused]] Transform(const Transform&) noexcept;

    [[maybe_unused]] void setApplyFriction(bool) noexcept;
    [[maybe_unused]] [[nodiscard]] bool isFrictionActive() const noexcept;

    [[maybe_unused]] [[nodiscard]] std::string toString() const noexcept;

    [[maybe_unused]] [[nodiscard]] Vector& getLocation() noexcept  {
        return this->_location;
    }

    [[maybe_unused]] [[nodiscard]] Vector& getRotation() noexcept {
        return this->_rotation;
    }

    [[maybe_unused]] [[nodiscard]] Vector& getVelocity() noexcept;
    [[maybe_unused]] [[nodiscard]] Vector& getScale() noexcept;

    [[maybe_unused]] [[nodiscard]] Vector& getVelocityTarget() noexcept;
    [[maybe_unused]] [[nodiscard]] Vector& getVelocityIncrease() noexcept;
    [[maybe_unused]] [[nodiscard]] Vector& getVelocityDecrease() noexcept;
    [[maybe_unused]] [[nodiscard]] Vector& getVelocityCapacity() noexcept;

    [[maybe_unused]] Transform& setLocation(const Vector&) noexcept;
    [[maybe_unused]] Transform& setRotation(const Vector&) noexcept;
    [[maybe_unused]] Transform& setVelocity(const Vector&) noexcept;
    [[maybe_unused]] Transform& setScale(const Vector&) noexcept;

    [[maybe_unused]] Transform& setVelocityTarget(const Vector&) noexcept;
    [[maybe_unused]] Transform& setVelocityIncrease(const Vector&) noexcept;
    [[maybe_unused]] Transform& setVelocityDecrease(const Vector&) noexcept;
    [[maybe_unused]] Transform& setVelocityCapacity(const Vector&) noexcept;
};


#endif //ENG1_TRANSFORM_H
