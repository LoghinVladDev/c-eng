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
            this->transform()->rotation().yaw()      = DEFAULT_YAW;
            this->transform()->rotation().pitch()    = DEFAULT_PITCH;
        }

        explicit VCamera(
            glm::vec3 const & location,
            glm::vec3 const & up = glm::vec3 (0.0f, 1.0f, 0.0f),
            float startingYaw = DEFAULT_YAW,
            float startingPitch = DEFAULT_PITCH
        ) noexcept : VCamera(){
            this->_worldUp = up;
            this->transform()->setLocation( location );
            this->transform()->rotation().yaw() = startingYaw;
            this->transform()->rotation().pitch() = startingPitch;
        }

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

        [[nodiscard]] auto toString () const noexcept -> String override {
             return String("VCamera {")
                .append("transform=").append(this->transform()->toString())
                .append("}");
        }

        [[nodiscard]] auto copy () const noexcept -> VCamera * override {
            return new VCamera (*this);
        }

        inline auto viewMatrix () const noexcept -> glm::mat4 {
            return glm::lookAt (
                    this->transform()->location(),
                this->transform()->location() + this->front(),
                this->up()
            );
        }

        inline auto collectRawInput ( float xOffset, float yOffset, bool constraintPitch = true ) noexcept -> void {
            this->transform()->rotation().yaw() += xOffset;
            this->transform()->rotation().pitch() += yOffset;

            if ( constraintPitch ) {
                if (this->transform()->rotation().pitch() > VCamera::DEFAULT_PITCH_CONSTRAINT_MAX )
                    this->transform()->rotation().pitch() = VCamera::DEFAULT_PITCH_CONSTRAINT_MAX;
                if (this->transform()->rotation().pitch() < VCamera::DEFAULT_PITCH_CONSTRAINT_MIN )
                    this->transform()->rotation().pitch() = VCamera::DEFAULT_PITCH_CONSTRAINT_MIN;
            }

            this->processVectors();
        }

    private:
        auto processVectors() noexcept -> void {
            auto cosYaw = std::cos(glm::radians(this->transform()->rotation().yaw()));
            auto cosPitch = std::cos(glm::radians(this->transform()->rotation().pitch()));

            auto sinYaw = std::sin(glm::radians(this->transform()->rotation().yaw()));
            auto sinPitch = std::sin(glm::radians(this->transform()->rotation().pitch()));

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
