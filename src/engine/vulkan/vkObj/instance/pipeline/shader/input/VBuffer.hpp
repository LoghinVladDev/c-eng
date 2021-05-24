//
// Created by loghin on 9/5/20.
//

#ifndef ENG1_VBUFFER_HPP
#define ENG1_VBUFFER_HPP

#include <VRenderObject.hpp>
#include <VLogicalDevice.hpp>
#include <VCommandPool.hpp>

namespace engine {

    /**
     * @class engine::VBuffer
     *
     * @brief Represents a Data Buffer. GPU Local or CPU-GPU shared. Abstract class
     */
    class VBuffer : public VRenderObject {
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

        ~VBuffer() noexcept override = default;

        /**
         * @brief Setter for number of elements. Protected, use from Derivates
         *
         * @param elementCount : uint32 = New Number of elements contained
         *
         * @exceptsafe
         */
        constexpr auto setElementCount ( uint32 elementCount ) noexcept -> void {
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
         * @return VulkanResult::VK_SUCCESS if initialisation was successful OR
         * @return VulkanResult::VK_ERROR_INITIALIZATION_FAILED if Concurrency Mode Chosen but not supported OR
         * @return VulkanResult returned vkCreateBuffer on error occurrence - internal vulkan function
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
         * @return VulkanResult::VK_SUCCESS if allocate of memory was successful OR
         * @return VulkanResult::VK_ERROR_INITIALIZATION_FAILED if memory type requested is not available OR
         * @return VulkanResult returned by vkAllocateMemory on error occurrence - internal vulkan function OR
         * @return VulkanResult returned by vkBindBufferMemory on error occurrence - internal vulkan function
         */
        virtual auto allocateMemory (
            VulkanMemoryPropertyFlags
        ) noexcept -> VulkanResult;

        /**
         * @brief Function Loads Data into Buffer. Overwritable
         *
         * Buffer will load a map from memory, copy data from address to map address, and unmap memory
         *
         * @param pData : void cptr = Address to Data to Load
         * @param dataSize : uint32 = Number of bytes to load from given address
         *
         * @exceptsafe
         *
         * @return VulkanResult::VK_SUCCESS if loading of memory onto buffer was successful OR
         * @return VulkanResult::VK_ERROR_MEMORY_MAP_FAILED if Memory was not allocated with flag MEMORY_CPU_WRITABLE OR
         * @return VulkanResult returned by vkMapMemory on error occurrence - internal vulkan function
         */
        virtual auto load (
            void const *,
            std::size_t
        ) noexcept -> VulkanResult;

        /**
         * @brief Function frees previously allocated GPU / CPU memory. Overwritable
         *
         * @exceptsafe
         */
        virtual auto free() noexcept -> void;

        /**
         * @brief Function de-allocates any vulkan allocated handles ( for buffer and memory )
         *
         * @exceptsafe
         */
         auto clear () noexcept -> void override;
//        virtual auto cleanup() noexcept -> void;

        /**
         * @brief Function will copy from a given buffer a number of bytes onto this buffer
         *
         * @param sourceBuffer : engine::VBuffer cref = Constant Reference to the buffer to copy from
         * @param commandPool : engine::VCommandPool cref = Constant Reference to a command pool to create a Command Buffer for Copying from
         * @param size : VulkanDeviceSize = number of bytes to copy. Default 0, if left default, copies all memory ( smallest between given buffer, or this buffer's size )
         * @param destinationOffset : uint32 = offset of the destination buffer ( start from ... )
         * @param sourceOffset : uint32 = offset of the source buffer ( start from ... )
         *
         * @exceptsafe
         *
         * @return VulkanResult::VK_SUCCESS if copy was successful OR
         * @return VulkanResult::VK_ERROR_NOT_PERMITTED_EXT if this is not a Destination Buffer and given buffer is not a Source Buffer OR
         * @return VulkanResult::VK_ERROR_FEATURE_NOT_PRESENT if given a Command Pool with Transfer capabilities but could not acquire a Transfer Queue OR
         * @return VulkanResult returned by VCommandBufferCollection::allocate in case of error OR
         * @return VulkanResult returned by VCommandBufferCollection::startRecord in case of error OR
         * @return VulkanResult returned by VCommandBufferCollection::submit in case of error OR
         * @return VulkanResult returned by vkQueueWaitIdle in case of error
         */
        auto copyFrom (
                VBuffer const &,
                VCommandPool const &,
                VulkanDeviceSize = 0U,
                uint32 = 0U,
                uint32 = 0U
        ) noexcept -> VulkanResult;

        /**
         * @brief Function returns the Vulkan Allocated Handle for the Buffer
         *
         * @exceptsafe
         *
         * @return VulkanBuffer cref = Constant Reference to the handle
         */
        [[nodiscard]] constexpr auto data () const noexcept -> VulkanBuffer const & {
            return this->_handle;
        }

        /**
         * @brief Function returns size of allocated buffer ( in bytes )
         *
         * @exceptsafe
         *
         * @return VulkanDeviceSize = size of buffer, in bytes
         */
        [[nodiscard]] constexpr auto size () const noexcept -> VulkanDeviceSize {
            return this->_memorySize;
        }

        /**
         * @brief Function returns the buffer usage flags used
         *
         * @exceptsafe
         *
         * @return VulkanBufferUsageFlags = Flags of Buffer Usage ( Vertex | Index | ... )
         */
        [[nodiscard]] constexpr auto getBufferUsageFlags () const noexcept -> VulkanBufferUsageFlags {
            return this->_bufferUsageFlags;
        }

        /**
         * @brief Function returns the number of elements stored in the buffer of given type, if given a type
         *
         * @exceptsafe
         *
         * @return uint32 = number of stored elements, 0 if no type of buffer is specified
         */
        [[nodiscard]] constexpr auto getElementCount () const noexcept -> uint32 {
            return this->_elementCount;
        }

        /**
         * @brief Function returns the sharing mode of the Buffer Memory
         *
         * @exceptsafe
         *
         * @return VulkanSharingMode = Memory Sharing Mode ( Exclusive | Concurrent )
         */
        [[nodiscard]] constexpr auto getBufferSharingMode () const noexcept -> VulkanSharingMode {
            return this->_sharingMode;
        }

        [[nodiscard]] auto toString () const noexcept -> String override;
        [[nodiscard]] auto operator == (Object const & o) const noexcept -> bool override {
            if ( this == & o ) return true;
            auto p = dynamic_cast < decltype (this) > ( & o );
            if ( p == nullptr ) return false;

            return
                this->_handle == p->_handle &&
                this->_memoryHandle == p->_memoryHandle;
        }

        [[nodiscard]] auto hash () const noexcept -> Index override {
            return
                dataTypes::hash(reinterpret_cast<AddressValueType>(this->_handle)) * 10000 +
                dataTypes::hash(reinterpret_cast<AddressValueType>(this->_memoryHandle)) % 10000;
        }

        [[nodiscard]] auto copy () const noexcept -> VBuffer * override = 0;
    };

}


#endif //ENG1_VBUFFER_HPP
