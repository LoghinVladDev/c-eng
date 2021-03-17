//
// Created by Vlad on 19/08/2020.
//

#ifndef ENG1_VCOMMANDBUFFER_H
#define ENG1_VCOMMANDBUFFER_H

#include <engineVulkanPreproc.h>
#include <vulkanExplicitTypes.h>
#include "VCommandPool.h"
#include <VFrameBuffer.h>
#include <VPipeline.h>
#include <VSemaphore.h>
#include <VFence.h>
#include <VVertex.h>
#include <VVertexBuffer.h>
#include <VIndexBuffer.h>

namespace engine {

    /**
     * @class engine::VCommandBuffer
     *
     * @brief Represents A Command given to the GPU, usually Draw Commands
     *
     * Commands are done on a Pipeline ( Shader - Vertex + Fragment ), and take as input
     *      - vertices
     *      - indices of vertices
     *
     *      And output result to Frame Buffers
     *
     * Command Buffers can also be used on other aspects, such as data transfer
     */
    class VCommandBuffer {
    private:

        /// Give access to engine::VCommandBufferCollection to private members
        friend class VCommandBufferCollection;

        //// private variables

        /// Command Buffer Vulkan Handle
        VulkanCommandBuffer     _handle         {nullptr};

        /// Frame Buffer to Operate On
        VFrameBuffer    const * _pFrameBuffer   {nullptr};

        /// Command Pool from which the Command Buffer allocates
        VCommandPool    const * _pCommandPool   {nullptr};

        //// private functions

    public:
        //// public variables

        /// PRIMARY_LEVEL = buffer to image drawing
        constexpr static VulkanCommandBufferLevel                  PRIMARY_LEVEL     = VulkanCommandBufferLevel::VK_COMMAND_BUFFER_LEVEL_PRIMARY;

        /// SECONDARY_LEVEL = buffer to primary buffer drawing ( queueing commands ) - composite drawing
        [[maybe_unused]] constexpr static VulkanCommandBufferLevel SECONDARY_LEVEL   = VulkanCommandBufferLevel::VK_COMMAND_BUFFER_LEVEL_SECONDARY;

        //// public functions

        /**
         * @brief Default Constructor
         *
         * @exceptsafe
         */
        VCommandBuffer() noexcept = delete;

        /**
         * @brief Constructor from Buffer Handle, Pool and Frame Buffer to draw on
         *
         * @param handle : VulkanCommandBuffer cref = Constant Reference to a Command Buffer Handle
         * @param pCommandPool : engine::VCommandPool cptr = Address to a Constant Command Pool
         * @param pFrameBuffer : engine::VFrameBuffer cptr = Address to a Constant Frame Buffer
         *
         * @exceptsafe
         */
        explicit VCommandBuffer (
                VulkanCommandBuffer const & handle,
                VCommandPool        const * pCommandPool = nullptr,
                VFrameBuffer        const * pFrameBuffer = nullptr
        ) noexcept :
            _handle ( handle ),
            _pFrameBuffer ( pFrameBuffer ),
            _pCommandPool ( pCommandPool ){

        }

        /**
         * @brief Function returns a One-Time use Command Buffer, unpopulated, allocated from a Pool
         *
         * @param commandPool : engine::VCommandPool cref = Constant Reference to a Command Pool to Allocate From
         *
         * @static
         *
         * @exceptsafe
         *
         * @return VCommandBuffer = newly created, one time use Command Buffer
         */
        [[nodiscard]] static auto getOneTimeUseBuffer ( VCommandPool const & ) noexcept -> VCommandBuffer;

        /**
         * @brief Function used on a one-time use Command Buffer. Starts Recording of commands onto buffer
         *
         * In case of an error, the Command Buffer is freed
         *
         * @exceptsafe
         *
         * @return VulkanResult =
         *      VulkanResult::VK_SUCCESS if Command Buffer was started successfully OR
         *      VulkanResult different from VK_SUCCESS returned by vkBeginCommandBuffer - vulkan internal function
         */
        [[nodiscard]] auto beginOneTimeUse() noexcept -> VulkanResult;

