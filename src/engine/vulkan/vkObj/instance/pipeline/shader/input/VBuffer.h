//
// Created by loghin on 9/5/20.
//

#ifndef ENG1_VBUFFER_H
#define ENG1_VBUFFER_H

#include <engineVulkanPreproc.h>
#include <vkDefs/types/vulkanExplicitTypes.h>
#include <vkObj/instance/device/VLogicalDevice.h>
#include <vkObj/instance/pipeline/command/VCommandPool.h>

namespace engine {

    /**
     * @class engine::VBuffer
     *
     * @brief Represents a Data Buffer. GPU Local or CPU-GPU shared. Abstract class
     */
    class VBuffer {
    private:
        //// private variables

        /// Handle of the Buffer, allocated by Vulkan
        VulkanBuffer                        _handle             {VK_NULL_HANDLE};

        /// Memory Handle, allocated by Vulkan
        VulkanDeviceMemory                  _memoryHandle       {VK_NULL_HANDLE};

        /// Memory Size
        VulkanDeviceSize                    _memorySize         {0ULL};

        /// Address to Logical Device, on which Data Buffer exists
        VLogicalDevice              const * _pLogicalDevice     {nullptr};

        /// Number of elements in the Buffer
        uint32                              _elementCount       {0U};


        /// Buffer Usage Flags - Combination of Vertex, Index, Uniform, Transfer Destination, Transfer Source.
        VulkanBufferUsageFlags              _bufferUsageFlags   {VULKAN_NULL_FLAGS};

        /// Buffer Memory Sharing Mode. If Queue Family Count > 1, Sharing Mode should be concurrent
        VulkanSharingMode                   _sharingMode        {VulkanSharingMode::VK_SHARING_MODE_EXCLUSIVE};

        /// Buffer Memory Property Flags - CPU-GPU, GPU local etc
        VulkanMemoryPropertyFlags           _memoryPropertyFlags{VULKAN_NULL_FLAGS};

        /// Variable containing Buffer allocation state
        bool                                _memoryAllocated    {false};

        //// private functions

    protected:
        /**
         * @brief Default Constructor. Protected
         *
         * @exceptsafe
         */
        VBuffer () noexcept = default;

        /**
         * @brief Setter for number of elements. Protected, use from Derivates
         *
         * @param elementCount : uint32 = New Number of elements contained
         *
         * @exceptsafe
         */
        auto setElementCount ( uint32 elementCount ) noexcept -> void {
            this->_elementCount = elementCount;
        }

    public:
        //// public variables

        /// Property Flag - Host ( CPU ) can modify memory
        constexpr static VulkanMemoryPropertyFlagBits MEMORY_HOST_COHERENT = VulkanMemoryPropertyFlagBits::VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;

        /// Property Flag - Host ( CPU ) can view memory
        constexpr static VulkanMemoryPropertyFlagBits MEMORY_CPU_WRITEABLE = VulkanMemoryPropertyFlagBits::VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT;

        /// Property Flag - GPU Local Memory
        constexpr static VulkanMemoryPropertyFlagBits MEMORY_GPU_LOCAL     = VulkanMemoryPropertyFlagBits::VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;

        /// Property Flag - CPU-GPU Shared Memory ( Uniform ) - CPU can view and modify
        constexpr static VulkanMemoryPropertyFlags MEMORY_CPU_BUFFER_FLAGS =
                (VulkanBufferUsageFlags) VBuffer::MEMORY_HOST_COHERENT |
                (VulkanBufferUsageFlags) VBuffer::MEMORY_CPU_WRITEABLE;

        /// Property Flag - GPU Local Memory = GPU Local Memory
        constexpr static VulkanMemoryPropertyFlags MEMORY_GPU_BUFFER_FLAGS =
                VBuffer::MEMORY_GPU_LOCAL;


