//
// Created by vladl on 9/5/2020.
//

#ifndef ENG1_VINDEXBUFFER_HPP
#define ENG1_VINDEXBUFFER_HPP

#include <VRenderObject.hpp>
#include <VLogicalDevice.hpp>
#include <VVertex.hpp>
#include <VBuffer.hpp>
#include <VStagingBuffer.hpp>

namespace engine {

    /**
     * @class engine::VIndexBufferBase, inherits engine::VBuffer
     *
     * @brief Represents index buffer type, will be derived into IndexBuffer of uint16 indices and IndexBuffer of uint32 indices
     */
    class VIndexBufferBase : public VBuffer {
    protected:
        //// protected variables

        /// Command Pool to Allocate Copy To GPU from
        VCommandPool const * _pCommandPool {nullptr};

        //// protected functions

        /**
         * @brief Default Base Constructor of Abstract class
         *
         * @protected
         *
         * @exceptsafe
         */
        VIndexBufferBase () noexcept = default;

        ~VIndexBufferBase() noexcept override = default;

    public:
        //// public variables

        /// represents Index Type 16 bit ( unsigned short int )
        constexpr static VulkanIndexType TYPE_16_BIT = VulkanIndexType::VK_INDEX_TYPE_UINT16;

        /// represents Index Type 32 bit ( unsigned int )
        constexpr static VulkanIndexType TYPE_32_BIT = VulkanIndexType::VK_INDEX_TYPE_UINT32;

        //// public functions

        /**
         * @brief Abstract Function used to flush CPU data to GPU memory
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
        virtual auto flush () noexcept -> VulkanResult = 0;

        /**
         * @brief Abstract Function used to get Type of Index stored in buffer
         *
         * @exceptsafe
         *
         * @return engine::VIndexBufferBase::TYPE_16_BIT if derived class is engine::VIndexBuffer16
         * @return engine::VIndexBufferBase::TYPE_32_BIT if derived class is engine::VIndexBuffer32
         */
        [[nodiscard]] virtual auto getIndexType () const noexcept -> VulkanIndexType = 0;

        /**
         * @brief Abstract Function used to Allocate Index Buffer Memory
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
        virtual auto allocateMemory () noexcept -> VulkanResult = 0;

        /**
         * @brief Function frees buffer data
         *
         * @exceptsafe
         */
        auto free () noexcept -> void override;

        /**
         * @brief Function de-allocates Vulkan Allocated Handles
         *
         * @exceptsafe
         */
        auto clear () noexcept -> void override;

        [[nodiscard]] auto toString () const noexcept -> String override {
            return String("VIndexBufferBase { base = ").append(VBuffer::toString()).append(" }");
        }

        [[nodiscard]] auto operator == (Object const & o) const noexcept -> bool override {
            return VBuffer::operator==(o);
        }

        [[nodiscard]] auto hash () const noexcept -> Index override {
            return VBuffer::hash();
        }

        [[nodiscard]] auto copy () const noexcept -> VIndexBufferBase * override = 0;
    };

    /**
     * @class engine::VIndexBuffer16, inherits engine::VIndexBufferBase
     *
     * @brief Represents an Index Buffer using uint16 elements ( unsigned short int )
     */
    class VIndexBuffer16 : public VIndexBufferBase {
    private:
        //// private variables

        /// CPU allocated Indices, in a Staging Buffer ( CPU Writable, Source ). Will be a bridge between CPU and GPU
        VStagingBuffer < uint16 > _stagingBuffer;

        //// private functions

    public:
        //// public variables

        //// public functions

        /**
         * @brief Default Constructor
         *
         * @exceptsafe
         */
        VIndexBuffer16 () noexcept = default;

        ~VIndexBuffer16() noexcept override = default;

        /**
         * @brief Function Initialises Index Buffer with given data
         *
         * @deprecated
         *
         * @param device : engine::VLogicalDevice cref = Constant Reference to Logical Device
         * @param indices : std::vector < uint16 > cref = Constant Reference to vector of indices to load
         * @param pCommandPool : engine::VCommandPool cptr = Address to Constant Command Pool that will be used to generate a command to copy from Bridge to CPU
         * @param pQueueFamilyIndices : uint32 cptr = Address to one / an array of Queue Family Indices representing the queue families that will operate on the buffer. Used in concurrency
         * @param queueFamilyIndexCount : uint32 = Number of Queue Family indices
         * @param forceMemoryExclusivity : bool = if true, it will transfer through graphics queue, Exclusive, without command buffer and queue indices. if false, it will act concurrently, transferring through dedicated transfer queue
         *
         * @exceptsafe
         *
         * @return VulkanResult::VK_SUCCESS if initialisation was successful OR
         * @return VulkanResult::VK_ERROR_INITIALIZATION_FAILED if Concurrency Mode Chosen but not supported OR
         * @return VulkanResult returned vkCreateBuffer on error occurrence - internal vulkan function
         */
        auto setup (
            VLogicalDevice          const &,
            std::vector < uint16 >  const &,
            VCommandPool            const *,
            uint32                  const * = nullptr,
            uint32                          = 0U,
            bool                            = false
        ) noexcept -> VulkanResult;

