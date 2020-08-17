//
// Created by Vlad on 16/08/2020.
//

#ifndef ENG1_VSWAPCHAIN_H
#define ENG1_VSWAPCHAIN_H

#include <engineVulkanPreproc.h>
#include <vkDefs/types/vulkanExplicitTypes.h>
#include <vkObj/window/surface/VSurface.h>
#include <vkObj/instance/device/VLogicalDevice.h>


namespace engine {

    class VLogicalDevice;

    class VSwapChain {
    private:
        //// private variables
        VulkanSwapChainKhronos          _handle     {VK_NULL_HANDLE};
        const VLogicalDevice *          _device     {nullptr};

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

        VulkanResult setup(  ) noexcept;
        VulkanResult setup( const VLogicalDevice* ) noexcept (false);

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
