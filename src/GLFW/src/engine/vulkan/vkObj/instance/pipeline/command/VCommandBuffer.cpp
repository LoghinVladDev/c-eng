//
// Created by Vlad on 19/08/2020.
//

#include "VCommandBuffer.h"
#include <vkUtils/VStdUtilsDefs.h>

inline static void populateCommandBufferAllocateInfo (
    VulkanCommandBufferAllocateInfo * allocateInfo,
    const engine::VCommandPool      & commandPool,
    uint32                            commandBufferCount,
    VulkanCommandBufferLevel          level
) noexcept {
    if ( allocateInfo == nullptr )
        return;

    * allocateInfo = { };

    allocateInfo->sType                 = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocateInfo->commandPool           = commandPool.data();
    allocateInfo->commandBufferCount    = commandBufferCount;
    allocateInfo->level                 = level;
}

inline static void populateCommandBufferBeginInfo (
    VulkanCommandBufferBeginInfo * beginInfo
) noexcept {
    if ( beginInfo == nullptr )
        return;

    * beginInfo = { };

    beginInfo->sType            = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo->flags            = 0U;
    beginInfo->pInheritanceInfo = nullptr;
}

inline static void populateRenderPassBeginInfo (
    VulkanRenderPassBeginInfo   * renderPassBeginInfo,
    const engine::VFrameBuffer  * frameBuffer,
    VulkanClearValue            * pClearValues,
    uint32                        clearValueCount
) noexcept {
    if ( renderPassBeginInfo == nullptr || frameBuffer == nullptr )
        return;

    * renderPassBeginInfo = { };

    renderPassBeginInfo->sType                  = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassBeginInfo->renderPass             = frameBuffer->getRenderPassPtr()->data();
    renderPassBeginInfo->framebuffer            = frameBuffer->data();
    renderPassBeginInfo->renderArea.offset      = {0, 0};
    renderPassBeginInfo->renderArea.extent      = frameBuffer->getRenderPassPtr()->getLogicalDevicePtr()->getSwapChain()->getImagesInfo().extent;

    renderPassBeginInfo->clearValueCount        = clearValueCount;
    renderPassBeginInfo->pClearValues           = pClearValues;
}

inline static void populateSubmitInfo (
    VulkanSubmitInfo                  * submitInfo,
    const VulkanPipelineStageFlags    * pWaitStages,
    const VulkanSemaphore             * pWaitSemaphores,
    uint32                              waitSemaphoreCount,
    const VulkanSemaphore             * pSignalSemaphores,
    uint32                              signalSemaphoreCount,
    const VulkanCommandBuffer         * pCommandBuffers,
    uint32                              commandBufferCount
) noexcept {
    if (
        submitInfo          == nullptr ||
        pWaitStages         == nullptr ||
        pWaitSemaphores     == nullptr ||
        pSignalSemaphores   == nullptr ||
        pCommandBuffers     == nullptr
    )
        return;

    * submitInfo = { };

    submitInfo->sType                   = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo->waitSemaphoreCount      = waitSemaphoreCount;
    submitInfo->pWaitDstStageMask       = pWaitStages;
    submitInfo->pWaitSemaphores         = pWaitSemaphores;

    submitInfo->commandBufferCount      = commandBufferCount;
    submitInfo->pCommandBuffers         = pCommandBuffers;

    submitInfo->signalSemaphoreCount    = signalSemaphoreCount;
    submitInfo->pSignalSemaphores       = pSignalSemaphores;
}

inline static void populateBeginInfoBufferCopy (
    VulkanCommandBufferBeginInfo * beginInfo
) noexcept {
    if ( beginInfo == nullptr )
        return;

    * beginInfo = VulkanCommandBufferBeginInfo {
        .sType              = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
        .pNext              = nullptr,
        .flags              = VulkanCommandBufferUsageFlagBits::VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
        .pInheritanceInfo   = nullptr
    };
}

inline static void populateBufferCopy (
    VulkanBufferCopy  * copyRegion,
    VulkanDeviceSize    sourceOffset,
    VulkanDeviceSize    destinationOffset,
    VulkanDeviceSize    size
) noexcept {
    if ( copyRegion == nullptr )
        return;

    * copyRegion = VulkanBufferCopy {
        .srcOffset  = sourceOffset,
        .dstOffset  = destinationOffset,
        .size       = size
    };
}

