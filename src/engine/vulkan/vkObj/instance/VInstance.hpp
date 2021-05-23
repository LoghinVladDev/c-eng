//
// Created by vladl on 06/08/2020.
//

#ifndef ENG1_VINSTANCE_HPP
#define ENG1_VINSTANCE_HPP

#include <VRenderObject.hpp>
#include <VValidationLayer.hpp>

#include <utility>
namespace engine {

    class VInstance : public VRenderObject {
    private:
        //// private variables
        VulkanInstance _instance {nullptr};
        std::string    _name;

        //// private functions

    public:
        //// public variables
        [[maybe_unused]] static const char* DEFAULT_VULKAN_INSTANCE_TITLE;

        //// public functions
        VInstance() noexcept = default;
        explicit VInstance(std::string appTitle) noexcept : VRenderObject(), _name(std::move(appTitle)) { }

        ~VInstance() noexcept override = default;

        auto setTitle(std::string appTitle) noexcept -> VInstance & {
            this->_name = std::move(appTitle);
            return *this;
        }

        auto setup() noexcept -> VulkanResult;
        auto setup( const VValidationLayerCollection &) noexcept -> VulkanResult;

        auto clear() noexcept -> void override;

        [[nodiscard]] constexpr auto data() const noexcept -> VulkanInstance const & {
            return this->_instance;
        }

        [[nodiscard]] auto toString () const noexcept -> String override;
        [[nodiscard]] auto operator == (Object const & o) const noexcept -> bool override {
            if ( this == & o ) return true;
            auto p = dynamic_cast < decltype(this) > (& o);
            if ( p == nullptr ) return false;
            if ( p->_instance == this->_instance ) return true;

            return p->_name == this->_name;
        }

        [[nodiscard]] auto copy () const noexcept -> VInstance * override {
            return new VInstance(* this);
        }

        [[nodiscard]] auto hash () const noexcept -> Index override {
            return dataTypes::hash(this->_name);
        }
    };

}


#endif //ENG1_VINSTANCE_HPP