        /**
         * @brief Function Initialises Index Buffer empty, having given capacity ( in element count )
         *
         * @param device : engine::VLogicalDevice cref = Constant Reference to Logical Device
         * @param indexCount : uint32 = Number of Indices Buffer will contain
         * @param pCommandPool : engine::VCommandPool cptr = Address to Constant Command Pool that will be used to generate a command to copy from Bridge to CPU
         * @param pQueueFamilyIndices : uint32 cptr = Address to one / an array of Queue Family Indices representing the queue families that will operate on the buffer. Used in concurrency
         * @param queueFamilyIndexCount : uint32 = Number of Queue Family indices
         * @param forceMemoryExclusivity : bool = if true, it will transfer through graphics queue, Exclusive, without command buffer and queue indices. if false, it will act concurrently, transferring through dedicated transfer queue
         *
         * @exceptsafe
         *
         * @return VulkanResult::VK_SUCCESS if initialisation was successful OR
         * @return VulkanResult::VK_ERROR_INITIALIZATION_FAILED if Concurrency Mode Chosen but not supported OR
         * @return VulkanResult returned vkCreateBuffer on error occurrence - internal vulkan function
         */
        auto setup (
           VLogicalDevice   const &,
           uint32,
           VCommandPool     const *,
           uint32           const * = nullptr,
           uint32                   = 0U,
           bool                     = false
        ) noexcept -> VulkanResult;

        /**
         * @brief Function Loads given Data onto buffer
         *
         * @param indices : std::vector < uint16 > cref = Constant Reference to a vector containing indices to load
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
        auto load ( std::vector < uint16 > const & ) noexcept -> VulkanResult;

        /**
         * @brief Getter for Buffer Contained Indices ( on CPU, not on GPU )
         *
         * @exceptsafe
         *
         * @return std::vector < uint16 > cref = Constant Reference to vector containing indices in buffer
         */
        [[nodiscard]] constexpr auto getBufferData () const noexcept -> std::vector < uint16 > const & {
            return this->_stagingBuffer._data;
        }

        /**
         * @brief Function Allocates Buffer Memory
         *
         * @exceptsafe
         *
         * @return VulkanResult::VK_SUCCESS if allocate of memory was successful OR
         * @return VulkanResult::VK_ERROR_INITIALIZATION_FAILED if memory type requested is not available OR
         * @return VulkanResult returned by vkAllocateMemory on error occurrence - internal vulkan function OR
         * @return VulkanResult returned by vkBindBufferMemory on error occurrence - internal vulkan function
         */
        auto allocateMemory() noexcept -> VulkanResult override;

        /**
         * @brief Function Flushes Staging Buffer Data to GPU Buffer
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
        auto flush() noexcept -> VulkanResult override;

        /**
         * @brief Function de-allocates any vulkan allocated handles
         *
         * @exceptsafe
         */
        auto clear() noexcept -> void override;

        /**
         * @brief Function frees Buffer Allocated Memory
         *
         * @exceptsafe
         */
        auto free() noexcept -> void override;

        /**
         * @brief Getter for Index Type contained
         *
         * @return VIndexBufferBase::TYPE_16_BIT
         */
        [[nodiscard]] constexpr auto getIndexType() const noexcept -> VulkanIndexType override {
            return VIndexBufferBase::TYPE_16_BIT;
        }

        [[nodiscard]] auto toString () const noexcept -> String override;
        [[nodiscard]] auto operator == (Object const & o) const noexcept -> bool override {
            return VIndexBufferBase::operator==(o);
        }

        [[nodiscard]] auto hash () const noexcept -> Index override {
            return VIndexBufferBase::hash();
        }

        [[nodiscard]] auto copy () const noexcept -> VIndexBuffer16 * override {
            return new VIndexBuffer16(* this);
        }
    };

    /**
     * @class engine::VIndexBuffer32, inherits engine::VIndexBufferBase
     *
     * @brief Represents an Index Buffer using uint32 elements ( unsigned int )
     */
    class VIndexBuffer32 : public VIndexBufferBase {
    private:
        //// private variables

        /// CPU allocated Indices, in a Staging Buffer ( CPU Writable, Source ). Will be a bridge between CPU and GPU
        VStagingBuffer < uint32 > _stagingBuffer;

        //// private functions

    public:
        //// public variables

        //// public functions

        /**
         * @brief Default Constructor
         *
         * @exceptsafe
         */
        VIndexBuffer32 () noexcept = default;
        ~VIndexBuffer32() noexcept override = default;

