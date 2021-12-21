//
// Created by Vlad on 19/08/2020.
//

#ifndef ENG1_VRENDERPASS_HPP
#define ENG1_VRENDERPASS_HPP

#include <VRenderObject.hpp>
#include <VLogicalDevice.hpp>
#include <CDS/Exception>

namespace engine {

    class EngineVRenderPassDeviceInvalidSwapChain : public cds :: Exception {
    public:
        inline EngineVRenderPassDeviceInvalidSwapChain () noexcept :
                cds :: Exception ("Passed VLogicalDevice has invalid / non-existent swap chain") {
            
        }
    };

    class VRenderPass : public VRenderObject {
    private:
        //// private variables
        VLogicalDevice    const *   _pLogicalDevice {nullptr};
        VulkanRenderPass            _handle         {nullptr};

        //// private functions

    public:
        //// public variables

        //// public functions
        VRenderPass () noexcept = default;
        ~VRenderPass() noexcept override = default;

        __CDS_NoDiscard constexpr auto data () const noexcept -> VulkanRenderPass const & {
            return this->_handle;
        }

        __CDS_NoDiscard constexpr auto getLogicalDevicePtr () const noexcept -> VLogicalDevice const * {
            return this->_pLogicalDevice;
        }

        auto setup (
            engine::VLogicalDevice  const & ,
            VulkanSubpassDependency const * = nullptr,
            cds :: uint32                   = 0U
        ) noexcept (false) -> VulkanResult;

        auto clear () noexcept -> void override;

        __CDS_NoDiscard auto toString () const noexcept -> cds :: String override;

        __CDS_NoDiscard auto operator == (VRenderPass const & o) const noexcept -> bool {
            if ( this == & o ) {
                return true;
            }

            return this->_handle == o._handle;
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

        __CDS_NoDiscard auto copy () const noexcept -> VRenderPass * override {
            return new VRenderPass(* this);
        }

        __CDS_NoDiscard auto hash () const noexcept -> cds :: Index override {
            return cds :: hash ( reinterpret_cast < cds :: AddressValueType const > (this->_handle) );
        }
    };

}


#endif //ENG1_VRENDERPASS_HPP
