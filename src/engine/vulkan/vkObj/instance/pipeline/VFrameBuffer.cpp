//
// Created by Vlad on 19/08/2020.
//

#include "VFrameBuffer.hpp"

#include <VSwapChain.hpp>
inline static auto populateFrameBufferCreateInfo (
    VulkanFrameBufferCreateInfo * createInfo,
    engine::VRenderPass   const * pRenderPass,
    VulkanImageView       const * pAttachments,
    uint32                        attachmentCount
) noexcept -> void {
    if ( createInfo == nullptr || pRenderPass == nullptr || pAttachments == nullptr )
        return;

    * createInfo = { };

    createInfo->sType               = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    createInfo->renderPass          = pRenderPass->data();
    createInfo->attachmentCount     = attachmentCount;
    createInfo->pAttachments        = pAttachments;
    createInfo->width               = pRenderPass->getLogicalDevicePtr()->getSwapChain()->getImagesInfo().extent.width;
    createInfo->height              = pRenderPass->getLogicalDevicePtr()->getSwapChain()->getImagesInfo().extent.height;
    createInfo->layers              = 1U;
}

auto engine::VFrameBufferCollection::setup(engine::VRenderPass const * pRenderPass, engine::VDepthBuffer const * pDepthBuffer) noexcept (false) -> VulkanResult {
    if( pRenderPass == nullptr )
        throw engine::EngineVFrameBufferInvalidRenderPass();

    this->_frameBuffers.clear();
    for ( const auto & imageView : pRenderPass->getLogicalDevicePtr()->getImageViewCollection()->getImageViews() ) {
        this->_frameBuffers.emplace_back( imageView, pRenderPass );

        if ( this->_frameBuffers.back().setup( pDepthBuffer ) != VK_SUCCESS )
            throw std::runtime_error ("Frame Buffer Initialization Error");
    }

    return VulkanResult::VK_SUCCESS;
}

auto engine::VFrameBufferCollection::clear() noexcept -> void {
    for ( auto & frameBuffer : this->_frameBuffers )
        frameBuffer.clear();

    this->_frameBuffers.clear();
}

#include <array>
auto engine::VFrameBuffer::setup( const engine::VDepthBuffer * pDepthBuffer ) noexcept -> VulkanResult {
    if ( this->_pImageView == nullptr || this->_pImageView == nullptr )
        return VulkanResult::VK_ERROR_INITIALIZATION_FAILED;

    VulkanFrameBufferCreateInfo createInfo { };

    if ( pDepthBuffer != nullptr ) {
        std::array<VulkanImageView, 2> attachments = {
                this->_pImageView->data(),
                pDepthBuffer->getImageView().data()
        };

        populateFrameBufferCreateInfo(
                &createInfo,
                this->_pRenderPass,
                attachments.data(),
                static_cast < uint32 > ( attachments.size() )
        );
    } else {
        populateFrameBufferCreateInfo(
                &createInfo,
                this->_pRenderPass,
                &(this->_pImageView->data()),
                1U
        );
    }

    return vkCreateFramebuffer( this->_pRenderPass->getLogicalDevicePtr()->data(), & createInfo, nullptr, & this->_handle );
}

auto engine::VFrameBuffer::clear() noexcept -> void {
    vkDestroyFramebuffer( this->_pRenderPass->getLogicalDevicePtr()->data(), this->_handle, nullptr );
    this->_handle       = VK_NULL_HANDLE;
    this->_pImageView   = nullptr;
    this->_pRenderPass  = nullptr;
}

#include <sstream>

auto engine::VFrameBufferCollection::toString() const noexcept -> String {
    std::stringstream oss;

    oss << "VFrameBufferCollection { frameBuffers = [ ";

    for (auto const & item : this->_frameBuffers)
        oss << item.toString() << ", ";

    auto s = oss.str();
    return s.substr(s.size() - 2).append("]}");
}

auto engine::VFrameBuffer::toString () const noexcept -> String {
    std::stringstream oss;
    oss <<"VFrameBuffer { " <<
        "handle = 0x" << std::hex << reinterpret_cast < AddressValueType > (this->_handle) <<
        ", pImageView = 0x" << reinterpret_cast < AddressValueType > (this->_pImageView) <<
        ", pRenderPass = 0x" << reinterpret_cast < AddressValueType > (this->_pRenderPass) << " }";

    return oss.str();
}