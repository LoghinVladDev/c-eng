//
// Created by vladl on 10/2/2020.
//

#ifndef ENG1_VTRANSFORM_H
#define ENG1_VTRANSFORM_H

#include <engineVulkanPreproc.h>
#include <vkDefs/types/vulkanExplicitTypes.h>
#include <transform/VRotor.h>

#include <ecm/VComponent.h>

namespace engine {

    class VTransform : public VComponent {
    private:
        //// private variables
        glm::vec3 _location { glm::vec3 (0.0f) };
        VRotor    _rotation { 0.0f, 0.0f, 0.0f };
        glm::vec3 _scale    { glm::vec3 (1.0f) };

        //// private functions

        explicit VTransform ( uint64 ignoredIncrementConstructor ) noexcept : VComponent( VComponent::DISTINCT, ignoredIncrementConstructor) { }
    public:
        //// public variables
        const static VTransform EMPTY;

        //// public functions
//        operator = not required due to Base having operator =
//        VTransform & operator = ( VTransform const & o ) noexcept {
//            if ( this == & o ) return * this;
//
//            this->_location = o._location;
//            this->_rotation = o._rotation;
//            this->_scale = o._scale;
//
//            return * this;
//        }

        [[nodiscard]] auto className() const noexcept -> ClassName override {
            return "VTransform";
        }

        explicit VTransform ( VEntity * pParent = nullptr ) noexcept : VComponent( VComponent::Tag::DISTINCT, pParent ) { }
        explicit VTransform (
                glm::vec3 const & location,
                glm::vec3 const & rotation = glm::vec3 ( 0.0f ),
                glm::vec3 const & scale = glm::vec3 ( 1.0f ),
                VEntity * pParent = nullptr
        ) noexcept :
            _location(location),
            _rotation(rotation),
            _scale(scale),
            VComponent( VComponent::Tag::DISTINCT, pParent ) {

        }

        explicit VTransform (
                glm::vec3 const & location,
                engine::VRotor const & rotor,
                glm::vec3 const & scale = glm::vec3 ( 1.0f ),
                VEntity * pParent = nullptr
        ) noexcept :
            _location(location),
            _rotation(rotor),
            _scale(scale),
            VComponent( VComponent::Tag::DISTINCT, pParent ) {

        }

        explicit VTransform (
                float locationScalar,
                float rotationScalar = 0.0f,
                float scaleScalar = 0.0f,
                VEntity * pParent = nullptr
        ) noexcept :
            _location ( glm::vec3 ( locationScalar ) ),
            _rotation ( glm::vec3 ( rotationScalar ) ),
            _scale ( glm::vec3 ( scaleScalar ) ),
            VComponent( VComponent::Tag::DISTINCT, pParent ) {

        }

        [[nodiscard]] const glm::vec3 & getLocation () const noexcept {
            return this->_location;
        }

        [[nodiscard]] glm::vec3 & getLocation () noexcept {
            return this->_location;
        }

        [[nodiscard]] const engine::VRotor & getRotation () const noexcept {
            return this->_rotation;
        }

        [[nodiscard]] engine::VRotor & getRotation () noexcept {
            return this->_rotation;
        }

        [[nodiscard]] const glm::vec3 & getScale () const noexcept {
            return this->_scale;
        }

        [[nodiscard]] glm::vec3 & getScale () noexcept {
            return this->_scale;
        }

        void setLocation ( const glm::vec3 & location ) noexcept {
            this->_location = location;
        }

        void setRotation ( const glm::vec3 & rotation ) noexcept {
            this->_rotation = rotation;
        }

        void setRotation ( const engine::VRotor & rotation ) noexcept {
            this->_rotation = rotation;
        }

        void setScale ( const glm::vec3 & scale ) noexcept {
            this->_scale = scale;
        }

        [[nodiscard]] auto toString () const noexcept -> String override {
            return String().append("VTransform { \n")
                .append("\tbase = ").append(VComponent::toString()).append(",\n")
                .append("\tlocation = (")
                    .append("x = ").append(this->_location.x).append(", ")
                    .append("y = ").append(this->_location.y).append(", ")
                    .append("z = ").append(this->_location.z).append("),\n")
                .append("\trotation = VRotor { ")
                    .append("yaw = ").append(this->_rotation.yaw()).append(", ")
                    .append("pitch = ").append(this->_rotation.pitch()).append(", ")
                    .append("roll = ").append(this->_rotation.roll()).append("},\n")
                .append("\tscale = (")
                    .append("x = ").append(this->_location.x).append(", ")
                    .append("y = ").append(this->_location.y).append(", ")
                    .append("z = ").append(this->_location.z).append(")\n")
                .append("}");
        }

        ~VTransform() noexcept override = default;
    };

}


#endif //ENG1_VTRANSFORM_H
