//
// Created by loghin on 9/20/20.
//

#ifndef ENG1_VTEXTURESAMPLER_HPP
#define ENG1_VTEXTURESAMPLER_HPP

#include <VRenderObject.hpp>
#include <VLogicalDevice.hpp>

namespace engine {

    class VTextureSampler : public VRenderObject {
    private:
        //// private variables
        VulkanSampler             _handle         {VK_NULL_HANDLE};
        VLogicalDevice    const * _pLogicalDevice {nullptr};

        //// private functions

    public:
        //// public variables

        //// public functions
        VTextureSampler() noexcept = default;
        ~VTextureSampler() noexcept override = default;

        auto setup ( const VLogicalDevice &, bool = true, float = 16.0F ) noexcept -> VulkanResult;
        auto clear () noexcept -> void override;

        __CDS_NoDiscard constexpr auto data () const noexcept -> VulkanSampler const & {
            return this->_handle;
        }

        __CDS_NoDiscard constexpr auto getLogicalDevicePtr () const noexcept -> VLogicalDevice const * {
            return this->_pLogicalDevice;
        }

        __CDS_NoDiscard auto toString () const noexcept -> cds :: String override;

        __CDS_NoDiscard auto operator == ( VTextureSampler const & o ) const noexcept -> bool {
            if ( this == & o ) {
                return true;
            }

            return this->_handle == o._handle;
        }


        __CDS_NoDiscard auto equals ( Object const & o ) const noexcept -> bool override {
            if ( this == & o ) {
                return true;
            }

            auto p = dynamic_cast < decltype(this) > (& o);
            if ( p == nullptr ) {
                return false;
            }

            return this->operator==(*p);
        }

        __CDS_NoDiscard auto copy () const noexcept -> VTextureSampler * override {
            return new VTextureSampler ( * this );
        }

        __CDS_NoDiscard auto hash () const noexcept -> cds :: Index override {
            return cds :: hash ( reinterpret_cast < cds :: AddressValueType const > (this->_handle) );
        }
    };

}


#endif //ENG1_VTEXTURESAMPLER_HPP
