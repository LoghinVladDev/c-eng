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

        [[nodiscard]] constexpr auto getImageView () const noexcept -> VImageView const & {
            return this->_imageView;
        }

        auto setup (
                VCommandPool    const &,
                uint32          const * = nullptr,
                uint32                  = 0U,
                bool                    = false
        ) noexcept -> VulkanResult;

        auto clear () noexcept -> void override;

        [[nodiscard]] auto toString () const noexcept -> String override;

        [[nodiscard]] auto operator == (VDepthBuffer const & o) const noexcept -> bool {
            if ( this == & o ) return true;
            return this->_image == o._image;
        }

        [[nodiscard]] auto equals (Object const & o) const noexcept -> bool override {
            if ( this == & o ) return true;
            auto p = dynamic_cast < decltype (this) > (& o);
            if ( p == nullptr ) return false;
            return this->operator==(*p);
        }

        [[nodiscard]] auto copy () const noexcept -> VDepthBuffer * override {
            return new VDepthBuffer(* this);
        }

        [[nodiscard]] auto hash () const noexcept -> Index override {
            return dataTypes::hash(
                    reinterpret_cast < AddressValueType > (this->_image) / 100000 +
                    reinterpret_cast < AddressValueType > (this->_imageMemory) / 1000
            ) + dataTypes::hash (
                    static_cast < Size > ( this->_currentLayout )
            ) + this->_imageView.hash();
        }
    };

}


#endif //ENG1_VDEPTHBUFFER_HPP
