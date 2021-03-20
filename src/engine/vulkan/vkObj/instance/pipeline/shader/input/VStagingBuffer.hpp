//
// Created by loghin on 9/5/20.
//

#ifndef ENG1_VSTAGINGBUFFER_HPP
#define ENG1_VSTAGINGBUFFER_HPP

#include <engineVulkanPreproc.hpp>
#include <vkDefs/types/vulkanExplicitTypes.h>
#include <vkObj/instance/device/VLogicalDevice.hpp>
#include <vkObj/instance/pipeline/shader/input/VVertex.hpp>
#include <vkObj/instance/pipeline/shader/input/VBuffer.hpp>

namespace engine {


    /**
     * @class engine::VStagingBuffer, inherits engine::VBuffer
     *
     * @brief Represents an intermediate, transfer buffer, representing CPU visible memory. Used to load data to be transferred to GPU local data
     *
     * @tparam T = Type of Data that will be stored in Buffer. Can Store multiple T Objects
     */
    template < class T >
    class VStagingBuffer : public VBuffer {
        /// give access to classes that use Staging Buffer. Redesign Pending
        friend class VVertexBuffer;
        friend class VIndexBuffer16;
        friend class VIndexBuffer32;
    private:
        //// private variables

        /// CPU stored temporary data, to be flushed on GPU memory on load
        std::vector < T > _data;

        //// private functions 

    public:
        //// public variables

        /**
         * @brief Default Constructor
         *
         * @exceptsafe
         */
        VStagingBuffer () noexcept = default;

        /**
         * @brief Function initialises Staging Buffer with given data
         *
         * @param device : engine::VLogicalDevice cref = Constant Reference to Logical Device
         * @param data : std::vector < T > cref = Constant Reference to Array to load the data from
         * @param sharingMode : VulkanSharingMode = Specify Transfer Mode of Buffer. VBuffer::TRANSFER_EXCLUSIVITY or VBuffer::TRANSFER_CONCURRENCY
         * @param pQueueFamilyIndices : uint32 cptr = Address to one / an array of Queue Family Indices. Used with TRANSFER_CONCURRENCY
         * @param queueFamilyIndexCount : uint32 = Number of queue family indices at the address above
         *
         * @exceptsafe
         *
         * @return VulkanResult::VK_SUCCESS if initialisation was successful OR
         * @return VulkanResult::VK_ERROR_INITIALIZATION_FAILED if Concurrency Mode Chosen but not supported OR
         * @return VulkanResult returned vkCreateBuffer on error occurrence - internal vulkan function
         */
        auto setup (
            VLogicalDevice      const &,
            std::vector < T >   const &,
            VulkanSharingMode           = VBuffer::TRANSFER_EXCLUSIVITY,
            uint32              const * = nullptr,
            uint32                      = 0U
        ) noexcept -> VulkanResult;

        /**
         * @brief Function initialises Staging Buffer with given number of elements. Size = number of elements * sizeof ( T )
         *
         * @param device : engine::VLogicalDevice cref = Constant Reference to Logical Device
         * @param size : uint32 = Number of elements that will exist in the buffer
         * @param sharingMode : VulkanSharingMode = Specify Transfer Mode of Buffer. VBuffer::TRANSFER_EXCLUSIVITY or VBuffer::TRANSFER_CONCURRENCY
         * @param pQueueFamilyIndices : uint32 cptr = Address to one / an array of Queue Family Indices. Used with TRANSFER_CONCURRENCY
         * @param queueFamilyIndexCount : uint32 = Number of queue family indices at the address above
         *
         * @exceptsafe
         *
         * @return VulkanResult::VK_SUCCESS if initialisation was successful OR
         * @return VulkanResult::VK_ERROR_INITIALIZATION_FAILED if Concurrency Mode Chosen but not supported OR
         * @return VulkanResult returned vkCreateBuffer on error occurrence - internal vulkan function
         */
        auto setup (
            VLogicalDevice      const &,
            uint32,
            VulkanSharingMode           = VBuffer::TRANSFER_EXCLUSIVITY,
            uint32              const * = nullptr,
            uint32                      = 0U
        ) noexcept -> VulkanResult;

