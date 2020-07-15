//
// Created by vladl on 05/07/2020.
//

#include "Transform.h"

[[maybe_unused]] engine::Transform::Transform() noexcept = default;

[[maybe_unused]] inline engine::Transform::Transform(const Transform &other) noexcept = default;

[[maybe_unused]] inline void engine::Transform::setApplyFriction(bool toggle) noexcept {
    this->_applyFriction = toggle;
}

[[maybe_unused]] [[nodiscard]] inline bool engine::Transform::isFrictionActive() const noexcept {
    return this->_applyFriction;
}

[[maybe_unused]] [[nodiscard]] inline engine::Vector& engine::Transform::getVelocity() noexcept {
    return this->_velocity;
}

[[maybe_unused]] [[nodiscard]] inline engine::Vector& engine::Transform::getVelocityTarget() noexcept {
    return this->_velocityTarget;
}

[[maybe_unused]] [[nodiscard]] inline engine::Vector& engine::Transform::getVelocityIncrease() noexcept {
    return this->_velocityIncrease;
}

[[maybe_unused]] [[nodiscard]] inline engine::Vector& engine::Transform::getVelocityDecrease() noexcept {
    return this->_velocityDecrease;
}

[[maybe_unused]] [[nodiscard]] inline engine::Vector& engine::Transform::getVelocityCapacity() noexcept {
    return this->_velocityCapacity;
}

[[maybe_unused]] inline engine::Transform &engine::Transform::setRotation(const Vector & rotation) noexcept {
    this->_rotation = rotation;
    return *this;
}

[[maybe_unused]] inline engine::Transform &engine::Transform::setVelocity(const Vector & velocity) noexcept {
    this->_velocity = velocity;
    return *this;
}

[[maybe_unused]] inline engine::Transform &engine::Transform::setScale(const Vector & scale) noexcept {
    this->_scale.x = scale.getX();
    this->_scale.y = scale.getY();
    this->_scale.z = scale.getZ();
    return *this;
}

[[maybe_unused]] inline engine::Transform& engine::Transform::setScale(const glm::vec3& scale) noexcept {
    this->_scale = scale;
    return *this;
}

[[maybe_unused]] inline engine::Transform &engine::Transform::setVelocityTarget(const Vector & target) noexcept {
    this->_velocityTarget = target;
    return *this;
}

[[maybe_unused]] inline engine::Transform &engine::Transform::setVelocityIncrease(const Vector & increase) noexcept {
    this->_velocityIncrease = increase;
    return *this;
}

[[maybe_unused]] inline engine::Transform &engine::Transform::setVelocityDecrease(const Vector & decrease) noexcept {
    this->_velocityDecrease = decrease;
    return *this;
}

[[maybe_unused]] inline engine::Transform &engine::Transform::setVelocityCapacity(const Vector & capacity) noexcept {
    this->_velocityCapacity = capacity;
    return *this;
}
