//
// Created by vladl on 20/08/2020.
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
        const VLogicalDevice *  _pLogicalDevice {nullptr};
        VulkanSemaphore         _handle         {nullptr};

        //// private functions

    public:
        //// public variables

        //// public functions

        VSemaphore() noexcept = default;

        void cleanup ( ) noexcept;
        VulkanResult setup ( const engine::VLogicalDevice & ) noexcept;

        [[nodiscard]] const VulkanSemaphore & data () const noexcept {
            return this->_handle;
        }
    };

}


#endif //ENG1_VSEMAPHORE_H
