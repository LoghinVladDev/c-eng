//
// Created by Vlad on 10/08/2020.
//

#ifndef ENG1_VQUEUE_H
#define ENG1_VQUEUE_H

#include <engineVulkanPreproc.h>
#include <vkDefs/types/vulkanExplicitTypes.h>
#include <vkObj/instance/device/VLogicalDevice.h>

namespace engine {

    /**
     * Predeclare Logical Device for parent ownership of queue and avoidance
     * of recursive inclusion problem
     */
    class VLogicalDevice;

    /**
     * @class engine::VQueue
     *
     * @brief Representation of a Queue - A bus of communication between the CPU and the GPU
     */
    class VQueue {
    private:

        //// private variables
        constexpr static float  DEFAULT_MIN_QUEUE_PRIORITY  = 0.0f;
        constexpr static float  DEFAULT_MAX_QUEUE_PRIORITY  = 1.0f;

        /// Vulkan Handler for queue
        VulkanQueue             _queueHandler               {};

        /// Family of the queue
        const VQueueFamily    * _parentFamily               {nullptr};

        /// Owner GPU
        const VLogicalDevice  * _parentLogicalDevice        {nullptr};

        /// Priority
        float                   _priority                   {engine::VQueue::DEFAULT_QUEUE_PRIORITY};

        /// Index of the Queue in the Family
        uint32                  _queueIndex                 {0U};

        //// private functions

    public:
        //// public variables
        constexpr static float  DEFAULT_QUEUE_PRIORITY      = DEFAULT_MAX_QUEUE_PRIORITY;

        //// public functions

        /**
         * @brief Default Constructor
         * @exceptsafe
         */
        VQueue () noexcept = default;

        /**
         * @brief Constructor Initialising Queue Family and Priority
         *
         * @param family : engine::VQueueFamily cref = family of the queue
         * @param priority : float = priority assigned to queue. Value between 0.0f - 1.0f (min-max)
         *
         * @exceptsafe
         */
        explicit VQueue ( const engine::VQueueFamily&, float = engine::VQueue::DEFAULT_QUEUE_PRIORITY ) noexcept;

        /**
         * @brief setup function initialising the queue
         *
         * @param logicalDevice: engine::VLogicalDevice cref = logical device owning the queue, where the queue will be created
         * @param index : uint32 = index of queue
         *
         * @exceptsafe
         */
        auto setup ( const VLogicalDevice&, uint32 ) noexcept -> void;

        /**
         * @brief getter for priority
         *
         * @exceptsafe
         *
         * @return float = priority of queue
         */
        [[nodiscard]] constexpr float getPriority () const noexcept {
            return this->_priority;
        }

        /**
         * @brief getter for Logical Device Owner ( GPU Interface )
         *
         * @exceptsafe
         *
         * @return engine::VLogicalDevice cptr = Address to the owner GPU Interface object
         */
        [[nodiscard]] auto getLogicalDevice () const noexcept -> VLogicalDevice const * {
            return this->_parentLogicalDevice;
        }

        /**
         * @brief getter for Parent Queue Family
         *
         * @exceptsafe
         *
         * @return engine::VQueueFamily cptr = Address to the owner queue family object inside the GPU interface
         */
        [[nodiscard]] auto getQueueFamily () const noexcept -> VQueueFamily const * {
            return this->_parentFamily;
        }

        /**
         * @brief getter for the Vulkan Handler associated with the object
         * @return VulkanQueue cref = handler assigned by Vulkan for Vulkan Functions
         */
        [[nodiscard]] auto data () const noexcept -> VulkanQueue const & {
            return this->_queueHandler;
        }

        /**
         * @brief getter for the index in the Queue Family
         *
         * @exceptsafe
         *
         * @return uint32 = index of the queue in the family
         */
        [[nodiscard]] auto getIndex () const noexcept -> uint32 {
            return this->_queueIndex;
        }

        /**
         * @brief function de-allocates the queue in the queue family
         *
         * @exceptsafe
         */
        auto cleanup () noexcept -> void {
            this->_parentFamily->freeQueueIndex (this->_queueIndex);
        }

        /**
         * @brief Destructor for VQueue, default
         *
         * @exceptsafe
         */
        ~VQueue () noexcept = default;
    };

}


#endif //ENG1_VQUEUE_H
