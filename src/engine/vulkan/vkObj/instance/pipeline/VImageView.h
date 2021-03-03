//
// Created by Vlad on 17/08/2020.
//

#ifndef ENG1_VIMAGEVIEW_H
#define ENG1_VIMAGEVIEW_H

#include <engineVulkanPreproc.h>
#include <vector>
//#include <vkObj/instance/device/VSwapChain.h>
#include <VLogicalDevice.h>

namespace engine {

    class VSwapChain;
    class VLogicalDevice;

    class VImageView {
    private:
        //// private variables
        VulkanImageView         _handle     {};
        uint32                  _index      {0U};

//        const VSwapChain  * _pSwapChain { nullptr };
        const VLogicalDevice  * _pLogicalDevice {nullptr};

        //// private functions

    public:
        //// public variables

        //// public functions
        VImageView () noexcept = default;
        explicit VImageView ( const engine::VImageView *, const engine::VLogicalDevice * ) noexcept;

        VulkanResult setup( VulkanImage, VulkanFormat, const VLogicalDevice&, VulkanImageAspectFlags = VulkanImageAspectFlagBits::VK_IMAGE_ASPECT_COLOR_BIT ) noexcept;

        [[nodiscard]] const engine::VSwapChain * getSwapChain () const noexcept;

        [[nodiscard]] const engine::VLogicalDevice * getLogicalDevicePtr() const noexcept {
            return this->_pLogicalDevice;
        }

        [[nodiscard]] const VulkanImageView & data () const noexcept {
            return this->_handle;
        }

        void cleanup() noexcept;
    };


    class VImageViewCollection {
    private:
        //// private variables
        std::vector < VImageView >  _imageViews;

        const VSwapChain *          _pSwapChain {nullptr};

        //// private functions

    public:
        //// public variables

        //// public functions
        VImageViewCollection () noexcept = default;
//        explicit VImageViewCollection ( const engine::VSwapChain& ) noexcept;
        explicit VImageViewCollection ( const engine::VImageViewCollection *, const engine::VSwapChain * ) noexcept;

        VulkanResult setup ( const engine::VSwapChain * ) noexcept;

        [[nodiscard]] const engine::VSwapChain * getSwapChain () const noexcept {
            return this->_pSwapChain;
        }

        [[nodiscard]] const std::vector < VImageView > & getImageViews () const noexcept {
            return this->_imageViews;
        }

        void cleanup () noexcept;
    };

}


#endif //ENG1_VIMAGEVIEW_H
