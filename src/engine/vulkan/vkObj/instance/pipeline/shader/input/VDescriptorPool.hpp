//
// Created by Vlad on 07/09/2020.
//

#ifndef ENG1_VDESCRIPTORPOOL_HPP
#define ENG1_VDESCRIPTORPOOL_HPP

#include <engineVulkanPreproc.hpp>
#include <vkDefs/types/vulkanExplicitTypes.h>
#include <vkObj/instance/device/VLogicalDevice.hpp>

namespace engine {

    /**
     * @class engine::VDescriptorPool
     *
     * @brief Represents a Pool of Memory for Descriptors <- bindings for CPU-GPU shared memory, assigned in layouts
     * Descriptor Sets will be allocated from a pool
     */
    class VDescriptorPool {
    private:
        //// private variables

        /// Internal Vulkan Handle of the Descriptor Pool
        VulkanDescriptorPool    _handle         {VK_NULL_HANDLE};

        /// Address of the Logical Device
        VLogicalDevice  const * _pLogicalDevice {nullptr};

        //// private functions

    public:
        //// public variables

        //// public functions

        /**
         * @brief Default Constructor
         *
         * @exceptsafe
         */
        VDescriptorPool() noexcept = default;

        /**
         * @brief Function Initialises Descriptor Pool
         *
         * @param device : engine::VLogicalDevice cref = Constant Reference to create Descriptor Pool from
         * @param pDescriptorTypes : VulkanDescriptorType cptr = Address to one / an array of Descriptor Types to be allocated from this pool
         * @param descriptorTypeCount : uint32 = Number of descriptor types at address attached
         * @param objectCount : uint32 = Number of Objects ( Uniform Buffers ) that will require one of each Descriptor Type.
         *
         * => Pool = ( descriptor types ) * no. of objects
         *
         * @exceptsafe
         *
         * @return VulkanResult::VK_SUCCESS if Descriptor Pool initialisation successful OR
         * @return VulkanResult returned by vkCreateDescriptorPool if error occurred - vulkan internal function
         */
        auto setup (
                VLogicalDevice          const &,
                VulkanDescriptorType    const *,
                uint32,
                uint32
        ) noexcept -> VulkanResult;

        /**
         * @brief Function de-allocates any Vulkan Allocated Handle
         *
         * @exceptsafe
         */
        auto cleanup() noexcept -> void;

        /**
         * @brief Getter for Descriptor Pool Handle
         *
         * @exceptsafe
         *
         * @return VulkanDescriptorPool cref = Constant Reference to the Vulkan Allocated Handle
         */
        [[nodiscard]] auto data () const noexcept -> VulkanDescriptorPool const & {
            return this->_handle;
        }

        /**
         * @brief Getter for Logical Device Address
         *
         * @exceptsafe
         *
         * @return VLogicalDevice cptr = Address to Constant Logical Device
         */
        [[nodiscard]] auto getLogicalDevicePtr () const noexcept -> VLogicalDevice const * {
            return this->_pLogicalDevice;
        }
    };

}


#endif //ENG1_VDESCRIPTORPOOL_HPP