        /// Buffer Usage Flag - Vertex Buffer
        constexpr static VulkanBufferUsageFlagBits VERTEX_BUFFER = VulkanBufferUsageFlagBits::VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;

        /// Buffer Usage Flag - Index Buffer
        constexpr static VulkanBufferUsageFlagBits INDEX_BUFFER = VulkanBufferUsageFlagBits::VK_BUFFER_USAGE_INDEX_BUFFER_BIT;

        /// Buffer Usage Flag - Uniform Buffer
        constexpr static VulkanBufferUsageFlagBits UNIFORM_BUFFER = VulkanBufferUsageFlagBits::VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;

        /// Buffer Usage Flag - Transfer Source Buffer
        constexpr static VulkanBufferUsageFlagBits TRANSFER_SOURCE_BUFFER = VulkanBufferUsageFlagBits::VK_BUFFER_USAGE_TRANSFER_SRC_BIT;

        /// Buffer Usage Flag - Transfer Destination Buffer
        constexpr static VulkanBufferUsageFlagBits TRANSFER_DESTINATION_BUFFER = VulkanBufferUsageFlagBits::VK_BUFFER_USAGE_TRANSFER_DST_BIT;

        /// Buffer Usage Flag - VertexBuffer on GPU = Vertex + Destination Buffer
        constexpr static VulkanBufferUsageFlags VERTEX_BUFFER_GPU_LOCAL =
                (VulkanBufferUsageFlags) VBuffer::VERTEX_BUFFER |
                (VulkanBufferUsageFlags) VBuffer::TRANSFER_DESTINATION_BUFFER;

        /// Buffer Usage Flag - IndexBuffer on GPU = Index + Destination Buffer
        constexpr static VulkanBufferUsageFlags INDEX_BUFFER_GPU_LOCAL =
                (VulkanBufferUsageFlags) VBuffer::INDEX_BUFFER |
                (VulkanBufferUsageFlags) VBuffer::TRANSFER_DESTINATION_BUFFER;

        /// Buffer Usage Flag - Staging Buffer ( transfer buffer ) = Source Buffer
        constexpr static VulkanBufferUsageFlags STAGING_BUFFER_CPU_LOCAL =
                VBuffer::TRANSFER_SOURCE_BUFFER;

        /// Buffer Usage Flag - VertexBuffer on CPU = Vertex Buffer
        constexpr static VulkanBufferUsageFlags VERTEX_BUFFER_CPU_LOCAL =
                VBuffer::VERTEX_BUFFER;

        /// Buffer Usage Flag - UniformBuffer on CPU = Uniform Buffer
        constexpr static VulkanBufferUsageFlags UNIFORM_BUFFER_CPU_LOCAL =
                VBuffer::UNIFORM_BUFFER;


        /// Memory Sharing Mode - Concurrent
        constexpr static VulkanSharingMode TRANSFER_CONCURRENCY = VulkanSharingMode::VK_SHARING_MODE_CONCURRENT;

        /// Memory Sharing Mode - Exclusive
        constexpr static VulkanSharingMode TRANSFER_EXCLUSIVITY = VulkanSharingMode::VK_SHARING_MODE_EXCLUSIVE;

        //// public functions

        /**
         * @brief Function returns optimal Sharing Mode according to device and used queue families
         *
         * @param forceExclusive : bool = if true, force exclusive mode
         * @param queueFamilyIndexCount : uint32 = number of queue families used. If > 1, will go concurrent
         * @param device : VLogicalDevice cref = Constant Reference to Logical Device. Used to check for transfer queue existence. If no transfer queue, go exclusive
         *
         * @exceptsafe
         *
         * @return VulkanSharingMode = Optimal Sharing Mode
         */
        [[nodiscard]] constexpr static auto getOptimalSharingMode (
                bool                    forceExclusive,
                uint32                  queueFamilyIndexCount,
                VLogicalDevice  const & device
        ) noexcept -> VulkanSharingMode {
            return (
                forceExclusive              || /// forcing exclusivity
                queueFamilyIndexCount <= 1  || /// not enough queue families
                device.getFirstTransferQueuePtr() == nullptr /// no transfer queue
            ) ? VBuffer::TRANSFER_EXCLUSIVITY : VBuffer::TRANSFER_CONCURRENCY; /// go exclusive, else go concurrent
        }