        /**
         * @brief Function used to end a one-time use Command Buffer's recording and submit it to be processed by the Vulkan API
         *
         * Function also will de-allocate the buffer if submit was a success
         * In case of an error, the Command Buffer is freed
         *
         * @param pQueue : engine::VQueue cptr = Address to a Queue to submit the Command Buffer to
         *
         * @exceptsafe
         *
         * @return VulkanResult =
         *      VulkanResult::VK_SUCCESS if Command Buffer was recorded and submitted successfully OR
         *      VulkanResult different from VK_SUCCESS returned by vkEndCommandBuffer - internal vulkan function OR
         *      VulkanResult different from VK_SUCCESS returned by vkQueueSubmit - internal vulkan function
         *      VulkanResult different from VK_SUCCESS returned by vkQueueWaitIdle - internal vulkan function
         */
        [[nodiscard]] auto submitOneTimeUse( VQueue const * ) noexcept -> VulkanResult;

        /**
         * @brief Function used to submit a Command Buffer Recorded with Draw Information
         *
         * @param pWaitStages : VulkanPipelineStageFlags cptr = address to one / an array of pipeline stage signals to wait for before submission (i.e. COLOR_ATTACHMENT_BIT flag - fragment shader finish ). Will be used if semaphores are not used
         * @param pWaitSemaphores : engine::VSemaphore cptr = address to one / an array of Semaphores to wait to be signalled before submission. Will be used if wait stages are not used
         * @param waitSemaphoreCount : uint32 = Number of Semaphore addresses in the array above. Number of semaphores to wait for
         * @param pSignalSemaphores : engine::VSemaphore cptr = address to one / an array of Semaphores to be signalled upon completion of submitted command
         * @param signalSemaphoreCount : uint32 = Number of Semaphore addresses in the array above. Number of semaphores to signal
         * @param pFence : engine::VFence cptr = Address of a Fence to reset as to signal start of command upon submission. Can be nullptr
         *
         * @exceptsafe
         *
         * @return VulkanResult =
         *      VulkanResult::VK_SUCCESS if Command Buffer was submitted successfully OR
         *      VulkanResult::VK_ERROR_INITIALISATION_FAILED if no Graphics Queue was found on Logical Device OR
         *      VulkanResult returned by vkQueueSubmit - internal Vulkan function
         */
        [[nodiscard]] auto submit (
            VulkanPipelineStageFlags const *,
            VSemaphore               const *,
            uint32,
            VSemaphore               const *,
            uint32,
            VFence                   const * = nullptr
        ) const noexcept -> VulkanResult;

        /**
         * @brief function used to submit Command Buffer as soon as possible onto a Queue
         *
         * @param pQueue : engine::VQueue cptr = Address of a Queue to submit in
         *
         * @exceptsafe
         *
         * @return VulkanResult = value returned by vkQueueSubmit - internal Vulkan function
         */
        [[nodiscard]] auto submit ( VQueue const * ) const noexcept -> VulkanResult ;

        /**
         * @brief function used to start the recording of a Command Buffer for the Draw Command
         *
         * @param pipeline : engine::VPipeline cref = the Pipeline to record the command on. Contains the shader program that will use the input data. The shader program will run once for each object, for each VertexBuffer, IndexBuffer, Descriptor Set attached
         * @param pVertexBuffers : engine::VVertexBuffer cptr = Address of one / an array of VertexBuffers containing input vertex data. One Vertex Buffer contains vertices of one object
         * @param pIndexBuffers : engine::VIndexBuffer cptr = Address of one / an array of IndexBuffers containing the order in which Vertex Buffers' vertices have to be drawn. They have to be directly associated with Vertex Buffers ( i.e. IndexBuffer[i] corresponds to VertexBuffer[i] )
         * @param pDescriptorSets : VulkanDescriptorSet cptr = Address of one / an array of VulkanDescriptorSets containing handles for descriptor sets, representing the CPU-GPU bindings of the shared data - Uniform Buffers, Textures
         * @param objectCount : uint32 = Number of times the shader program inside the pipeline has to run = Number of Vertex Buffers = Number of Index Buffers = Number of Descriptor Sets = Number of drawn Objects
         * @param pOffsets : VulkanDeviceSize cptr = Address of one / an array of Offsets of differently laid out objects inside buffers. I.e. two objects' data residing in the same VertexBuffer, IndexBuffer and Descriptor Set. Used in composite objects
         * @param offsetCount = uint32 = Number of offsets at the address passed above.
         *
         * @exceptsafe
         *
         * @return VulkanResult =
         *      VulkanResult::VK_SUCCESS if Command Buffer was recorded successfully OR
         *      VulkanResult returned by vkBeginCommandBuffer in case of error - internal Vulkan function OR
         *      VulkanResult returned by vkEndCommandBuffer in case of error - internal Vulkan function
         */
        [[nodiscard]] auto startRecord (
            VPipeline           const &,
            VVertexBuffer       const * = nullptr,
            VIndexBuffer        const * = nullptr,
            VulkanDescriptorSet const * = nullptr,
            uint32                      = 0U,
            VulkanDeviceSize    const * = nullptr,
            uint32                      = 0U
        ) noexcept -> VulkanResult;

