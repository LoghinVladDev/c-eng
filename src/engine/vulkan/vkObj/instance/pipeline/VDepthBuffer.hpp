//
// Created by vladl on 9/21/2020.
//

#ifndef ENG1_VDEPTHBUFFER_HPP
#define ENG1_VDEPTHBUFFER_HPP

#include <engineVulkanPreproc.hpp>
#include <vkDefs/types/vulkanExplicitTypes.h>
#include <VCommandPool.hpp>
#include <VImageView.hpp>

namespace engine {

    class VDepthBuffer {
    private:
        //// private variables
        VulkanImage             _image          {VK_NULL_HANDLE};
        VulkanDeviceMemory      _imageMemory    {VK_NULL_HANDLE};
        VImageView              _imageView;
        VulkanImageLayout       _currentLayout  {VulkanImageLayout::VK_IMAGE_LAYOUT_UNDEFINED};

        const VCommandPool    * _pCommandPool   {nullptr};

        VulkanSharingMode       _sharingMode    {VulkanSharingMode::VK_SHARING_MODE_EXCLUSIVE};
        VulkanFormat            _format         {VulkanFormat::VK_FORMAT_D32_SFLOAT};

        //// private functions
        VulkanResult transitionImageLayout ( VulkanImageLayout ) noexcept;

    public:
        //// public variables

        //// public functions
        VDepthBuffer () noexcept = default;

        [[nodiscard]] const VImageView & getImageView () const noexcept {
            return this->_imageView;
        }

        VulkanResult setup (
                const VCommandPool &,
                const uint32 * = nullptr,
                uint32 = 0U,
                bool = false
        ) noexcept;

        void cleanup () noexcept;
    };

}


#endif //ENG1_VDEPTHBUFFER_HPP
