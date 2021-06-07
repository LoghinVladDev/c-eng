//
// Created by Vlad on 19/08/2020.
//

#ifndef ENG1_VCOMMANDPOOL_HPP
#define ENG1_VCOMMANDPOOL_HPP

#include <VRenderObject.hpp>
#include <VLogicalDevice.hpp>

namespace engine {

    /**
     * @class engine::VCommandPool
     *
     * @brief Represents a Memory Pool for Command Buffers.
     */
    class VCommandPool : public VRenderObject {
    private:
        //// private variables

        /// Logical Device from on which the Pool will exist, from which the pool allocates memory
        VLogicalDevice    const * _pLogicalDevice   {nullptr};

        /// Vulkan Handle for Command Pool
        VulkanCommandPool         _handle           {nullptr};

        /// Variable mentioning whether pool is built for transfer commands or not
        bool                      _optimizedForTransfers {false};

        //// private functions

    public:
        //// public variables

        //// public functions

        /**
         * @brief Default Constructor
         *
         * @exceptsafe
         */
        VCommandPool() noexcept = default;
        ~VCommandPool() noexcept override = default;

        /**
         * @brief Getter function for Logical Device Owner Address
         *
         * @exceptsafe
         *
         * @return engine::VLogicalDevice cptr = Address to a Constant Logical Device the Pool will exist on
         */
        [[nodiscard]] constexpr auto getLogicalDevicePtr () const noexcept -> VLogicalDevice const * {
            return this->_pLogicalDevice;
        }

        /**
         * @brief Getter function for Vulkan Handle for Command Buffer
         *
         * @exceptsafe
         *
         * @return VulkanCommandPool cref = Constant Reference to Handle allocated by Vulkan
         */
        [[nodiscard]] constexpr auto data() const noexcept -> VulkanCommandPool const & {
            return this->_handle;
        }

        /**
         * @brief Function checks if Command Pool is transfer optimised ( uses transfer queue )
         *
         * @exceptsafe
         *
         * @return bool = true if Command Pool is optimised for transfers, false otherwise
         */
        [[nodiscard]] constexpr auto isOptimizedForTransfers () const noexcept -> bool {
            return this->_optimizedForTransfers;
        }

        /**
         * @brief Function initialises the Command Pool on a logical device, with a queue family ( optional )
         *
         * @param device : engine::VLogicalDevice cref = Constant Reference to Logical Device to allocate Command Pool on
         * @param pQueueFamily : engine::VQueueFamily cptr = Address of a Constant Queue Family, to specify queue for Command Pool operations. Optional. If not given ( nullptr ), will acquire a graphical queue
         *
         * @exceptsafe
         *
         * @return VulkanResult::VK_SUCCESS if initialisation is successful OR
         * @return VulkanResult::VK_ERROR_INITIALIZATION_FAILED if no queue family exists on Logical Device OR
         * @return VulkanResult from vkCreateCommandPool if error occurred - internal vulkan function
         */
        auto setup (
                VLogicalDevice  const &,
                VQueueFamily    const * = nullptr
        ) noexcept -> VulkanResult;

        /**
         * @brief Function de-allocates any Handles created by Vulkan
         *
         * @exceptsafe
         */
        auto clear () noexcept -> void override;

        [[nodiscard]] auto toString () const noexcept -> String override;

        [[nodiscard]] auto operator == (VCommandPool const & o) const noexcept -> bool {
            if ( this == & o ) return true;

            return this->_handle == o._handle;
        }

        [[nodiscard]] auto equals (Object const & o) const noexcept -> bool override {
            if ( this == & o ) return true;
            auto p = dynamic_cast < decltype ( this ) > ( & o );
            if ( p == nullptr ) return false;

            return this->operator==(*p);
        }

        [[nodiscard]] auto hash () const noexcept -> Index override {
            return dataTypes::hash(reinterpret_cast<AddressValueType>(this->_handle));
        }

        [[nodiscard]] auto copy () const noexcept -> VCommandPool * override {
            return new VCommandPool(* this);
        }
    };

}


#endif //ENG1_VCOMMANDPOOL_HPP
