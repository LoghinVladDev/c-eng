//
// Created by vladl on 06/07/2020.
//

#pragma once

#ifndef ENG1_CAMERA_H
#define ENG1_CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../GameObject.h"

//constexpr float _replace_sensitivity = 0.1f;

namespace engine {

    class [[maybe_unused]] Camera : public GameObject {
    public:
        constexpr static float DEFAULT_YAW = -90.0f;
        constexpr static float DEFAULT_PITCH = 0.0f;
        constexpr static float DEFAULT_PITCH_CONSTRAINT_MIN = -89.0f;
        constexpr static float DEFAULT_PITCH_CONSTRAINT_MAX =  89.0f;
    protected:

        float _yaw = DEFAULT_YAW;
        float _pitch = DEFAULT_PITCH;

        glm::vec3 _front;
        glm::vec3 _up;
        glm::vec3 _right;
        glm::vec3 _worldUp;

//        float angle{0.0f};
//        float deltaMove{0.0f};
//        float deltaAngle{0.0f};
    public:
//        Camera() = delete;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-pro-type-member-init"
        [[maybe_unused]] explicit Camera(
                glm::vec3 location = glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
                float yaw = DEFAULT_YAW,
                float pitch = DEFAULT_PITCH
        ) :
            _front(glm::vec3(0.0f, 0.0f, -1.0f)),
            _yaw (yaw),
            _pitch(pitch),
            _worldUp(up) {

            this->_transform.setLocation(location);
            this->updateCameraVectors();
        }
#pragma clang diagnostic pop

        [[maybe_unused]] explicit Camera(const Transform &);

        void update() noexcept override {

        }

        void draw() noexcept override {

        }

        glm::mat4 getViewMatrix() {
            return glm::lookAt(
                this->_transform.getLocation(),
                this->_transform.getLocation() + this->_front,
                this->_up
            );
        }

        void processOrientation(float xOffset, float yOffset, bool constrainPitch = true) {
            this->_yaw += xOffset;
            this->_pitch += yOffset;

            if(constrainPitch) {
                if ( this->_pitch > DEFAULT_PITCH_CONSTRAINT_MAX )
                    this->_pitch = DEFAULT_PITCH_CONSTRAINT_MAX;
                if ( this->_pitch < DEFAULT_PITCH_CONSTRAINT_MIN )
                    this->_pitch = DEFAULT_PITCH_CONSTRAINT_MIN;
            }

            this->updateCameraVectors();
        }
    private:
        void updateCameraVectors() {
            this->_front = glm::normalize (
                glm::vec3 (
                    cos(glm::radians(this->_yaw)) * cos(glm::radians(this->_pitch)),
                    sin(glm::radians(this->_pitch)),
                    sin(glm::radians(this->_yaw)) * cos(glm::radians(this->_pitch))
                )
            );

            this->_right = glm::normalize(glm::cross(this->_front, this->_worldUp));
            this->_up    = glm::normalize(glm::cross(this->_right, this->_front));
        }
    };

}

#endif //ENG1_CAMERA_H
