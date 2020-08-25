//
// Created by Vlad on 21/08/2020.
//

#ifndef ENG1_VFENCE_H
#define ENG1_VFENCE_H

#include <engineVulkanPreproc.h>
#include <vkDefs/types/vulkanExplicitTypes.h>
#include <vkObj/instance/device/VLogicalDevice.h>
namespace engine {

    class VFence {
    private:
        //// private variables
        VulkanFence             _handle         {nullptr};
        const VLogicalDevice  * _pLogicalDevice {nullptr};

        //// private functions

    public:
        //// public variables

        //// public functions
        VFence () noexcept = default;

        VulkanResult setup () noexcept;
        void cleanup () noexcept;
    };

}


#endif //ENG1_VFENCE_H
