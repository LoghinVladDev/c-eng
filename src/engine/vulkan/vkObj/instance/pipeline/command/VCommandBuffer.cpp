//
// Created by Vlad on 19/08/2020.
//

#include "VCommandBuffer.hpp"
#include <vkUtils/VStdUtilsDefs.h>

/**
 * @brief internal function used to populate Command Buffer Allocation Info Structure
 *
 * @param allocateInfo : VulkanCommandBufferAllocateInfo ptr = Address to the Structure to populate
 * @param commandPool : engine::VCommandPool cref = Constant Reference to the Command Pool to allocate from
 * @param commandBufferCount : uint32 = Number of Command Buffers to allocate
 * @param level : VulkanCommandBufferLevel = Level to allocate Command Buffers with - PRIMARY = buffer to frame buffer, SECONDARY = buffer to primary buffer
 *
 * @exceptsafe
 */
inline static auto populateCommandBufferAllocateInfo (
    VulkanCommandBufferAllocateInfo * allocateInfo,
    engine::VCommandPool      const & commandPool,
    uint32                            commandBufferCount,
    VulkanCommandBufferLevel          level
) noexcept -> void {
    if ( allocateInfo == nullptr )
        return;

    * allocateInfo = {
        .sType                 = VulkanStructureType::VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
        .pNext                 = nullptr, /// no associated structure linked
        .commandPool           = commandPool.data(),
        .level                 = level,
        .commandBufferCount    = commandBufferCount
    };
}

/**
 * @brief internal function used to populate Command Buffer Begin Info Structure
 *
 * @param beginInfo : VulkanCommandBufferBeginInfo ptr = Address to Structure to populate
 *
 * @exceptsafe
 */
inline static auto populateCommandBufferBeginInfo (
    VulkanCommandBufferBeginInfo * beginInfo
) noexcept -> void {
    if ( beginInfo == nullptr )
        return;

    * beginInfo = {
        .sType            = VulkanStructureType::VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
        .pNext            = nullptr, /// no associated structure linked
        .flags            = 0U,     /// no special flags
        .pInheritanceInfo = nullptr /// does not inherit any Secondary Command Buffer Data
    };
}

/**
 * @brief internal function used to populate Render Pass Begin Info
 *
 * @param renderPassBeginInfo : VulkanRenderPassBeginInfo ptr = Address to the Structure to populate
 * @param frameBuffer : engine::VFrameBuffer cptr = Address to the Frame Buffer used in Render Pass
 * @param pClearValues : VulkanClearValue ptr = Address to one / array of Clear Value Structures, used in clearing Frame Buffer before start of render pass
 * @param clearValueCount : uint32 = Number of Clear Value Structures attached
 *
 * @exceptsafe
 */
inline static auto populateRenderPassBeginInfo (
    VulkanRenderPassBeginInfo   * renderPassBeginInfo,
    engine::VFrameBuffer  const * frameBuffer,
    VulkanClearValue            * pClearValues,
    uint32                        clearValueCount
) noexcept -> void {
    if ( renderPassBeginInfo == nullptr || frameBuffer == nullptr )
        return;

    * renderPassBeginInfo = {
        .sType              = VulkanStructureType::VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
        .pNext              = nullptr,
        .renderPass         = frameBuffer->getRenderPassPtr()->data(),
        .framebuffer        = frameBuffer->data(),
        .renderArea         = {
            .offset             = { /// no offset on render area
                .x                  = 0,
                .y                  = 0
            }, /// extent is determined by swap chian image info
            .extent             = frameBuffer->getRenderPassPtr()->getLogicalDevicePtr()->getSwapChain()->getImagesInfo().extent,
        },
        .clearValueCount    = clearValueCount,
        .pClearValues       = pClearValues,
    };
}

