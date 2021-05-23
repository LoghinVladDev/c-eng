//
// Created by vladl on 10/10/2020.
//

#include "VMeshRenderer.hpp"
#include <vkUtils/VStdUtilsDefs.h>

const engine::VMeshRenderer engine::VMeshRenderer::EMPTY = VMeshRenderer(UINT64_MAX);

VulkanResult engine::VMeshRenderer::recreateUniformBuffers() noexcept {
    this->_MVPDescriptorBuffers.resize( this->_pLogicalDevice->getSwapChain()->getImages().size() );

    for ( auto & uniformBuffer : this->_MVPDescriptorBuffers ) {
        ENG_RETURN_IF_NOT_SUCCESS(uniformBuffer.setup(* this->_pLogicalDevice,1U))
        ENG_RETURN_IF_NOT_SUCCESS(uniformBuffer.allocateMemory())
    }

    return VulkanResult::VK_SUCCESS;
}

VulkanResult engine::VMeshRenderer::recreate() noexcept {
    ENG_RETURN_IF_NOT_SUCCESS( this->recreateUniformBuffers() )
    ENG_RETURN_IF_NOT_SUCCESS( this->recreateDescriptorSets() )

    return VulkanResult::VK_SUCCESS;
}

VulkanResult engine::VMeshRenderer::recreateDescriptorSets() noexcept {
    ENG_RETURN_IF_NOT_SUCCESS (
            this->_descriptorSets.allocate(
                    * this->_pDescriptorPool,
                    this->_pShader->getDescriptorSetLayout()
            )
    )

    auto layoutBindings = this->_pShader->getDescriptorSetLayoutBindings();
    int32 MVPBufferBinding = -1;
    int32 textureSamplerBinding = -1;

    for ( const auto & binding : layoutBindings ) {
        if ( binding.descriptorType == VulkanDescriptorType::VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER )
            MVPBufferBinding = binding.binding;

        if ( binding.descriptorType == VulkanDescriptorType::VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER )
            textureSamplerBinding = binding.binding;
    }

    this->_descriptorSets.configure(this->_MVPDescriptorBuffers, static_cast < uint32 > ( MVPBufferBinding ) );
    this->_descriptorSets.configure(this->_texture, * this->_pTextureSampler, static_cast < uint32 > ( textureSamplerBinding ) );

    return VulkanResult::VK_SUCCESS;
}

VulkanResult engine::VMeshRenderer::setup(
        const VCommandPool              & transferCommandPool,
        const VDescriptorPool           & descriptorPool,
        const VShader                   & shader,
        const std::string               & texturePath,
        const VTextureSampler           & textureSampler,
        const VQueueFamilyCollection    & queueFamilyCollection
) noexcept {
    this->_pShader          = & shader;
    this->_pDescriptorPool  = & descriptorPool;
    this->_pTextureSampler  = & textureSampler;
    this->_pCommandPool     = & transferCommandPool,
    this->_pLogicalDevice   = transferCommandPool.getLogicalDevicePtr();

    // uni buffers

    ENG_RETURN_IF_NOT_SUCCESS( this->recreateUniformBuffers() )

    // texture

    auto queueFamilyIndices = queueFamilyCollection.getQueueFamilyIndices();

    ENG_RETURN_IF_NOT_SUCCESS(
        this->_texture.setup(
            texturePath.c_str(),
            transferCommandPool,
            queueFamilyIndices.data(),
            static_cast < uint32 > ( queueFamilyIndices.size() )
        )
    )

    // desc sets

    ENG_RETURN_IF_NOT_SUCCESS( this->recreateDescriptorSets() );

    return VulkanResult::VK_SUCCESS;
}

void engine::VMeshRenderer::cleanupUniformBuffers() noexcept {
    for ( auto & buffer : this->_MVPDescriptorBuffers ) {
        buffer.free();
        buffer.cleanup();
    }
}

void engine::VMeshRenderer::cleanup() noexcept {
    this->cleanupUniformBuffers();
    this->_texture.cleanup();
}