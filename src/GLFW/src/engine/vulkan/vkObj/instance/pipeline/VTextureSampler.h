//
// Created by loghin on 9/20/20.
//

#ifndef ENG1_VTEXTURESAMPLER_H
#define ENG1_VTEXTURESAMPLER_H

#include <engineVulkanPreproc.h>
#include <vkDefs/types/vulkanExplicitTypes.h>
#include <VLogicalDevice.h>

namespace engine {

    class VTextureSampler {
    private:
        //// private variables
        VulkanSampler             _handle         {VK_NULL_HANDLE};
        const VLogicalDevice    * _pLogicalDevice {nullptr};

        //// private functions

    public:
        //// public variables

        //// public functions
        VTextureSampler() noexcept = default;
        VulkanResult setup ( const VLogicalDevice &, bool = true, float = 16.0f ) noexcept;
        void cleanup () noexcept;

        [[nodiscard]] const VulkanSampler & data () const noexcept {
            return this->_handle;
        }

        [[nodiscard]] const VLogicalDevice * getLogicalDevicePtr () const noexcept {
            return this->_pLogicalDevice;
        }
    };

}


#endif //ENG1_VTEXTURESAMPLER_H
