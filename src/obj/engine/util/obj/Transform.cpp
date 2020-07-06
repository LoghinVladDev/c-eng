//
// Created by vladl on 05/07/2020.
//

#include "Transform.h"

[[maybe_unused]] Transform::Transform() noexcept = default;

[[maybe_unused]] inline Transform::Transform(const Transform &other) noexcept = default;

[[maybe_unused]] inline void Transform::setApplyFriction(bool toggle) noexcept {
    this->_applyFriction = toggle;
}

[[maybe_unused]] [[nodiscard]] inline bool Transform::isFrictionActive() const noexcept {
    return this->_applyFriction;
}

[[maybe_unused]] [[nodiscard]] inline std::string Transform::toString() const noexcept {
    return "Transform { location = " +
        this->_location.toString() +
        ", rotation = " +
        this->_rotation.toString() +
        ", velocity = " +
        this->_velocity.toString() +
        ", scale = " +
        this->_scale.toString() +
        " }";
}

[[maybe_unused]] [[nodiscard]] inline Vector& Transform::getVelocity() noexcept {
    return this->_velocity;
}

[[maybe_unused]] [[nodiscard]] inline Vector& Transform::getScale() noexcept {
    return this->_scale;
}

[[maybe_unused]] [[nodiscard]] inline Vector& Transform::getVelocityTarget() noexcept {
    return this->_velocityTarget;
}

[[maybe_unused]] [[nodiscard]] inline Vector& Transform::getVelocityIncrease() noexcept {
    return this->_velocityIncrease;
}

[[maybe_unused]] [[nodiscard]] inline Vector& Transform::getVelocityDecrease() noexcept {
    return this->_velocityDecrease;
}

[[maybe_unused]] [[nodiscard]] inline Vector& Transform::getVelocityCapacity() noexcept {
    return this->_velocityCapacity;
}

[[maybe_unused]] inline Transform &Transform::setLocation(const Vector & location) noexcept {
    this->_location = location;
    return *this;
}

[[maybe_unused]] inline Transform &Transform::setRotation(const Vector & rotation) noexcept {
    this->_rotation = rotation;
    return *this;
}

[[maybe_unused]] inline Transform &Transform::setVelocity(const Vector & velocity) noexcept {
    this->_velocity = velocity;
    return *this;
}

[[maybe_unused]] inline Transform &Transform::setScale(const Vector & scale) noexcept {
    this->_scale = scale;
    return *this;
}

[[maybe_unused]] inline Transform &Transform::setVelocityTarget(const Vector & target) noexcept {
    this->_velocityTarget = target;
    return *this;
}

[[maybe_unused]] inline Transform &Transform::setVelocityIncrease(const Vector & increase) noexcept {
    this->_velocityIncrease = increase;
    return *this;
}

[[maybe_unused]] inline Transform &Transform::setVelocityDecrease(const Vector & decrease) noexcept {
    this->_velocityDecrease = decrease;
    return *this;
}

[[maybe_unused]] inline Transform &Transform::setVelocityCapacity(const Vector & capacity) noexcept {
    this->_velocityCapacity = capacity;
    return *this;
}