inline static void populateSubmitInfo (
    VulkanSubmitInfo          * submitInfo,
    const VulkanCommandBuffer * pCommandBuffers,
    uint32                      commandBufferCount
) noexcept {
    if ( submitInfo == nullptr )
        return;

    * submitInfo = {
        .sType                  = VK_STRUCTURE_TYPE_SUBMIT_INFO,
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

engine::VCommandBuffer engine::VCommandBuffer::getOneTimeUseBuffer(const VCommandPool & commandPool) noexcept {
    VulkanCommandBufferAllocateInfo allocateInfo { };
    populateCommandBufferAllocateInfo(
        & allocateInfo,
        commandPool,
        1U,
        VulkanCommandBufferLevel::VK_COMMAND_BUFFER_LEVEL_PRIMARY
    );

    VulkanCommandBuffer oneTimeUseBufferHandle = VK_NULL_HANDLE;
    if( vkAllocateCommandBuffers(
            commandPool.getLogicalDevicePtr()->data(),
            & allocateInfo,
            & oneTimeUseBufferHandle
    ) != VulkanResult::VK_SUCCESS ) {
        return VCommandBuffer( VK_NULL_HANDLE, nullptr );
    }

    return VCommandBuffer ( oneTimeUseBufferHandle, & commandPool );
}

VulkanResult engine::VCommandBuffer::beginOneTimeUse() noexcept {

    VulkanCommandBufferBeginInfo beginInfo {};
    populateCommandBufferBeginInfo( & beginInfo );

    ENG_RETURN_IF_NOT_SUCCESS_2(
        vkBeginCommandBuffer( this->_handle, & beginInfo ),
        vkFreeCommandBuffers(
                this->_pCommandPool->getLogicalDevicePtr()->data(),
                this->_pCommandPool->data(),
                1U,
                & this->_handle
        )
     )

    return VulkanResult::VK_SUCCESS;
}

VulkanResult engine::VCommandBuffer::submitOneTimeUse(const VQueue* pQueue) noexcept {
    ENG_RETURN_IF_NOT_SUCCESS_2(
        vkEndCommandBuffer( this->_handle ) ,
        vkFreeCommandBuffers(
                this->_pCommandPool->getLogicalDevicePtr()->data(),
                this->_pCommandPool->data(),
                1U,
                & this->_handle
        )
    )

    VulkanSubmitInfo submitInfo {};
    populateSubmitInfo( & submitInfo, & this->_handle, 1U );

    ENG_RETURN_IF_NOT_SUCCESS_2(
        vkQueueSubmit( pQueue->data(), 1U, & submitInfo, VK_NULL_HANDLE ),
        vkFreeCommandBuffers(
            this->_pCommandPool->getLogicalDevicePtr()->data(),
            this->_pCommandPool->data(),
            1U,
            & this->_handle
        )
    )

    ENG_RETURN_IF_NOT_SUCCESS_2(
        vkQueueWaitIdle( pQueue->data() ),
        vkFreeCommandBuffers(
                this->_pCommandPool->getLogicalDevicePtr()->data(),
                this->_pCommandPool->data(),
                1U,
                & this->_handle
        )
    )

    vkFreeCommandBuffers(
        this->_pCommandPool->getLogicalDevicePtr()->data(),
        this->_pCommandPool->data(),
        1U,
        & this->_handle
    );

    return VulkanResult::VK_SUCCESS;
}

VulkanResult engine::VCommandBufferCollection::allocate(const engine::VCommandPool & commandPool, const engine::VFrameBufferCollection & frameBufferCollection) noexcept {
    this->_pCommandPool = & commandPool;
    VulkanCommandBufferAllocateInfo allocateInfo { };
    std::vector < VulkanCommandBuffer > handles (frameBufferCollection.size());

    populateCommandBufferAllocateInfo( & allocateInfo, commandPool, handles.size(), VCommandBuffer::PRIMARY_LEVEL );

    VulkanResult allocateResult = vkAllocateCommandBuffers( commandPool.getLogicalDevicePtr()->data(), & allocateInfo, handles.data() );

    if ( allocateResult != VK_SUCCESS )
        return allocateResult;

    uint32 frameBufferIndex = 0U;

    for ( const auto & handle : handles ) {
        this->_commandBuffers.emplace_back( handle, & commandPool, & frameBufferCollection.getFrameBuffers()[frameBufferIndex++] );
    }

    return allocateResult;
}

VulkanResult engine::VCommandBufferCollection::allocate(const engine::VCommandPool & commandPool, uint32 commandBufferCount) noexcept {
    this->_pCommandPool = & commandPool;
    VulkanCommandBufferAllocateInfo allocateInfo { };
    std::vector < VulkanCommandBuffer > handles ( commandBufferCount );

    populateCommandBufferAllocateInfo( & allocateInfo, commandPool, handles.size(), VCommandBuffer::PRIMARY_LEVEL );

    VulkanResult allocateResult = vkAllocateCommandBuffers( commandPool.getLogicalDevicePtr()->data(), & allocateInfo, handles.data() );

    if ( allocateResult != VK_SUCCESS )
        return allocateResult;

    for ( const auto & handle : handles ) {
        this->_commandBuffers.emplace_back( handle, & commandPool );
    }

    return allocateResult;
}

VulkanResult engine::VCommandBuffer::startRecord(
    const engine::VPipeline & pipeline,
    const VBuffer * pVertexBuffers,
    const VulkanDeviceSize * pOffsets,
    uint32 vertexBufferCount,
    const VIndexBuffer * pIndexBuffer,
    const VulkanDescriptorSet * pDescriptorSets,
    uint32 descriptorSetCount
) noexcept {
    VulkanCommandBufferBeginInfo beginInfo { };

    populateCommandBufferBeginInfo( & beginInfo );

    VulkanResult recordResult = vkBeginCommandBuffer( this->_handle, & beginInfo );

    if ( recordResult != VulkanResult::VK_SUCCESS )
        return recordResult;

    VulkanRenderPassBeginInfo renderPassBeginInfo { };
    VulkanClearValue          clearColor          { 0.0f, 0.0f, 0.0f, 1.0f };

    populateRenderPassBeginInfo( & renderPassBeginInfo, this->_pFrameBuffer, & clearColor, 1U );

    vkCmdBeginRenderPass( this->_handle, & renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE );
    vkCmdBindPipeline   ( this->_handle, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.data() );

    uint32 vertexCount = 0U;

    if ( pVertexBuffers != nullptr ) {
        VulkanBuffer vertexBufferHandles [ vertexBufferCount ];
        for ( uint32 vertexBufferIndex = 0U; vertexBufferIndex < vertexBufferCount; vertexBufferIndex ++ ) {
            vertexBufferHandles[vertexBufferIndex] = pVertexBuffers[vertexBufferIndex].data();
            vertexCount += pVertexBuffers[ vertexBufferIndex ].getElementCount();
        }

        vkCmdBindVertexBuffers( this->_handle, 0, vertexBufferCount, vertexBufferHandles, pOffsets );

        if ( pIndexBuffer != nullptr ) {
            vkCmdBindIndexBuffer( this->_handle, pIndexBuffer->data(), 0, pIndexBuffer->getIndexType() );
        }
    }

    if ( pDescriptorSets != nullptr )
        vkCmdBindDescriptorSets( this->_handle, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.layout(), 0U, descriptorSetCount, pDescriptorSets, 0U, nullptr );

    if ( pIndexBuffer == nullptr )
        vkCmdDraw           ( this->_handle, vertexCount , 1, 0, 0 );
    else
        vkCmdDrawIndexed    ( this->_handle, pIndexBuffer->getElementCount(), 1, 0, 0, 0 );
//    vkCmdDraw           ( this->_handle, 3 , 1, 3, 0 );
    vkCmdEndRenderPass  ( this->_handle );

    return vkEndCommandBuffer( this->_handle );
}

VulkanResult engine::VCommandBuffer::startRecord(
    const VBuffer & destination,
    const VBuffer & source,
    uint32          size
) const noexcept {
    VulkanCommandBufferBeginInfo beginInfo { };
    populateBeginInfoBufferCopy( & beginInfo );

    VulkanResult beginResult = vkBeginCommandBuffer( this->_handle, & beginInfo );
    if ( beginResult != VulkanResult::VK_SUCCESS )
        return beginResult;

    VulkanBufferCopy copyRegion {};
    populateBufferCopy(
        & copyRegion,
        0ULL,
        0ULL,
        static_cast < VulkanDeviceSize > ( size )
    );

    vkCmdCopyBuffer ( this->_handle, source.data(), destination.data(), 1U, & copyRegion );

    return vkEndCommandBuffer( this->_handle );
}

VulkanResult engine::VCommandBufferCollection::startRecord(
    const engine::VPipeline & pipeline,
    const engine::VBuffer * pVertexBuffers,
    const VulkanDeviceSize * pOffsets,
    uint32 vertexBufferCount,
    const VIndexBuffer * pIndexBuffer,
    const VulkanDescriptorSet * pDescriptorSets,
    uint32 descriptorSetCount
) noexcept {
    if ( pDescriptorSets != nullptr && descriptorSetCount != static_cast < uint32 > (this->_commandBuffers.size()) )
        return VulkanResult::VK_ERROR_UNKNOWN; // todo : find something else for this

    uint32 descriptorSetIndex = 0U;

    for ( auto & commandBuffer : this->_commandBuffers ) {
        VulkanResult startRecordResult = commandBuffer.startRecord(
            pipeline,
            pVertexBuffers,
            pOffsets,
            vertexBufferCount,
            pIndexBuffer,
            pDescriptorSets + (descriptorSetIndex++),
            1U
        );
        if( startRecordResult != VulkanResult::VK_SUCCESS )
            return startRecordResult;
    }
    return VulkanResult::VK_SUCCESS;
}

VulkanResult engine::VCommandBufferCollection::startRecord(
    const VBuffer & destination,
    const VBuffer & source,
    uint32 size
) const noexcept {
    for ( const auto & commandBuffer : this->_commandBuffers ) {
        VulkanResult startRecordResult = commandBuffer.startRecord( destination, source, size );
        if ( startRecordResult != VulkanResult::VK_SUCCESS )
            return startRecordResult;
    }

    return VulkanResult::VK_SUCCESS;
}

VulkanResult engine::VCommandBuffer::submit(const VQueue * pQueue) const noexcept {
    VulkanSubmitInfo submitInfo {};

    populateSubmitInfo(
            &submitInfo,
            &this->_handle,
            1U
    );

    return vkQueueSubmit( pQueue->data(), 1U, & submitInfo, VK_NULL_HANDLE );
}

VulkanResult engine::VCommandBufferCollection::submit(const VQueue * pQueue) const noexcept {
    for ( const auto & commandBuffer : this->_commandBuffers ) {
        VulkanResult submitInfo = commandBuffer.submit( pQueue );
        if ( submitInfo != VulkanResult::VK_SUCCESS )
            return submitInfo;
    }

    return VulkanResult::VK_SUCCESS;
}

void engine::VCommandBufferCollection::free() noexcept {
    std::vector < VulkanCommandBuffer > commandBufferHandles;
    for( const auto & commandBuffer : this->_commandBuffers )
        commandBufferHandles.emplace_back( commandBuffer.data() );

    vkFreeCommandBuffers (
        this->_pCommandPool->getLogicalDevicePtr()->data(),
        this->_pCommandPool->data(),
        static_cast < uint32 > ( commandBufferHandles.size() ),
        commandBufferHandles.data()
    );

    this->_commandBuffers.clear();
    this->_pCommandPool = nullptr;
}

VulkanResult engine::VCommandBuffer::submit(
    const VulkanPipelineStageFlags * pWaitStages,
    const VSemaphore * pWaitSemaphores,
    uint32 waitSemaphoreCount,
    const VSemaphore * pSignalSemaphores,
    uint32 signalSemaphoreCount,
    const VFence * pFence
) const noexcept {
    VulkanSubmitInfo    submitInfo { };
    VulkanSemaphore     waitHandles[waitSemaphoreCount];
    VulkanSemaphore     signalHandles[signalSemaphoreCount];

    for ( uint32 i = 0; i < waitSemaphoreCount; i++ )
        waitHandles[i] = pWaitSemaphores[i].data();

    for ( uint32 i = 0; i < signalSemaphoreCount; i++ )
        signalHandles[i] = pSignalSemaphores[i].data();

    populateSubmitInfo (
        & submitInfo,
        pWaitStages,
        waitHandles,
        waitSemaphoreCount,
        signalHandles,
        signalSemaphoreCount,
        & this->_handle,
        1U
    );

    const auto * pGraphicsQueue = this->_pFrameBuffer->getRenderPassPtr()->getLogicalDevicePtr()->getFirstGraphicsQueuePtr();

    if ( pGraphicsQueue == nullptr )
        return VulkanResult::VK_ERROR_INITIALIZATION_FAILED;

    if ( pFence == nullptr )
        return vkQueueSubmit( pGraphicsQueue->data(), 1U, & submitInfo, VK_NULL_HANDLE );
    else {
        vkResetFences(
            this->_pFrameBuffer->getRenderPassPtr()->getLogicalDevicePtr()->data(),
            1U,
            & pFence->data()
        );

        return vkQueueSubmit(pGraphicsQueue->data(), 1U, &submitInfo, pFence->data());
    }
}