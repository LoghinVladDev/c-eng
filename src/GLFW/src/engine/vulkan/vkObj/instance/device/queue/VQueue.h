//
// Created by Vlad on 10/08/2020.
//

#ifndef ENG1_VQUEUE_H
#define ENG1_VQUEUE_H

#include <engineVulkanPreproc.h>
#include <vkDefs/types/vulkanExplicitTypes.h>
#include <vkObj/instance/device/VLogicalDevice.h>

namespace engine {

    class VLogicalDevice;

    class VQueue {
    private:

        //// private variables
        constexpr static float  DEFAULT_MIN_QUEUE_PRIORITY  = 0.0f;
        constexpr static float  DEFAULT_MAX_QUEUE_PRIORITY  = 1.0f;

        VulkanQueue             _queueHandler               {};
        const VQueueFamily    * _parentFamily               {nullptr};
        const VLogicalDevice  * _parentLogicalDevice        {nullptr};
        const float             _priority                   {engine::VQueue::DEFAULT_QUEUE_PRIORITY};
        uint32                  _queueIndex                 {0U};
        //// private functions

    public:
        //// public variables
        constexpr static float  DEFAULT_QUEUE_PRIORITY      = DEFAULT_MAX_QUEUE_PRIORITY;

        //// public functions

//        VQueue() noexcept = delete;
//        explicit VQueue(const engine::VLogicalDevice &, const engine::VQueueFamily &, uint32, float = engine::VQueue::DEFAULT_QUEUE_PRIORITY) noexcept;

        VQueue () noexcept = default;
        explicit VQueue ( const engine::VQueueFamily&, float = engine::VQueue::DEFAULT_QUEUE_PRIORITY ) noexcept;

        void setup ( const VLogicalDevice& logicalDevice, uint32 index ) noexcept {
            this->_parentLogicalDevice = ( & logicalDevice );
            this->_queueIndex = index;
            vkGetDeviceQueue( logicalDevice.data(), this->_parentFamily->getQueueFamilyIndex(), index, & this->_queueHandler );
        }

        [[nodiscard]] float getPriority () const noexcept {
            return this->_priority;
        }

        [[nodiscard]] const VLogicalDevice & getLogicalDevice () const noexcept {
            return *this->_parentLogicalDevice;
        }

        [[nodiscard]] const VQueueFamily & getQueueFamily () const noexcept {
            return *this->_parentFamily;
        }

        [[nodiscard]] const VulkanQueue & data () const noexcept {
            return this->_queueHandler;
        }

        ~VQueue () noexcept {
            this->_parentFamily->freeQueueIndex (this->_queueIndex);
        }
    };

}


#endif //ENG1_VQUEUE_H
