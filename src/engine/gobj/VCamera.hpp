//
// Created by loghin on 08.04.2021.
//

#ifndef C_ENG_VCAMERA_HPP
#define C_ENG_VCAMERA_HPP

#include <VGameObject.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#ifdef DEFAULT_PITCH
#undef DEFAULT_PITCH
#endif

namespace engine {

    class VCamera : public VGameObject {
    public:
        constexpr static float DEFAULT_YAW                  = -90.0f;
        constexpr static float DEFAULT_PITCH                = 0.0f;
        constexpr static float DEFAULT_PITCH_CONSTRAINT_MIN = -89.0f;
        constexpr static float DEFAULT_PITCH_CONSTRAINT_MAX =  89.0f;

    private:
        //// private variables
        glm::vec3       _front          {0.0f, 0.0f, -1.0f};
        glm::vec3       _up             {0.0f, 1.0f, 0.0f};
        glm::vec3       _right          {0.0f};
        glm::vec3       _worldUp        {0.0f};
        glm::vec3       _worldFront     {0.0f};

        VTransform    * _pTransform     {new VTransform()};

        //// private functions

    public:
        //// public variables

        //// public functions

        VCamera() noexcept {
            this->add(this->_pTransform);
            this->transform()->getRotation().yaw()      = DEFAULT_YAW;
            this->transform()->getRotation().pitch()    = DEFAULT_PITCH;
        }

        explicit VCamera(
            glm::vec3 const & location,
            glm::vec3 const & up = glm::vec3 (0.0f, 1.0f, 0.0f),
            float startingYaw = DEFAULT_YAW,
            float startingPitch = DEFAULT_PITCH
        ) noexcept : VCamera(){
            this->_up = up;
            this->transform()->setLocation( location );
            this->transform()->getRotation().yaw() = startingYaw;
            this->transform()->getRotation().pitch() = startingPitch;
        }

        constexpr auto transform() noexcept -> VTransform * { return this->_pTransform; }
        constexpr auto transform() const noexcept -> VTransform const * { return this->_pTransform; }

        constexpr auto front() noexcept -> glm::vec3 & { return this->_front; }
        constexpr auto worldUp () noexcept -> glm::vec3 & { return this->_worldUp; }
        constexpr auto worldFront() noexcept -> glm::vec3 & { return this->_worldFront; }
        constexpr auto right() noexcept -> glm::vec3 & { return this->_right; }
        constexpr auto up() noexcept -> glm::vec3 & { return this->_up; }

        constexpr auto front() const noexcept -> glm::vec3 const & { return this->_front; }
        constexpr auto worldUp () const noexcept -> glm::vec3 const & { return this->_worldUp; }
        constexpr auto worldFront() const noexcept -> glm::vec3 const & { return this->_worldFront; }
        constexpr auto right() const noexcept -> glm::vec3 const & { return this->_right; }
        constexpr auto up() const noexcept -> glm::vec3 const & { return this->_up; }

        inline auto viewMatrix () const noexcept -> glm::mat4 {
            return glm::lookAt (
                this->transform()->getLocation(),
                this->transform()->getLocation() * this->front(),
                this->up()
            );
        }

        inline auto collectRawInput ( float xOffset, float yOffset, bool constraintPitch = true ) noexcept -> void {
            this->transform()->getRotation().yaw() += xOffset;
            this->transform()->getRotation().pitch() += yOffset;

            if ( constraintPitch ) {
                if ( this->transform()->getRotation().pitch() > VCamera::DEFAULT_PITCH_CONSTRAINT_MAX )
                    this->transform()->getRotation().pitch() = VCamera::DEFAULT_PITCH_CONSTRAINT_MAX;
                if ( this->transform()->getRotation().pitch() < VCamera::DEFAULT_PITCH_CONSTRAINT_MIN )
                    this->transform()->getRotation().pitch() = VCamera::DEFAULT_PITCH_CONSTRAINT_MIN;
            }

            this->processVectors();
        }

    private:
        auto processVectors() noexcept -> void {
            auto cosYaw = std::cos(glm::radians(this->transform()->getRotation().yaw()));
            auto cosPitch = std::cos(glm::radians(this->transform()->getRotation().pitch()));

            auto sinYaw = std::sin(glm::radians(this->transform()->getRotation().yaw()));
            auto sinPitch = std::sin(glm::radians(this->transform()->getRotation().pitch()));

            this->front() = glm::normalize ( glm::vec3 (
                cosYaw * cosPitch,
                sinPitch,
                sinYaw * cosPitch
            ));

            this->worldFront() = glm::normalize( glm::vec3 (
                cosYaw,
                0.0f,
                sinYaw
            ));

            this->right() = glm::normalize(glm::cross(this->front(), this->worldUp()));
            this->up() = glm::normalize(glm::cross(this->right(), this->front()));
        }
    };

}

#endif //C_ENG_VCAMERA_HPP