        /**
         * @brief function used to start the recording of a Command Buffer used for copying / transferring data from one Data Buffer to another
         *
         * Copies size bytes from source Data Buffer to destination Data Buffer upon activation from a submitted queue
         *
         * @param destination : engine::VBuffer cref = Constant Reference to a Destination Data Buffer.
         * @param source : engine::VBuffer cref = Constant Reference to a Source Data Buffer
         * @param size : uint32 = Number of bytes to copy from source to destination
         * @param destinationOffset : uint32 = Offset for the Destination Buffer ( number of bytes to skip from beginning )
         * @param sourceOffset : uint32 = Offset for the Source Buffer ( number of bytes to skip from beginning )
         *
         * @exceptsafe
         *
         * @return VulkanResult =
         *      VulkanResult::VK_SUCCESS if recording of Command Buffer was Successful OR
         *      VulkanResult returned by vkBeginCommandBuffer in case of error - vulkan internal function OR
         *      VulkanResult returned by vkEndCommandBuffer in case of error - vulkan internal function
         */
        [[nodiscard]] auto startRecord (
            VBuffer const &,
            VBuffer const &,
            uint32,
            uint32 = 0llu,
            uint32 = 0llu
        ) const noexcept -> VulkanResult;

        /**
         * @brief Getter for Internal Handle allocated by Vulkan for Command Buffer
         *
         * @exceptsafe
         *
         * @return VulkanCommandBuffer cref = Constant Reference to Vulkan Allocated Handle
         */
        [[nodiscard]] const VulkanCommandBuffer & data () const noexcept {
            return this->_handle;
        }
    };

    /**
     * @class engine::VCommandBufferCollection
     *
     * @brief Represents a collection of Command Buffers, generally used in Drawing as they contain one framebuffer for each command buffer
     */
    class VCommandBufferCollection {
    private:
        //// private variables

        /// vector of Command Buffers in collection
        std::vector < VCommandBuffer > _commandBuffers;

        /// command pool to initialise Buffers from
        const VCommandPool           * _pCommandPool    {nullptr};

        //// private functions

    public:
        //// public variables

        //// public functions

        /**
         * @brief Default Constructor
         *
         * @exceptsafe
         */
        VCommandBufferCollection() noexcept = default;

        /**
         * @brief Function used to allocate several command buffers from a pool, with assignation of Frame Buffers
         *
         * Allocates a number of Command Buffers equivalent to number of passed Frame Buffers
         *
         * @param commandPool : engine::VCommandPool cref = Constant Reference to Command Pool to allocate from
         * @param frameBufferCollection : engine::VFrameBufferCollection cref = Constant Reference to Frame Buffer Collection to assign Frame Buffers to Command Buffers from
         *
         * @exceptsafe
         *
         * @return VulkanResult =
         *      VulkanResult::VK_SUCCESS if allocation was successful OR
         *      VulkanResult returned by vkAllocateCommandBuffers if error occurred - internal vulkan function
         */
        [[nodiscard]] auto allocate ( engine::VCommandPool const &, engine::VFrameBufferCollection const & ) noexcept -> VulkanResult;

        /**
         * @brief Function used to allocate explicit count of command buffers from a Command Pool
         *
         * @param commandPool : engine::VCommandPool cref = Constant Reference to Command Pool to allocate from
         * @param commandBufferCount : uint32 = Number of Command Buffers to allocate
         *
         * @exceptsafe
         *
         * @return VulkanResult =
         *      VulkanResult::VK_SUCCESS if allocation was successful OR
         *      VulkanResult returned by vkAllocateCommandBuffers if error occurred - internal vulkan function
         */
        [[nodiscard]] auto allocate ( engine::VCommandPool const &, uint32 ) noexcept -> VulkanResult;