/**
 * @brief internal function used to populate Submit Info structure
 *
 * @param submitInfo : VulkanSubmitInfo ptr = Address to Structure to populate
 * @param pWaitStages : VulkanPipelineStageFlags cptr = Address to one / array of Pipeline Stage Flags. Command will not start until flags have been signaled by pipeline
 * @param pWaitSemaphores : VulkanSemaphore cptr = Address to one / array of Semaphore Handles. Command will not start until all Semaphores have been signaled
 * @param waitSemaphoreCount : uint32 = Number of Semaphores to wait for before start of Command.
 * @param pSignalSemaphores : VulkanSemaphore cptr = Address to one / array of Semaphore Handles. Submit will signal all Semaphores with given handles once Command Has Finished
 * @param signalSemaphoreCount : uint32 = Number of Semaphores to signal once Command has finished
 * @param pCommandBuffers : VulkanCommandBuffer cptr = Address to one / array of Command Buffer Handles. These Handles will be sumbitted
 * @param commandBufferCount : uint32 = Number of Command Buffers submitted
 *
 * @exceptsafe
 */
inline static auto populateSubmitInfo (
    VulkanSubmitInfo                  * submitInfo,
    VulkanPipelineStageFlags    const * pWaitStages,
    VulkanSemaphore             const * pWaitSemaphores,
    uint32                              waitSemaphoreCount,
    VulkanSemaphore             const * pSignalSemaphores,
    uint32                              signalSemaphoreCount,
    VulkanCommandBuffer         const * pCommandBuffers,
    uint32                              commandBufferCount
) noexcept -> void {
    if (
        submitInfo          == nullptr ||
        pCommandBuffers     == nullptr
    )
        return;

    * submitInfo = {
        .sType                  = VulkanStructureType::VK_STRUCTURE_TYPE_SUBMIT_INFO,
        .pNext                  = nullptr,
        .waitSemaphoreCount     = waitSemaphoreCount,
        .pWaitSemaphores        = pWaitSemaphores,
        .pWaitDstStageMask      = pWaitStages,
        .commandBufferCount     = commandBufferCount,
        .pCommandBuffers        = pCommandBuffers,
        .signalSemaphoreCount   = signalSemaphoreCount,
        .pSignalSemaphores      = pSignalSemaphores
    };
}

/**
 * @brief internal function used to populate Begin Info Structure for Copy Command Buffers
 *
 * @param beginInfo : VulkanCommandBufferBeginInfo ptr = Address of the Structure to be populated
 *
 * @exceptsafe
 */
inline static auto populateBeginInfoBufferCopy (
    VulkanCommandBufferBeginInfo * beginInfo
) noexcept -> void {
    if ( beginInfo == nullptr )
        return;

    * beginInfo = VulkanCommandBufferBeginInfo {
        .sType              = VulkanStructureType::VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
        .pNext              = nullptr,
        .flags              = VulkanCommandBufferUsageFlagBits::VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT, /// specify that buffer is used once
        .pInheritanceInfo   = nullptr
    };
}

/**
 * @brief internal function used to populate Buffer Copy Region Structure
 *
 * @param copyRegion : VulkanBufferCopy ptr = Address of the Structure to populate
 * @param sourceOffset : uint32 = offset of the source buffer ( in bytes, from start of buffer )
 * @param destinationOffset : uint32 = offset of the destination buffer ( in bytes, from start of buffer )
 * @param size : uint32 = no. of bytes to copy
 *
 * @exceptsafe
 */
inline static auto populateBufferCopy (
    VulkanBufferCopy  * copyRegion,
    VulkanDeviceSize    sourceOffset,
    VulkanDeviceSize    destinationOffset,
    VulkanDeviceSize    size
) noexcept -> void {
    if ( copyRegion == nullptr )
        return;

    * copyRegion = VulkanBufferCopy {
        .srcOffset  = sourceOffset,
        .dstOffset  = destinationOffset,
        .size       = size
    };
}

