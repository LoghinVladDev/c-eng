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
        /// TODO : fix:0002. Make Returns from queueFamily by type to return std::vector < VQueueFamily*> instead of std::vector < VQueueFamily >.
        VulkanQueue             _queueHandler               {};
        const VQueueFamily    * _parentFamily               {nullptr}; // fix:0002 temporary fix for problematic pointer
//        VQueueFamilyCollection* _parentFamilyCollection     {nullptr};
        const VLogicalDevice  * _parentLogicalDevice        {nullptr};
        float                   _priority                   {engine::VQueue::DEFAULT_QUEUE_PRIORITY};
        uint32                  _queueIndex                 {0U};
//        uint32                  _queueFamilyIndex           {0U}; // fix:0002 temporary fix for problematic pointer issue
        //// private functions

    public:
        //// public variables
        constexpr static float  DEFAULT_QUEUE_PRIORITY      = DEFAULT_MAX_QUEUE_PRIORITY;

        //// public functions

        VQueue () noexcept = default;
        explicit VQueue ( const engine::VQueueFamily&, float = engine::VQueue::DEFAULT_QUEUE_PRIORITY ) noexcept;

        void setup ( const VLogicalDevice&, uint32 ) noexcept;
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

        [[nodiscard]] uint32 getIndex () const noexcept {
            return this->_queueIndex;
        }

        void cleanup () noexcept {
            this->_parentFamily->freeQueueIndex (this->_queueIndex);
        }

        ~VQueue () noexcept = default;
    };

}


#endif //ENG1_VQUEUE_H
