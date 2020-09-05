//
// Created by Vlad on 19/08/2020.
//

#ifndef ENG1_VCOMMANDPOOL_H
#define ENG1_VCOMMANDPOOL_H

#include <engineVulkanPreproc.h>
#include <vkDefs/types/vulkanExplicitTypes.h>
#include <vkObj/instance/device/VLogicalDevice.h>

namespace engine {

    class VCommandPool {
    private:
        //// private variables
        const VLogicalDevice    * _pLogicalDevice   {nullptr};
        VulkanCommandPool         _handle           {nullptr};

        bool                      _optimizedForTransfers {false};

        //// private functions

    public:
        //// public variables

        //// public functions

        VCommandPool() noexcept = default;

        [[nodiscard]] const VLogicalDevice * getLogicalDevicePtr () const noexcept {
            return this->_pLogicalDevice;
        }

        [[nodiscard]] const VulkanCommandPool & data() const noexcept {
            return this->_handle;
        }

        [[nodiscard]] bool isOptimizedForTransfers () const noexcept {
            return this->_optimizedForTransfers;
        }

        VulkanResult setup ( const VLogicalDevice &, const VQueueFamily * = nullptr ) noexcept;
        void cleanup () noexcept;
    };

}


#endif //ENG1_VCOMMANDPOOL_H