/**
 * @brief internal function used to populate Submit Info Structure
 *
 * @param submitInfo : VulkanSubmitInfo ptr = Address to the Structure to populate
 * @param pCommandBuffers : VulkanCommandBuffer cptr = Address to one / an array of Buffer Handles to submit
 * @param commandBufferCount : uint32 = number of Command Buffer Handles to submit
 *
 * @exceptsafe
 */
inline static auto populateSubmitInfo (
    VulkanSubmitInfo          * submitInfo,
    VulkanCommandBuffer const * pCommandBuffers,
    uint32                      commandBufferCount
) noexcept -> void {
    if ( submitInfo == nullptr )
        return;

    * submitInfo = {
        .sType                  = VulkanStructureType::VK_STRUCTURE_TYPE_SUBMIT_INFO,
        .pNext                  = nullptr,
        .waitSemaphoreCount     = 0,
        .pWaitSemaphores        = nullptr,
        .pWaitDstStageMask      = nullptr,
        .commandBufferCount     = commandBufferCount,
        .pCommandBuffers        = pCommandBuffers,
        .signalSemaphoreCount   = 0,
        .pSignalSemaphores      = nullptr
    };
}

auto engine::VCommandBuffer::getOneTimeUseBuffer(
        VCommandPool const & commandPool
) noexcept -> VCommandBuffer {
    VulkanCommandBufferAllocateInfo allocateInfo { };

    populateCommandBufferAllocateInfo(
        & allocateInfo, // allocate a single command buffer from pool
        commandPool,
        1U,
        VulkanCommandBufferLevel::VK_COMMAND_BUFFER_LEVEL_PRIMARY
    );

    VulkanCommandBuffer oneTimeUseBufferHandle = VK_NULL_HANDLE;
    if( vkAllocateCommandBuffers(
            commandPool.getLogicalDevicePtr()->data(), /// on this Logical Device
            & allocateInfo, /// with parameters
            & oneTimeUseBufferHandle /// save in this handle
    ) != VulkanResult::VK_SUCCESS ) {
        return VCommandBuffer( VK_NULL_HANDLE, nullptr ); /// construct invalid object
    }

    return VCommandBuffer ( oneTimeUseBufferHandle, & commandPool ); /// construct object
}

auto engine::VCommandBuffer::beginOneTimeUse() noexcept -> VulkanResult {
    VulkanCommandBufferBeginInfo beginInfo {};
    populateCommandBufferBeginInfo( & beginInfo );

    ENG_RETURN_IF_NOT_SUCCESS_2(
        vkBeginCommandBuffer( this->_handle, & beginInfo ), /// if begin fails
        vkFreeCommandBuffers( /// free buffer
                this->_pCommandPool->getLogicalDevicePtr()->data(),
                this->_pCommandPool->data(),
                1U,
                & this->_handle
        )
     )

    return VulkanResult::VK_SUCCESS;
}

auto engine::VCommandBuffer::submitOneTimeUse( VQueue const * pQueue ) noexcept -> VulkanResult {
    auto freeCommandBuffers = [this] () { /// use lambda for avoidance of code repeats
        vkFreeCommandBuffers(
            this->_pCommandPool->getLogicalDevicePtr()->data(),
            this->_pCommandPool->data(),
            1U,
            & this->_handle
        );
    };

    ENG_RETURN_IF_NOT_SUCCESS_2(
            vkEndCommandBuffer( this->_handle ) ,
            freeCommandBuffers()
    )

    VulkanSubmitInfo submitInfo {};
    populateSubmitInfo( & submitInfo, & this->_handle, 1U );

    ENG_RETURN_IF_NOT_SUCCESS_2(
        vkQueueSubmit(
                pQueue->data(),
                1U,
                & submitInfo,
                VK_NULL_HANDLE
        ),
        freeCommandBuffers()
    )

    ENG_RETURN_IF_NOT_SUCCESS_2( /// wait for queue to finish submission
        vkQueueWaitIdle( pQueue->data() ),
        freeCommandBuffers()
    )

    freeCommandBuffers();

    return VulkanResult::VK_SUCCESS;
}