        /**
         * @brief Function checks if buffer is Source Buffer
         *
         * @exceptsafe
         *
         * @return bool = true if Buffer is Source, false otherwise
         */
        [[nodiscard]] constexpr auto isSourceBuffer () const noexcept -> bool {
            return static_cast < bool > (this->_bufferUsageFlags & static_cast < VulkanBufferUsageFlags > ( VBuffer::TRANSFER_SOURCE_BUFFER ) );
        }

        /**
         * @brief Function checks if buffer is Destination Buffer
         *
         * @exceptsafe
         *
         * @return bool = true if Buffer is Destination, false otherwise
         */
        [[nodiscard]] constexpr auto isDestinationBuffer () const noexcept -> bool {
            return static_cast < bool > (this->_bufferUsageFlags & static_cast < VulkanBufferUsageFlags > ( VBuffer::TRANSFER_DESTINATION_BUFFER ) );
        }

        /**
         * @brief Function Initialises Buffer, creating memory layout and creating handle. Overwritable
         *
         * @param device : engine::VLogicalDevice cref = Constant Reference to Logical Device
         * @param dataSize : std::size_t = Size of Buffer
         * @param usageFlags : VulkanBufferUsageFlags = flags for usage - vertex / index / ...
         * @param sharingMode : VulkanSharingMode = Concurrent / Exclusive
         * @param pQueueFamilyIndices : uint32 cptr = Address of one / an array of Queue Family Indices
         * @param queueFamilyIndexCount : uint32 = Number of passed Queue Family Indices at the address above
         *
         * @exceptsafe
         *
         * @return VulkanResult =
         *      VulkanResult::VK_SUCCESS if initialisation was successful OR
         *      VulkanResult::VK_ERROR_INITIALIZATION_FAILED if Concurrency Mode Chosen but not supported OR
         *      VulkanResult returned vkCreateBuffer on error occurrence - internal vulkan function
         */
        virtual auto setup (
            VLogicalDevice          const &,
            std::size_t,
            VulkanBufferUsageFlags,
            VulkanSharingMode,
            uint32                  const *,
            uint32
        ) noexcept -> VulkanResult;

        /**
         * @brief Function Allocates Buffer Memory. Overwritable
         *
         * @param memoryPropertyFlags : VulkanMemoryPropertyFlags = Memory Properties = GPU / CPU Memory
         *
         * @exceptsafe
         *
         * @return VulkanResult =
         *      VulkanResult::VK_SUCCESS if
         */
        virtual auto allocateMemory (
            VulkanMemoryPropertyFlags
        ) noexcept -> VulkanResult;

        virtual VulkanResult load (
            const void *pData,
            std::size_t
        ) noexcept;

        virtual void free() noexcept;
        virtual void cleanup() noexcept;
        VulkanResult copyFrom ( const VBuffer &, const VCommandPool &, VulkanDeviceSize = 0U ) noexcept;

        [[nodiscard]] const VulkanBuffer & data () const noexcept {
            return this->_handle;
        }

        [[nodiscard]] VulkanDeviceSize size () const noexcept {
            return this->_memorySize;
        }

        [[nodiscard]] VulkanBufferUsageFlags getBufferUsageFlags () const noexcept {
            return this->_bufferUsageFlags;
        }

        [[nodiscard]] uint32 getElementCount () const noexcept {
            return this->_elementCount;
        }

        [[nodiscard]] VulkanSharingMode getBufferSharingMode () const noexcept {
            return this->_sharingMode;
        }
    };

}


#endif //ENG1_VBUFFER_H
