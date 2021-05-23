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
        uint32                  _index      {0U};
        VLogicalDevice  const * _pLogicalDevice {nullptr};

        //// private functions

    public:
        //// public variables

        //// public functions
        VImageView () noexcept = default;
        explicit VImageView ( engine::VImageView const *, engine::VLogicalDevice const * ) noexcept;

        ~VImageView() noexcept override = default;

        auto setup( VulkanImage, VulkanFormat, VLogicalDevice const &, VulkanImageAspectFlags = VulkanImageAspectFlagBits::VK_IMAGE_ASPECT_COLOR_BIT ) noexcept -> VulkanResult;

        [[nodiscard]] auto getSwapChain () const noexcept -> engine::VSwapChain const *;

        [[nodiscard]] constexpr auto getLogicalDevicePtr() const noexcept -> engine::VLogicalDevice const * {
            return this->_pLogicalDevice;
        }

        [[nodiscard]] constexpr auto data () const noexcept -> VulkanImageView const & {
            return this->_handle;
        }

        auto clear () noexcept -> void override;

        [[nodiscard]] auto toString () const noexcept -> String override;
        [[nodiscard]] auto operator == (Object const & o) const noexcept -> bool override {
            if ( this == & o ) return true;
            auto p = dynamic_cast < decltype(this) > ( & o );
            if ( p == nullptr ) return false;

            return this->_index == p->_index && this->_handle == p->_handle;
        }

        [[nodiscard]] auto copy () const noexcept -> VImageView * override {
            return new VImageView(*this);
        }

        [[nodiscard]] auto hash () const noexcept -> Index override {
            return dataTypes::hash(this->_index) * 10000 +
                dataTypes::hash(reinterpret_cast<AddressValueType>(this->_handle) % 10000);
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

        [[nodiscard]] constexpr auto getSwapChainPtr () const noexcept -> engine::VSwapChain const * {
            return this->_pSwapChain;
        }

        [[nodiscard]] constexpr auto getImageViews () const noexcept -> std::vector < VImageView > const & {
            return this->_imageViews;
        }

        auto clear () noexcept -> void override;

        [[nodiscard]] auto toString () const noexcept -> String override;
        [[nodiscard]] auto operator == (Object const & o) const noexcept -> bool override {
            if ( this == & o ) return true;
            auto p = dynamic_cast < decltype(this) > (& o);
            if ( p == nullptr ) return false;

            return this->_imageViews == p->_imageViews;
        }

        [[nodiscard]] auto copy () const noexcept -> VImageViewCollection * override {
            return new VImageViewCollection (*this);
        }

        [[nodiscard]] auto hash () const noexcept -> Index override {
            Index hashSum = 0;
            std::for_each(this->_imageViews.begin(), this->_imageViews.end(), [& hashSum](auto const & o){hashSum += o.hash();});
            return hashSum;
        }
    };

}


#endif //ENG1_VIMAGEVIEW_HPP
