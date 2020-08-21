//
// Created by Vlad on 16/08/2020.
//

#ifndef ENG1_VSWAPCHAIN_H
#define ENG1_VSWAPCHAIN_H

#include <engineVulkanPreproc.h>
#include <vkDefs/types/vulkanExplicitTypes.h>
#include <vkObj/window/surface/VSurface.h>
#include <vkObj/instance/device/VLogicalDevice.h>
#include <vkObj/instance/pipeline/VImageView.h>
#include <vkObj/instance/pipeline/synchronization/VSemaphore.h>

#include <vector>

namespace engine {

    class VSemaphore;
    class VLogicalDevice;
    class VImageViewCollection;

    class VSwapChain {
    public:
        typedef struct  {
            VulkanFormat    format;
            VulkanExtent2D  extent;
        } VSwapChainImageInfo;

    private:
        //// private variables
        VulkanSwapChainKhronos          _handle         {VK_NULL_HANDLE};
        const VLogicalDevice *          _device         {nullptr};

        std::vector < VulkanImage >     _images;

//        VulkanFormat                    _imageFormat    {VulkanFormat::VK_FORMAT_A8B8G8R8_SRGB_PACK32};
//        VulkanExtent2D                  _extent         {};

        VSwapChainImageInfo             _imagesInfo     { VulkanFormat::VK_FORMAT_A8B8G8R8_SRGB_PACK32, { } };

        //// private functions

    public:
        //// public variables

        //// public functions
        VSwapChain() noexcept = default;
        explicit VSwapChain( const VLogicalDevice* ) noexcept (false);

        /**
         * enhanced copy ctr to enforce set LD for VSC
         */
        explicit VSwapChain( const VSwapChain&, const VLogicalDevice* ) noexcept;

        [[nodiscard]] const VulkanSwapChainKhronos & data () const noexcept {
            return this->_handle;
        }

        [[nodiscard]] const VSwapChainImageInfo & getImagesInfo () const noexcept {
            return this->_imagesInfo;
        }

        [[nodiscard]] const std::vector < VulkanImage > & getImages () const noexcept {
            return this->_images;
        }

        [[nodiscard]] engine::VImageViewCollection getImageViewCollection () const noexcept;

        VulkanResult setup(  ) noexcept;
        VulkanResult setup( const VLogicalDevice* ) noexcept (false);
        VulkanResult present ( const VSemaphore *, uint32, uint32 ) const noexcept;

        void setLogicalDevice ( const VLogicalDevice* device ) noexcept {
            if( this->_handle != nullptr )
                return;

            this->_device = device;
        }

        void cleanup () noexcept;

        [[nodiscard]] const VLogicalDevice * getDevice () const noexcept {
            return this->_device;
        }
    };

}


#endif //ENG1_VSWAPCHAIN_H
