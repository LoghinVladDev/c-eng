//
// Created by Vlad on 19/08/2020.
//

#ifndef ENG1_VCOMMANDPOOL_H
#define ENG1_VCOMMANDPOOL_H

#include <engineVulkanPreproc.h>
#include <vkDefs/types/vulkanExplicitTypes.h>
#include <vkObj/instance/device/VLogicalDevice.h>

namespace engine {

    /**
     * @class engine::VCommandPool
     *
     * @brief Represents a Memory Pool for Command Buffers.
     */
    class VCommandPool {
    private:
        //// private variables

        /// Logical Device from on which the Pool will exist, from which the pool allocates memory
        const VLogicalDevice    * _pLogicalDevice   {nullptr};

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
         * @return VulkanResult =
         *      VulkanResult::VK_SUCCESS if initialisation is successful OR
         *      VulkanResult::VK_ERROR_INITIALIZATION_FAILED if no queue family exists on Logical Device OR
         *      VulkanResult from vkCreateCommandPool if error occurred - internal vulkan function
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
        auto cleanup () noexcept -> void;
    };

}


#endif //ENG1_VCOMMANDPOOL_H
