//
// Created by Vlad on 12/08/2020.
//

#ifndef ENG1_VSURFACE_HPP
#define ENG1_VSURFACE_HPP

#include <VInstance.hpp>

namespace engine {

    class VSurface : public VRenderObject {
    private:
        //// private variables
        VulkanSurfaceKhronos    _surface {};
        VInstance const *       _instance {nullptr};

        //// private functions

    public:
        //// public functions

        //// public variables
        VSurface( ) noexcept = default;
        explicit VSurface ( GLFWwindow * pWindow, VInstance const * pInstance = nullptr ) noexcept : VRenderObject() {
            if (pInstance != nullptr)
                this->setup(pWindow, *pInstance);
        }

        explicit VSurface( GLFWwindow * pWindow, VInstance const & instance) noexcept : VSurface(pWindow, & instance) { }

        ~VSurface() noexcept override = default;

        auto setup ( GLFWwindow*, VInstance const & ) noexcept -> VulkanResult;

        [[nodiscard]] constexpr auto data() const noexcept -> VulkanSurfaceKhronos const & {
            return this->_surface;
        }

        auto clear () noexcept -> void override;

        [[nodiscard]] auto toString () const noexcept -> String override;

        [[nodiscard]] auto operator == (VSurface const & o) const noexcept -> bool {
            if ( this == & o ) return true;
            return this->_surface == o._surface && this->_instance == o._instance;
        }

        [[nodiscard]] auto equals (Object const & o) const noexcept -> bool override {
            if ( this == & o ) return true;
            auto p = dynamic_cast < decltype ( this ) > (& o);
            if ( p == nullptr ) return false;

            return this->operator==(*p);
        }

        [[nodiscard]] auto copy () const noexcept -> VSurface * override {
            return new VSurface(* this);
        }

        [[nodiscard]] auto hash () const noexcept -> Index override {
            return
                dataTypes::hash(reinterpret_cast<AddressValueType>(this->_surface)) +
                dataTypes::hash(reinterpret_cast<AddressValueType>(this->_instance));
        }
    };

}


#endif //ENG1_VSURFACE_HPP