auto engine::VCommandBufferCollection::allocate(
        engine::VCommandPool const & commandPool,
        engine::VFrameBufferCollection const & frameBufferCollection
) noexcept -> VulkanResult {
    this->_pCommandPool = & commandPool;
    VulkanCommandBufferAllocateInfo allocateInfo { };
    std::vector < VulkanCommandBuffer > handles (frameBufferCollection.size()); /// structure to hold handles

    populateCommandBufferAllocateInfo(
            & allocateInfo,
            commandPool,
            static_cast<uint32>(handles.size()),
            VCommandBuffer::PRIMARY_LEVEL /// allocate on primary level as they go to frame buffers
    );

    VulkanResult allocateResult = vkAllocateCommandBuffers(
            commandPool.getLogicalDevicePtr()->data(),  /// on this Logical Device
            & allocateInfo, /// with these Allocation parameters
            handles.data() /// save handles here
    );

    if ( allocateResult != VK_SUCCESS )
        return allocateResult;

    uint32 frameBufferIndex = 0U;

    for ( const auto & handle : handles ) {
        this->_commandBuffers.emplace_back(  /// construct Command Buffer in place
                handle,  /// with handle
                & commandPool, /// with parent pool
                & frameBufferCollection.getFrameBuffers()[frameBufferIndex++] /// acquire framebuffer and move to the next
        );
    }

    return allocateResult;
}

auto engine::VCommandBufferCollection::allocate(
        engine::VCommandPool const & commandPool,
        uint32 commandBufferCount
) noexcept -> VulkanResult {
    this->_pCommandPool = & commandPool;
    VulkanCommandBufferAllocateInfo allocateInfo { };
    std::vector < VulkanCommandBuffer > handles ( commandBufferCount );

    populateCommandBufferAllocateInfo(
            & allocateInfo,
            commandPool,
            static_cast<uint32>(handles.size()),
            VCommandBuffer::PRIMARY_LEVEL
    );

    VulkanResult allocateResult = vkAllocateCommandBuffers(
            commandPool.getLogicalDevicePtr()->data(),
            & allocateInfo,
            handles.data()
    );

    if ( allocateResult != VK_SUCCESS )
        return allocateResult;

    for ( const auto & handle : handles ) {
        this->_commandBuffers.emplace_back( handle, & commandPool ); /// construct in place, without frame buffer
    }

    return allocateResult;
}