        /**
         * @brief Function Initialises Index Buffer with given data
         *
         * @deprecated
         *
         * @param device : engine::VLogicalDevice cref = Constant Reference to Logical Device
         * @param indices : std::vector < uint32 > cref = Constant Reference to vector of indices to load
         * @param pCommandPool : engine::VCommandPool cptr = Address to Constant Command Pool that will be used to generate a command to copy from Bridge to CPU
         * @param pQueueFamilyIndices : uint32 cptr = Address to one / an array of Queue Family Indices representing the queue families that will operate on the buffer. Used in concurrency
         * @param queueFamilyIndexCount : uint32 = Number of Queue Family indices
         * @param forceMemoryExclusivity : bool = if true, it will transfer through graphics queue, Exclusive, without command buffer and queue indices. if false, it will act concurrently, transferring through dedicated transfer queue
         *
         * @exceptsafe
         *
         * @return VulkanResult::VK_SUCCESS if initialisation was successful OR
         * @return VulkanResult::VK_ERROR_INITIALIZATION_FAILED if Concurrency Mode Chosen but not supported OR
         * @return VulkanResult returned vkCreateBuffer on error occurrence - internal vulkan function
         */
        auto setup (
            VLogicalDevice          const &,
            std::vector < uint32 >  const &,
            VCommandPool            const *,
            uint32                  const * = nullptr,
            uint32                          = 0U,
            bool                            = false
        ) noexcept -> VulkanResult;

        /**
         * @brief Function Initialises Index Buffer empty, having given capacity ( in element count )
         *
         * @param device : engine::VLogicalDevice cref = Constant Reference to Logical Device
         * @param indexCount : uint32 = Number of Indices Buffer will contain
         * @param pCommandPool : engine::VCommandPool cptr = Address to Constant Command Pool that will be used to generate a command to copy from Bridge to CPU
         * @param pQueueFamilyIndices : uint32 cptr = Address to one / an array of Queue Family Indices representing the queue families that will operate on the buffer. Used in concurrency
         * @param queueFamilyIndexCount : uint32 = Number of Queue Family indices
         * @param forceMemoryExclusivity : bool = if true, it will transfer through graphics queue, Exclusive, without command buffer and queue indices. if false, it will act concurrently, transferring through dedicated transfer queue
         *
         * @exceptsafe
         *
         * @return VulkanResult::VK_SUCCESS if initialisation was successful OR
         * @return VulkanResult::VK_ERROR_INITIALIZATION_FAILED if Concurrency Mode Chosen but not supported OR
         * @return VulkanResult returned vkCreateBuffer on error occurrence - internal vulkan function
         */
        auto setup (
           VLogicalDevice   const &,
           uint32,
           VCommandPool     const *,
           uint32           const * = nullptr,
           uint32                   = 0U,
           bool                     = false
        ) noexcept -> VulkanResult;

        /**
         * @brief Function Loads given Data onto buffer
         *
         * @param indices : std::vector < uint32 > cref = Constant Reference to a vector containing indices to load
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
        auto load ( std::vector < uint32 > const & ) noexcept -> VulkanResult;

        /**
         * @brief Getter for Buffer Contained Indices ( on CPU, not on GPU )
         *
         * @exceptsafe
         *
         * @return std::vector < uint32 > cref = Constant Reference to vector containing indices in buffer
         */
        [[nodiscard]] constexpr auto getBufferData () const noexcept -> std::vector < uint32 > const & {
            return this->_stagingBuffer._data;
        }

        /**
         * @brief Function Allocates Buffer Memory
         *
         * @exceptsafe
         *
         * @return VulkanResult::VK_SUCCESS if allocate of memory was successful OR
         * @return VulkanResult::VK_ERROR_INITIALIZATION_FAILED if memory type requested is not available OR
         * @return VulkanResult returned by vkAllocateMemory on error occurrence - internal vulkan function OR
         * @return VulkanResult returned by vkBindBufferMemory on error occurrence - internal vulkan function
         */
        auto allocateMemory() noexcept -> VulkanResult override;

        /**
         * @brief Function Flushes Staging Buffer Data to GPU Buffer
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
        auto flush() noexcept -> VulkanResult override;

        /**
         * @brief Function de-allocates any vulkan allocated handles
         *
         * @exceptsafe
         */
        auto clear() noexcept -> void override;

        /**
         * @brief Function frees Buffer Allocated Memory
         *
         * @exceptsafe
         */
        auto free() noexcept -> void override;

        /**
         * @brief Getter for Index Type contained
         *
         * @return VIndexBufferBase::TYPE_32_BIT
         */
        [[nodiscard]] constexpr auto getIndexType() const noexcept -> VulkanIndexType override {
            return VIndexBufferBase::TYPE_32_BIT;
        }

        [[nodiscard]] auto toString () const noexcept -> String override;
        [[nodiscard]] auto operator == (Object const & o) const noexcept -> bool override {
            return VIndexBufferBase::operator==(o);
        }

        [[nodiscard]] auto hash () const noexcept -> Index override {
            return VIndexBufferBase::hash();
        }

        [[nodiscard]] auto copy () const noexcept -> VIndexBuffer32 * override {
            return new VIndexBuffer32(* this);
        }
    };

    /// default Index Buffer is Index Buffer 16
    typedef VIndexBuffer16 VIndexBuffer;
}


#endif //ENG1_VINDEXBUFFER_HPP
