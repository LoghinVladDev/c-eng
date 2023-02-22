//
// Created by vladl on 06/08/2020.
//

#ifndef ENG1_VINSTANCE_HPP
#define ENG1_VINSTANCE_HPP

#include <VRenderObject.hpp>
#include <VValidationLayer.hpp>

namespace engine {

    class VInstance : public VRenderObject {
    private:
        //// private variables
        VulkanInstance _instance {nullptr};
        std::string    _name;

        //// private functions

    public:
        //// public variables
        __CDS_MaybeUnused static cds :: StringLiteral defaultVulkanInstanceTitle;

        static inline cds :: uint32 defaultVulkanApplicationVersion = VK_MAKE_VERSION(1U, 2U, 0U); // NOLINT(clion-misra-cpp2008-8-0-1,clion-misra-cpp2008-5-2-4)
        static inline cds :: uint32 defaultVulkanEngineVersion      = VK_MAKE_VERSION(1U, 2U, 0U); // NOLINT(clion-misra-cpp2008-8-0-1,clion-misra-cpp2008-5-2-4)
        static inline cds :: uint32 defaultVulkanAPIVersion         = VK_API_VERSION_1_2; // NOLINT(clion-misra-cpp2008-5-2-4,clion-misra-cpp2008-8-0-1)

        //// public functions
        VInstance() noexcept = default;
        explicit VInstance ( std::string appTitle ) noexcept :
                VRenderObject(),
                _name(std::move(appTitle)) {

        }

        ~VInstance() noexcept override = default;

        __CDS_MaybeUnused auto setTitle ( std :: string appTitle ) noexcept -> VInstance & {
            this->_name = std::move(appTitle);
            return *this;
        }

        auto setup () noexcept -> VulkanResult;
        auto setup ( VValidationLayerCollection const & ) noexcept -> VulkanResult;

        auto clear() noexcept -> void override;

        __CDS_NoDiscard constexpr auto data() const noexcept -> VulkanInstance const & {
            return this->_instance;
        }

        __CDS_NoDiscard auto toString () const noexcept -> cds :: String override;

        __CDS_NoDiscard auto operator == (VInstance const & o) const noexcept -> bool {

            if ( this == & o ) {
                return true;
            }

            if ( o._instance == this->_instance ) {
                return true;
            }

            return o._name == this->_name;
        }

        __CDS_NoDiscard auto equals (Object const & o) const noexcept -> bool override {

            if ( this == & o ) {
                return true;
            }

            auto p = dynamic_cast < decltype(this) > (& o);
            if ( p == nullptr ) {
                return false;
            }

            return this->operator==(*p);
        }

        __CDS_NoDiscard auto copy () const noexcept -> VInstance * override {
            return new VInstance(* this);
        }

        __CDS_NoDiscard auto hash () const noexcept -> cds :: Index override {
            return cds :: hash(this->_name);
        }
    };

}


#endif //ENG1_VINSTANCE_HPP