auto engine::VCommandBuffer::startRecord(
        engine::VPipeline       const & pipeline,
        engine::VVertexBuffer   const * pVertexBuffers,
        engine::VIndexBuffer    const * pIndexBuffers,
        VulkanDescriptorSet     const * pDescriptorSets,
        uint32                          objectCount,
        VulkanDeviceSize        const * pOffsets,
        uint32                          offsetCount
) noexcept -> VulkanResult {
    VulkanCommandBufferBeginInfo beginInfo { };

    populateCommandBufferBeginInfo( & beginInfo );

    VulkanResult recordResult = vkBeginCommandBuffer( this->_handle, & beginInfo ); /// start recording of draw command

    if ( recordResult != VulkanResult::VK_SUCCESS )
        return recordResult;

    VulkanRenderPassBeginInfo renderPassBeginInfo { }; /// populate render pass, first clear the buffers
    std::array < VulkanClearValue, 2 > clearValues {};
    clearValues[0].color        = { 0.0f, 0.0f, 0.0f, 1.0f }; /// clear all colors
    clearValues[1].depthStencil = { 1.0f, 0 }; /// clear depth testing object ( DepthBuffer )

    populateRenderPassBeginInfo(
            & renderPassBeginInfo, /// this parameter
            this->_pFrameBuffer, /// for this frame
            clearValues.data(), /// with these clear values
            static_cast < uint32 > ( clearValues.size() )
    );

    /// start render pass, CONTENTS_INLINE = no secondary command buffers
    vkCmdBeginRenderPass( this->_handle, & renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE );

    /// bind given pipeline to send input data to. Bind on GRAPHICS computation - vertex shader - fragment shader
    vkCmdBindPipeline   ( this->_handle, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.data() );

    for ( uint32 objectIndex = 0; objectIndex < objectCount; objectIndex ++ ) {
        /// if vertex buffers are to be bound, bind and send vertex buffers
        if ( pVertexBuffers != nullptr )
            vkCmdBindVertexBuffers(
                    this->_handle,
                    0,  /// from what element to start
                    1U, /// how many bindings for object
                    & pVertexBuffers[ objectIndex ].data(), /// binding address
                    pOffsets /// offsets for multiple bindings
            );

        /// if index buffers are to be bound, bind and send index buffers
        if ( pIndexBuffers != nullptr )
            vkCmdBindIndexBuffer(
                    this->_handle,
                    pIndexBuffers[ objectIndex ].data(), /// array of indices
                    0, /// offset of indices
                    pIndexBuffers[ objectIndex ].getIndexType() /// implementation data type ( uint16 by default )
            );


        /// if descriptor sets are to be bound, bind and send descriptor sets
        if ( pDescriptorSets != nullptr ) {
            vkCmdBindDescriptorSets(
                    this->_handle,
                    VulkanPipelineBindPoint::VK_PIPELINE_BIND_POINT_GRAPHICS, /// bind CPU-GPU memory on graphics compute ( vertex shading )
                    pipeline.layout(), /// acquire binding layout
                    0U, /// first set located at index ...
                    1U, /// how many sets for this object
                    pDescriptorSets + objectIndex, /// address of descriptor set
                    0U, /// dynamic offsets, unused for now
                    nullptr
            );
        }

        if ( pIndexBuffers == nullptr ) /// if no indexed drawing is used
            vkCmdDraw(
                    this->_handle,
                    pVertexBuffers[ objectIndex ].getElementCount(), /// draw number of vertices
                    1,  /// one drawing instance
                    0,  /// start of vertex
                    0  /// start of first instance
            );
        else
            vkCmdDrawIndexed(
                    this->_handle,
                    pIndexBuffers[ objectIndex ].getElementCount(), /// draw by indices
                    1, /// one drawing instance
                    0, /// offset of index array
                    0, /// offset of vertex array
                    0 /// start of first instance
            );

        /**
         * Regarding vkCmdDraw and vkCmdDrawIndexed - instanceCount and firstInstance parameters
         * Drawing can be done in multiple instances, split for each object for example.
         *
         * Number of instances can be specified, and instances can be skipped ( or biased ) by using first instance
         */
    }

    /// once all objects' draw commands are recorded, end render pass
    vkCmdEndRenderPass  ( this->_handle );

    /// end command buffer record as well
    return vkEndCommandBuffer( this->_handle );
}

auto engine::VCommandBuffer::startRecord(
        VBuffer const & destination,
        VBuffer const & source,
        uint32          size,
        uint32          destinationOffset,
        uint32          sourceOffset
) const noexcept -> VulkanResult {
    VulkanCommandBufferBeginInfo beginInfo { };
    populateBeginInfoBufferCopy( & beginInfo ); /// populate copy information

    VulkanResult beginResult = vkBeginCommandBuffer( this->_handle, & beginInfo ); /// start recording
    if ( beginResult != VulkanResult::VK_SUCCESS )
        return beginResult;

    VulkanBufferCopy copyRegion {}; /// populate copy region
    populateBufferCopy(
        & copyRegion,
        sourceOffset, /// from offset
        destinationOffset, /// to offset
        static_cast < VulkanDeviceSize > ( size )
    );

    vkCmdCopyBuffer (
            this->_handle,
            source.data(), /// from
            destination.data(), /// to
            1U,  /// number of regions TODO : expand on maybe multiple ranges?
            & copyRegion /// region
    );

    return vkEndCommandBuffer( this->_handle ); /// end command buffer recording
}