        /**
         * @brief function records draw command to each Command Buffer in Collection with given parameters for each
         *
         * @param pipeline : engine::VPipeline cref = the Pipeline to record the command on. Contains the shader program that will use the input data. The shader program will run once for each object, for each VertexBuffer, IndexBuffer, Descriptor Set attached
         * @param pVertexBuffers : engine::VVertexBuffer cptr = Address of one / an array of VertexBuffers containing input vertex data. One Vertex Buffer contains vertices of one object
         * @param pIndexBuffers : engine::VIndexBuffer cptr = Address of one / an array of IndexBuffers containing the order in which Vertex Buffers' vertices have to be drawn. They have to be directly associated with Vertex Buffers ( i.e. IndexBuffer[i] corresponds to VertexBuffer[i] )
         * @param objectCount : uint32 = Number of times the shader program inside the pipeline has to run = Number of Vertex Buffers = Number of Index Buffers = Number of Descriptor Sets = Number of drawn Objects
         * @param pOffsets : VulkanDeviceSize cptr = Address of one / an array of Offsets of differently laid out objects inside buffers. I.e. two objects' data residing in the same VertexBuffer, IndexBuffer and Descriptor Set. Used in composite objects
         * @param offsetCount = uint32 = Number of offsets at the address passed above.
         * @param ppDescriptorSets : VulkanDescriptorSet cptr cptr = Address to an array of one / an array of Vulkan Descriptor Sets, one for each Command Buffer. Binds Uniform Buffers associated with each Command Buffer so that frames can be pre-calculated
         * @param descriptorSetCount : uint32 = Number of Descriptor Sets Arrays. Should be same as Command Buffer count / Frame Buffer Count, as each image should have their own Uniform/Texture bindings
         *
         * @exceptsafe
         *
         * @return VulkanResult =
         *      VulkanResult::VK_SUCCESS if each Command Buffer was recorded successfully OR
         *      VulkanResult returned by vkBeginCommandBuffer in case of error - internal Vulkan function OR
         *      VulkanResult returned by vkEndCommandBuffer in case of error - internal Vulkan function
         */
        [[nodiscard]] auto startRecord (
                VPipeline                   const &,
                VVertexBuffer               const * = nullptr,
                VIndexBuffer                const * = nullptr,
                uint32                              = 0U,
                VulkanDeviceSize            const * = nullptr,
                uint32                              = 0U,
                VulkanDescriptorSet const * const * = nullptr,
                uint32                              = 0U
        ) noexcept -> VulkanResult;

        /**
         * @brief function used to start the recording of all Command Buffers in Collection used for copying / transferring data from one Data Buffer to another
         *
         * Copies size bytes from source Data Buffer to destination Data Buffer upon activation from a submitted queue
         *
         * @param destination : engine::VBuffer cref = Constant Reference to a Destination Data Buffer.
         * @param source : engine::VBuffer cref = Constant Reference to a Source Data Buffer
         * @param size : uint32 = Number of bytes to copy from source to destination
         * @param destinationOffset : uint32 = Offset for the Destination Buffer ( number of bytes to skip from beginning )
         * @param sourceOffset : uint32 = Offset for the Source Buffer ( number of bytes to skip from beginning )
         *
         * @exceptsafe
         *
         * Reminder : Redesign function to accommodate multiple copies in parallel
         *
         * @return VulkanResult =
         *      VulkanResult::VK_SUCCESS if recording of Command Buffer was Successful OR
         *      VulkanResult returned by vkBeginCommandBuffer in case of error - vulkan internal function OR
         *      VulkanResult returned by vkEndCommandBuffer in case of error - vulkan internal function
         */
        [[nodiscard]] auto startRecord (
            VBuffer const &,
            VBuffer const &,
            uint32,
            uint32 = 0llu,
            uint32 = 0llu
        ) const noexcept -> VulkanResult;

        /**
         * @brief Function submits all Command Buffers in Collection onto a queue
         *
         * @param pQueue : engine::VQueue cptr = Address to a Constant Queue to submit Command Buffers in
         *
         * @exceptsafe
         *
         * @return VulkanResult =
         *      VulkanResult::VK_SUCCESS if Command Buffer was submitted successfully OR
         *      VulkanResult returned by vkQueueSubmit - internal Vulkan function
         */
        auto submit ( VQueue const * ) const noexcept -> VulkanResult;

        /**
         * @brief Getter function for Command Buffers vector
         *
         * @exceptsafe
         *
         * @return std::vector < engine::VCommandBuffer > cref = Constant Reference to vector of Command Buffers
         */
        [[nodiscard]] auto getCommandBuffers () const noexcept -> std::vector < VCommandBuffer > const & {
            return this->_commandBuffers;
        }

        /**
         * @brief Function frees all allocated Command Buffers
         *
         * @exceptsafe
         */
        auto free () noexcept -> void;
    };

}


#endif //ENG1_VCOMMANDBUFFER_H
