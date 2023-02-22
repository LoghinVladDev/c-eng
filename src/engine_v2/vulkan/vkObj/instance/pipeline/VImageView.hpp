//
// Created by Vlad on 17/08/2020.
//

#ifndef ENG1_VIMAGEVIEW_HPP
#define ENG1_VIMAGEVIEW_HPP

#include <VRenderObject.hpp>

#include <vector>
#include <VLogicalDevice.hpp>

namespace engine {

    class VSwapChain;
    class VLogicalDevice;

    class VImageView : public VRenderObject {
    private:
        //// private variables
        VulkanImageView         _handle     {};
        cds :: uint32           _index      {0U};
        VLogicalDevice  const * _pLogicalDevice {nullptr};

        //// private functions

    public:
        //// public variables

        //// public functions
        VImageView () noexcept = default;
        explicit VImageView ( engine::VImageView const *, engine::VLogicalDevice const * ) noexcept;

        ~VImageView() noexcept override = default;

        auto setup ( VulkanImage, VulkanFormat, VLogicalDevice const &, VulkanImageAspectFlags = VulkanImageAspectFlagBits :: VK_IMAGE_ASPECT_COLOR_BIT ) noexcept -> VulkanResult;

        __CDS_NoDiscard auto getSwapChain () const noexcept -> engine::VSwapChain const *;

        __CDS_NoDiscard constexpr auto getLogicalDevicePtr() const noexcept -> engine::VLogicalDevice const * {
            return this->_pLogicalDevice;
        }

        __CDS_NoDiscard constexpr auto data () const noexcept -> VulkanImageView const & {
            return this->_handle;
        }

        auto clear () noexcept -> void override;

        __CDS_NoDiscard auto toString () const noexcept -> cds :: String override;

        __CDS_NoDiscard auto operator == (VImageView const & o) const noexcept -> bool {
            if ( this == & o ) {
                return true;
            }

            return this->_index == o._index && this->_handle == o._handle;
        }

        __CDS_NoDiscard auto equals (Object const & o) const noexcept -> bool override {
            if ( this == & o ) {
                return true;
            }

            auto p = dynamic_cast < decltype(this) > ( & o );
            if ( p == nullptr ) {
                return false;
            }

            return this->operator==(*p);
        }

        __CDS_NoDiscard auto copy () const noexcept -> VImageView * override {
            return new VImageView(*this);
        }

        __CDS_NoDiscard auto hash () const noexcept -> cds :: Index override {
            return cds :: hash(this->_index) * 10000 +
                cds :: hash ( reinterpret_cast < cds :: AddressValueType const > ( this->_handle ) % 10000U );
        }
    };


    class VImageViewCollection : public VRenderObject {
    private:
        //// private variables
        std::vector < VImageView >          _imageViews;

        VSwapChain                  const * _pSwapChain {nullptr};

        //// private functions

    public:
        //// public variables

        //// public functions
        VImageViewCollection () noexcept = default;
//        explicit VImageViewCollection ( const engine::VSwapChain& ) noexcept;
        explicit VImageViewCollection ( engine::VImageViewCollection const *, engine::VSwapChain const * ) noexcept;

        ~VImageViewCollection () noexcept override = default;

        auto setup ( engine::VSwapChain const * ) noexcept -> VulkanResult;

        __CDS_NoDiscard __CDS_MaybeUnused constexpr auto getSwapChainPtr () const noexcept -> engine::VSwapChain const * {
            return this->_pSwapChain;
        }

        __CDS_NoDiscard constexpr auto getImageViews () const noexcept -> std::vector < VImageView > const & {
            return this->_imageViews;
        }

        auto clear () noexcept -> void override;

        __CDS_NoDiscard auto toString () const noexcept -> cds :: String override;

        __CDS_NoDiscard auto operator == (VImageViewCollection const & o) const noexcept -> bool {
            if ( this == & o ) {
                return true;
            }

            return this->_imageViews == o._imageViews;
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

        __CDS_NoDiscard auto copy () const noexcept -> VImageViewCollection * override {
            return new VImageViewCollection (*this);
        }

        __CDS_NoDiscard auto hash () const noexcept -> cds :: Index override {
            cds :: Index hashSum = 0;
            (void) std :: for_each(this->_imageViews.begin(), this->_imageViews.end(), [& hashSum](auto const & o){hashSum += o.hash();});
            return hashSum;
        }
    };

}


#endif //ENG1_VIMAGEVIEW_HPP
