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

    class VSwapChain {
    private:
        //// private variables
        const VulkanSwapChainKhronos    _handle     {nullptr};
        const VLogicalDevice *          _device     {nullptr};

        //// private functions

    public:
        //// public variables

        //// public functions
        VSwapChain() noexcept = default;
        explicit VSwapChain( const VLogicalDevice* ) noexcept (false);

        VulkanResult setup(  ) noexcept;
        VulkanResult setup( const VLogicalDevice* ) noexcept (false);

        void setLogicalDevice ( const VLogicalDevice* device ) noexcept {
            if( this->_handle != nullptr )
                return;

            this->_device = device;
        }

        void cleanup () noexcept {

        }

        [[nodiscard]] const VSurface* getSurface() const noexcept {
            return this->_surface;
        }

    };

}


#endif //ENG1_VSWAPCHAIN_H
