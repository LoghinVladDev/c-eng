//
// Created by vladl on 06/07/2020.
//

#include "Camera.h"

Camera::Camera() {
    this->_transform.getLocation().setY(1.0f);
    this->_transform.getRotation().setZ(-1.0f);
    this->_drawPriority = UINT8_MIN;
}

[[maybe_unused]] Camera::Camera(const Transform& vector) {
    this->_transform = vector;
    this->_tagsArray = EngineUtility::Array <std::string> ();
}

void Camera::update() noexcept {
    if( this->deltaMove != 0.0f ){
        this->_transform.getLocation()
            .setX( this->_transform.getLocation().getX() + this->deltaMove * this->_transform.getRotation().getX() * 0.1f )
            .setZ( this->_transform.getLocation().getZ() + this->deltaMove * this->_transform.getRotation().getZ() * 0.1f );
    }

    if( Engine::getInstance()->getMainWindow().isMouseMoving()){
        this->angle += this->deltaAngle;
        this->_transform.getRotation()
            .setX(std::sin(this->angle))
            .setZ( - std::cos(this->angle));
    }
}

void Camera::draw() noexcept {
    gluLookAt(
        this->_transform.getLocation().getX(), this->_transform.getLocation().getY(), this->_transform.getLocation().getZ(),
        this->_transform.getLocation().getX() + this->_transform.getRotation().getX(), this->_transform.getLocation().getY() + this->_transform.getRotation().getY(), this->_transform.getLocation().getZ() + this->_transform.getRotation().getZ(),
        0.0f, 1.0f, 0.0f
    );
}
