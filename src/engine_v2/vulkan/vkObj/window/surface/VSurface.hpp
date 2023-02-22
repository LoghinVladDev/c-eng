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
        explicit VSurface ( GLFWwindow * pWindow, VInstance const * pInstance = nullptr ) noexcept :
                VRenderObject() {

            if (pInstance != nullptr) {
                (void) this->setup(pWindow, *pInstance);
            }
        }

        explicit VSurface( GLFWwindow * pWindow, VInstance const & instance ) noexcept : VSurface(pWindow, & instance) { }

        ~VSurface() noexcept override = default;

        auto setup ( GLFWwindow *, VInstance const & ) noexcept -> VulkanResult;

        __CDS_NoDiscard constexpr auto data() const noexcept -> VulkanSurfaceKhronos const & {
            return this->_surface;
        }

        auto clear () noexcept -> void override;

        __CDS_NoDiscard auto toString () const noexcept -> cds :: String override;

        __CDS_NoDiscard auto operator == ( VSurface const & o ) const noexcept -> bool {
            if ( this == & o ) {
                return true;
            }

            return this->_surface == o._surface && this->_instance == o._instance;
        }

        __CDS_NoDiscard auto equals ( Object const & o ) const noexcept -> bool override {
            if ( this == & o ) {
                return true;
            }

            auto p = dynamic_cast < decltype ( this ) > (& o);
            if ( p == nullptr ) {
                return false;
            }

            return this->operator==(*p);
        }

        __CDS_NoDiscard auto copy () const noexcept -> VSurface * override {
            return new VSurface(* this);
        }

        __CDS_NoDiscard auto hash () const noexcept -> cds :: Index override {
            return
                cds :: hash ( reinterpret_cast < cds :: AddressValueType > (this->_surface) ) +
                cds :: hash ( reinterpret_cast < cds :: AddressValueType const > (this->_instance) );
        }
    };

}


#endif //ENG1_VSURFACE_HPP
