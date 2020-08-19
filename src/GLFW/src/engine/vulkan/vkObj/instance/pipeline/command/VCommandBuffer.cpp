//
// Created by Vlad on 19/08/2020.
//

#include "VCommandBuffer.h"

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


VulkanResult engine::VCommandBufferCollection::allocate(const engine::VCommandPool & commandPool, const engine::VFrameBufferCollection & frameBufferCollection) {
    VulkanCommandBufferAllocateInfo allocateInfo { };
    std::vector < VulkanCommandBuffer > handles (frameBufferCollection.size());

    populateCommandBufferAllocateInfo( & allocateInfo, commandPool, handles.size(), VCommandBuffer::PRIMARY_LEVEL );

    VulkanResult allocateResult = vkAllocateCommandBuffers( commandPool.getLogicalDevicePtr()->data(), & allocateInfo, handles.data() );

    if ( allocateResult != VK_SUCCESS )
        return allocateResult;

    uint32 frameBufferIndex = 0U;
    for ( const auto & handle : handles ) {
        this->_commandBuffers.emplace_back( handle, & frameBufferCollection.getFrameBuffers()[frameBufferIndex++] );
    }

    return allocateResult;
}

VulkanResult engine::VCommandBuffer::startRecord( const engine::VPipeline & pipeline ) noexcept {
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
    vkCmdDraw           ( this->_handle, 3, 1, 0, 0 );
    vkCmdEndRenderPass  ( this->_handle );

    return vkEndCommandBuffer( this->_handle );
}

VulkanResult engine::VCommandBufferCollection::startRecord( const engine::VPipeline & pipeline ) noexcept {
    for ( auto & commandBuffer : this->_commandBuffers ) {
        VulkanResult startRecordResult = commandBuffer.startRecord(pipeline);
        if( startRecordResult != VulkanResult::VK_SUCCESS )
            return startRecordResult;
    }
    return VulkanResult::VK_SUCCESS;
}
