//
// Created by vladl on 9/21/2020.
//

#ifndef ENG1_VDEPTHBUFFER_HPP
#define ENG1_VDEPTHBUFFER_HPP

#include <VRenderObject.hpp>
#include <VCommandPool.hpp>
#include <VImageView.hpp>

namespace engine {

    class VDepthBuffer : public VRenderObject {
    private:
        //// private variables
        VulkanImage             _image          {VK_NULL_HANDLE};
        VulkanDeviceMemory      _imageMemory    {VK_NULL_HANDLE};
        VImageView              _imageView;
        VulkanImageLayout       _currentLayout  {VulkanImageLayout::VK_IMAGE_LAYOUT_UNDEFINED};

        VCommandPool    const * _pCommandPool   {nullptr};

        VulkanSharingMode       _sharingMode    {VulkanSharingMode::VK_SHARING_MODE_EXCLUSIVE};
        VulkanFormat            _format         {VulkanFormat::VK_FORMAT_D32_SFLOAT};

        //// private functions
        auto transitionImageLayout ( VulkanImageLayout ) noexcept -> VulkanResult;

    public:
        //// public variables

        //// public functions
        VDepthBuffer () noexcept = default;
        ~VDepthBuffer() noexcept override = default;

        __CDS_NoDiscard constexpr auto getImageView () const noexcept -> VImageView const & {
            return this->_imageView;
        }

        auto setup (
                VCommandPool    const &,
                cds :: uint32   const * = nullptr,
                cds :: uint32           = 0U,
                bool                    = false
        ) noexcept -> VulkanResult;

        auto clear () noexcept -> void override;

        __CDS_NoDiscard auto toString () const noexcept -> cds :: String override;

        __CDS_NoDiscard auto operator == (VDepthBuffer const & o) const noexcept -> bool {
            if ( this == & o ) {
                return true;
            }

            return this->_image == o._image;
        }

        __CDS_NoDiscard auto equals (Object const & o) const noexcept -> bool override {
            if ( this == & o ) {
                return true;
            }

            auto p = dynamic_cast < decltype (this) > (& o);
            if ( p == nullptr ) {
                return false;
            }

            return this->operator==(*p);
        }

        __CDS_NoDiscard auto copy () const noexcept -> VDepthBuffer * override {
            return new VDepthBuffer(* this);
        }

        __CDS_NoDiscard auto hash () const noexcept -> cds :: Index override {
            return cds :: hash(
                    reinterpret_cast < cds :: AddressValueType const > (this->_image) / 100000U +
                    reinterpret_cast < cds :: AddressValueType const > (this->_imageMemory) / 1000U
            ) + cds :: hash (
                    static_cast < cds :: Size > ( this->_currentLayout )
            ) + this->_imageView.hash();
        }
    };

}


#endif //ENG1_VDEPTHBUFFER_HPP
