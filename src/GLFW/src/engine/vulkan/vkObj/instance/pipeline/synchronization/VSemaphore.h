//
// Created by Vlad on 21/08/2020.
//

#ifndef ENG1_VSEMAPHORE_H
#define ENG1_VSEMAPHORE_H

#include <engineVulkanPreproc.h>
#include <vkDefs/types/vulkanExplicitTypes.h>
#include <vkObj/instance/device/VLogicalDevice.h>

namespace engine {

    class VSemaphore {
    private:
        //// private variables
        VulkanSemaphore           _handle         {nullptr};
        const VLogicalDevice    * _pLogicalDevice {nullptr};

        //// private functions

    public:
        //// public variables

        //// public functions
        VSemaphore () noexcept = default;

        VulkanResult setup ( const VLogicalDevice & ) noexcept;
        void cleanup () noexcept;

        [[nodiscard]] const VulkanSemaphore & data () const noexcept {
            return this->_handle;
        }
    };

}


#endif //ENG1_VSEMAPHORE_H
