//
// Created by Vlad on 21/08/2020.
//

#ifndef ENG1_VSEMAPHORE_H
#define ENG1_VSEMAPHORE_H

#include <engineVulkanPreproc.h>
#include <vkDefs/types/vulkanExplicitTypes.h>
#include <vkObj/instance/device/VLogicalDevice.h>
#include <vector>

namespace engine {

    class VLogicalDevice;

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

    class VSemaphoreCollection {
    private:
        //// private variables
        std::vector < VSemaphore > _semaphores;
        const VLogicalDevice     * _pLogicalDevice  {nullptr};

        //// private functions

    public:
        //// public variables

        //// public functions
        VSemaphoreCollection () noexcept = default;

        [[nodiscard]] const std::vector < VSemaphore > & getSemaphores () const noexcept {
            return this->_semaphores;
        }

        [[nodiscard]] const VLogicalDevice * getLogicalDevicePtr () const noexcept {
            return this->_pLogicalDevice;
        }

        [[nodiscard]] uint32 size () const noexcept {
            return this->_semaphores.size();
        }

        [[nodiscard]] const VSemaphore & operator [] (uint32 index) const noexcept {
            return this->_semaphores[ index ];
        }

        [[nodiscard]] VSemaphore & operator [] (uint32 index) noexcept {
            return this->_semaphores[ index ];
        }

        VulkanResult setup ( const VLogicalDevice &, uint32 ) noexcept;
        VulkanResult resize ( const VLogicalDevice &, uint32 ) noexcept;

        void cleanup () noexcept;
    };

}




#endif //ENG1_VSEMAPHORE_H