auto engine::VCommandBufferCollection::startRecord(
        engine::VPipeline           const & pipeline,
        engine::VVertexBuffer       const * pVertexBuffers,
        engine::VIndexBuffer        const * pIndexBuffers,
        uint32                              objectCount,
        VulkanDeviceSize            const * pOffsets,
        uint32                              offsetCount,
        VulkanDescriptorSet const * const * ppDescriptorSets,
        uint32                              descriptorSetCount
) noexcept -> VulkanResult {
    uint32 descriptorSetIndex = 0U;

    for ( auto & commandBuffer : this->_commandBuffers ) {
        VulkanResult startRecordResult = commandBuffer.startRecord ( /// record for each Command Buffer in Collection
                pipeline, /// pass pipeline
                pVertexBuffers, /// pass vertex buffers
                pIndexBuffers,  /// pass index buffers
                ppDescriptorSets [ descriptorSetIndex++ ], /// pass descriptor sets associated to the object. pass and move to the next descriptor sets
                objectCount, /// number of objects drawn by buffer
                pOffsets, /// pass offsets
                offsetCount /// pass offset count
        );

        if( startRecordResult != VulkanResult::VK_SUCCESS ) /// if any fail, return
            return startRecordResult;
    }
    return VulkanResult::VK_SUCCESS;
}

auto engine::VCommandBufferCollection::startRecord(
        const VBuffer & destination,
        const VBuffer & source,
        uint32 size,
        uint32 destinationOffset,
        uint32 sourceOffset
) const noexcept -> VulkanResult {
    for ( const auto & commandBuffer : this->_commandBuffers ) {
        VulkanResult startRecordResult = commandBuffer.startRecord( /// for each copy command buffer, record copy information
                destination,  /// pass destination buffer
                source,       /// pass source buffer
                size,         /// pass size
                destinationOffset, /// pass offsets
                sourceOffset
        );

        if ( startRecordResult != VulkanResult::VK_SUCCESS ) /// if any fail, return failure
            return startRecordResult;
    }

    return VulkanResult::VK_SUCCESS;
}

auto engine::VCommandBuffer::submit( VQueue const * pQueue ) const noexcept -> VulkanResult {
    VulkanSubmitInfo submitInfo {};

    populateSubmitInfo(
            &submitInfo,
            &this->_handle,
            1U
    ); /// populate submit info

    /// submit to queue
    return vkQueueSubmit( pQueue->data(), 1U, & submitInfo, VK_NULL_HANDLE );
}

auto engine::VCommandBufferCollection::submit( VQueue const * pQueue ) const noexcept -> VulkanResult {
    for ( const auto & commandBuffer : this->_commandBuffers ) { /// for each buffer
        VulkanResult submitInfo = commandBuffer.submit( pQueue ); /// submit to queue
        if ( submitInfo != VulkanResult::VK_SUCCESS )
            return submitInfo;
    }

    return VulkanResult::VK_SUCCESS;
}

void engine::VCommandBufferCollection::free() noexcept {
    std::vector < VulkanCommandBuffer > commandBufferHandles;
    for( const auto & commandBuffer : this->_commandBuffers )
        commandBufferHandles.emplace_back( commandBuffer.data() );

    vkFreeCommandBuffers ( /// free all buffer handles
        this->_pCommandPool->getLogicalDevicePtr()->data(),
        this->_pCommandPool->data(), /// from command pool
        static_cast < uint32 > ( commandBufferHandles.size() ),
        commandBufferHandles.data()
    );

    this->_commandBuffers.clear();
    this->_pCommandPool = nullptr;
}

