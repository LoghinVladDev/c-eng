//
// Created by Vlad on 10/08/2020.
//

#ifndef ENG1_VQUEUE_HPP
#define ENG1_VQUEUE_HPP

#include <VRenderObject.hpp>
#include <VLogicalDevice.hpp>

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
    class VQueue : public VRenderObject {
    private:

        //// private variables
        constexpr static float  DEFAULT_MIN_QUEUE_PRIORITY  = 0.0f;
        constexpr static float  DEFAULT_MAX_QUEUE_PRIORITY  = 1.0f;

        /// Vulkan Handler for queue
        VulkanQueue             _handle                     {};

        /// Family of the queue
        VQueueFamily    const * _parentFamily               {nullptr};

        /// Owner GPU
        VLogicalDevice  const * _parentLogicalDevice        {nullptr};

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
        explicit VQueue ( engine::VQueueFamily const &, float = engine::VQueue::DEFAULT_QUEUE_PRIORITY ) noexcept;

        /**
         * @brief setup function initialising the queue
         *
         * @param logicalDevice: engine::VLogicalDevice cref = logical device owning the queue, where the queue will be created
         * @param index : uint32 = index of queue
         *
         * @exceptsafe
         */
        auto setup ( VLogicalDevice const &, uint32 ) noexcept -> void;

        /**
         * @brief getter for priority
         *
         * @exceptsafe
         *
         * @return float = priority of queue
         */
        [[nodiscard]] constexpr auto getPriority () const noexcept -> float {
            return this->_priority;
        }

        /**
         * @brief getter for Logical Device Owner ( GPU Interface )
         *
         * @exceptsafe
         *
         * @return engine::VLogicalDevice cptr = Address to the owner GPU Interface object
         */
        [[nodiscard]] constexpr auto getLogicalDevicePtr () const noexcept -> VLogicalDevice const * {
            return this->_parentLogicalDevice;
        }

        /**
         * @brief getter for Parent Queue Family
         *
         * @exceptsafe
         *
         * @return engine::VQueueFamily cptr = Address to the owner queue family object inside the GPU interface
         */
        [[nodiscard]] constexpr auto getQueueFamilyPtr () const noexcept -> VQueueFamily const * {
            return this->_parentFamily;
        }

        /**
         * @brief getter for the Vulkan Handler associated with the object
         * @return VulkanQueue cref = handler assigned by Vulkan for Vulkan Functions
         */
        [[nodiscard]] constexpr auto data () const noexcept -> VulkanQueue const & {
            return this->_handle;
        }

        /**
         * @brief getter for the index in the Queue Family
         *
         * @exceptsafe
         *
         * @return uint32 = index of the queue in the family
         */
        [[nodiscard]] constexpr auto getIndex () const noexcept -> uint32 {
            return this->_queueIndex;
        }

        /**
         * @brief function de-allocates the queue in the queue family
         *
         * @exceptsafe
         */
        auto clear () noexcept -> void override {
            this->_parentFamily->freeQueueIndex (this->_queueIndex);
        }

        /**
         * @brief Destructor for VQueue, default
         *
         * @exceptsafe
         */
        ~VQueue () noexcept override = default;

        [[nodiscard]] auto toString () const noexcept -> String override;
        [[nodiscard]] auto operator == (Object const & o) const noexcept -> bool override {
            if ( this == & o ) return true;
            auto p = dynamic_cast < decltype (this) > (& o);

            return this->_queueIndex == p->_queueIndex && this->_handle == p->_handle;
        }

        [[nodiscard]] auto hash () const noexcept -> Index override {
            return
                dataTypes::hash ( reinterpret_cast < AddressValueType > ( this->_parentFamily ) ) % 256 +
                dataTypes::hash ( this->_queueIndex );
        }

        [[nodiscard]] auto copy () const noexcept -> VQueue * override {
            return new VQueue(* this);
        }
    };

}


#endif //ENG1_VQUEUE_HPP