        /**
         * @brief Function Allocates Buffer Memory
         *
         * @exceptsafe
         *
         * @return VulkanResult::VK_SUCCESS if allocate of memory was successful OR
         * @return VulkanResult::VK_ERROR_INITIALIZATION_FAILED if memory type requested is not available OR
         * @return VulkanResult returned by vkAllocateMemory on error occurrence - internal vulkan function OR
         * @return VulkanResult returned by vkBindBufferMemory on error occurrence - internal vulkan function OR
         * @return VulkanResult::VK_ERROR_MEMORY_MAP_FAILED if Memory was not allocated with flag MEMORY_CPU_WRITABLE OR
         * @return VulkanResult returned by vkMapMemory on error occurrence - internal vulkan function
         */
        auto allocateMemory () noexcept -> VulkanResult;

        /**
         * @brief Function Loads privately stored memory in CPU allocated variable onto GPU data visible by CPU
         *
         * @exceptsafe
         *
         * @return VulkanResult::VK_SUCCESS if reload successful OR
         * @return VulkanResult::VK_ERROR_MEMORY_MAP_FAILED if Memory was not allocated with flag MEMORY_CPU_WRITABLE OR
         * @return VulkanResult returned by vkMapMemory on error occurrence - internal vulkan function
         */
        auto reload () noexcept -> VulkanResult;

        /**
         * @brief Getter for CPU-side stored data.
         *
         * @exceptsafe
         *
         * @return std::vector < T > cref = Constant Reference to the Vector containing data of type T
         */
        [[nodiscard]] auto getBufferData () const noexcept -> std::vector < T > const &  {
            return this->_data;
        }

        /**
         * @brief Getter for CPU-side stored data.
         *
         * If updated, to update GPU memory as well, use reload()
         *
         * @exceptsafe
         *
         * @return std::vector < T > ref = Constant Reference to the Vector containing data of type T
         */
        [[nodiscard]] auto getBufferData () noexcept -> std::vector < T > & {
            return this->_data;
        }

        /**
         * @brief Function frees allocated memory on GPU
         *
         * @exceptsafe
         */
        auto free () noexcept -> void override;

        /**
         * @brief Function de-allocates any vulkan allocated handles
         *
         * @exceptsafe
         */
        auto cleanup () noexcept -> void override;

        //// public functions

    };

}

template <class T>
auto engine::VStagingBuffer<T>::free() noexcept -> void {
    return VBuffer::free();
}

template <class T>
auto engine::VStagingBuffer<T>::cleanup() noexcept -> void {
    return VBuffer::cleanup();
}

template <class T>
auto engine::VStagingBuffer<T>::allocateMemory() noexcept -> VulkanResult {
    /// staging buffer is CPU visible and writable
    VulkanResult allocateResult = VBuffer::allocateMemory( VBuffer::MEMORY_CPU_BUFFER_FLAGS );
    if ( allocateResult != VulkanResult::VK_SUCCESS )
        return allocateResult;

    /// load memory ( initialisations )
    return this->reload();
}

template <class T>
auto engine::VStagingBuffer<T>::reload() noexcept -> VulkanResult {
    return VBuffer::load(
        static_cast < const void * > ( this->_data.data() ),
        static_cast < std::size_t > ( this->_data.size() * sizeof ( T ) )
    );
}

template <class T>
auto engine::VStagingBuffer<T>::setup(
    VLogicalDevice  const & device,
    uint32                  size,
    VulkanSharingMode       sharingMode,
    uint32          const * pQueueFamilyIndices,
    uint32                  queueFamilyIndexCount
) noexcept -> VulkanResult {
    this->_data.resize ( size ); /// resize the data to hold as much as requested
    this->setElementCount( size );

    return VBuffer::setup(
        device,
        static_cast < std::size_t > ( sizeof ( T ) * size ),
        VBuffer::STAGING_BUFFER_CPU_LOCAL, /// STAGING_BUFFER = TRANSFER_SOURCE
        sharingMode,
        pQueueFamilyIndices,
        queueFamilyIndexCount
    );
}

template <class T>
auto engine::VStagingBuffer<T>::setup(
    VLogicalDevice      const & device,
    std::vector<T>      const & data,
    VulkanSharingMode           sharingMode,
    uint32              const * pQueueFamilyIndices,
    uint32                      queueFamilyIndexCount
) noexcept -> VulkanResult {
    this->_data = data;
    this->setElementCount( static_cast<uint32>(data.size()) );

    return VBuffer::setup(
        device,
        static_cast < std::size_t > ( sizeof ( T ) * data.size() ),
        VBuffer::STAGING_BUFFER_CPU_LOCAL,
        sharingMode,
        pQueueFamilyIndices,
        queueFamilyIndexCount
    );
}


#endif //ENG1_VSTAGINGBUFFER_HPP