auto engine::VCommandBuffer::submit(
    VulkanPipelineStageFlags const * pWaitStages,
    VSemaphore               const * pWaitSemaphores,
    uint32                           waitSemaphoreCount,
    VSemaphore               const * pSignalSemaphores,
    uint32                           signalSemaphoreCount,
    VFence                   const * pFence
) const noexcept -> VulkanResult {
    VulkanSubmitInfo    submitInfo { };

#if !defined(_MSC_VER)
    VulkanSemaphore     waitHandles[waitSemaphoreCount];
    VulkanSemaphore     signalHandles[signalSemaphoreCount];
#else
    /// MSVC requires no stack-allocated arrays of variardic size
    auto                waitHandles = new VulkanSemaphore [ waitSemaphoreCount ];
    auto                signalHandles = new VulkanSemaphore [ signalSemaphoreCount ];
#endif

    /// gather handles for semaphores
    for ( uint32 i = 0; i < waitSemaphoreCount; i++ )
        waitHandles[i] = pWaitSemaphores[i].data();

    for ( uint32 i = 0; i < signalSemaphoreCount; i++ )
        signalHandles[i] = pSignalSemaphores[i].data();

    populateSubmitInfo (
        & submitInfo,
        pWaitStages,            /// wait until stages end
        waitSemaphoreCount == 0 ? nullptr : waitHandles, /// wait until semaphores triggered
        waitSemaphoreCount,
        signalSemaphoreCount == 0 ? nullptr : signalHandles, /// signal semaphores when finished
        signalSemaphoreCount,
        & this->_handle, /// pass this buffer's address as an "array of 1 element"
        1U  /// only one buffer
    );

    /// submit of draw needs to be done on graphics queue
    const auto * pGraphicsQueue = this->_pFrameBuffer->getRenderPassPtr()->getLogicalDevicePtr()->getFirstGraphicsQueuePtr();

    VulkanResult result;

    if ( pGraphicsQueue == nullptr ) /// if no graphics queue, return failure
        result = VulkanResult::VK_ERROR_INITIALIZATION_FAILED;
    else {
        if (pFence == nullptr) { /// if no fence is used
            result = vkQueueSubmit( /// submit directly
                    pGraphicsQueue->data(),
                    1U, /// one submit info
                    &submitInfo,
                    VK_NULL_HANDLE /// no fence
            );
        }

        else {
            vkResetFences( /// reset the fence so that it gets signaled once command is done
                this->_pFrameBuffer->getRenderPassPtr()->getLogicalDevicePtr()->data(),
                1U,
                & pFence->data()
            );

            result = vkQueueSubmit(
                    pGraphicsQueue->data(),
                    1U,
                    &submitInfo,
                    pFence->data() /// pass fence to be signalled once draw is finished
            );
        }
    }

#if defined(_MSC_VER)
    delete[] waitHandles;
    delete[] signalHandles;
#endif

    return result;
}

#include <sstream>

auto engine::VCommandBuffer::toString() const noexcept -> String {
    std::stringstream oss;
    oss << "VCommandBuffer " <<
        "{ handle = 0x" << std::hex << reinterpret_cast<AddressValueType>(this->_handle) <<
        ", pCommandPool = 0x" << reinterpret_cast<AddressValueType>(this->_pCommandPool) <<
        ", pFrameBuffer = 0x" << reinterpret_cast<AddressValueType>(this->_pFrameBuffer);

    return oss.str();
}

auto engine::VCommandBufferCollection::toString() const noexcept -> String {
    std::stringstream oss;
    oss << "VCommandBufferCollection " <<
        "{ pCommandPool = 0x" << std::hex << reinterpret_cast<AddressValueType>(this->_pCommandPool) <<
        ", buffers = [ ";

    for (auto const & item : this->_commandBuffers)
        oss << item.toString() << ", ";

    auto s = oss.str();
    return s.substr(s.size() - 2).append(" ]}");
}