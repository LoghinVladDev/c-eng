//
// Created by vladl on 10/9/2020.
//

#include "VShader.hpp"
#include <vkUtils/VStdUtilsDefs.h>
#include <VVertex.hpp>

VulkanResult engine::VShader::setup(
        const engine::VLogicalDevice    & logicalDevice,
        const engine::VShaderCompiler   & shaderCompiler,
        const std::string               & shaderTag
) noexcept {
    this->_pLogicalDevice = & logicalDevice;
//    std::vector < VulkanPipelineShaderStageCreateInfo > shaderStages;
    auto bindingDescription = VVertex::getBindingDescription();
    auto attributeDescriptions = VVertex::getAttributeDescriptions();

    for ( const auto & target : shaderCompiler.getTargets() ) {
        if ( target.getTag() == shaderTag ) {
            if ( target.getType() == VShaderModule::VERTEX ) {
                this->_vertexShader.setType( VShaderModule::VERTEX );

                ENG_RETURN_IF_NOT_SUCCESS(
                        this->_vertexShader.setup(
                            target.getCompiledPath(),
                            logicalDevice
                        )
                )

                this->_shaderStages.push_back( this->_vertexShader.getShaderStageInfo() );
            } else if ( target.getType() == VShaderModule::FRAGMENT ) {
                this->_fragmentShader.setType( VShaderModule::FRAGMENT );

                ENG_RETURN_IF_NOT_SUCCESS(
                        this->_fragmentShader.setup(
                            target.getCompiledPath(),
                            logicalDevice
                        )
                )
                this->_shaderStages.push_back( this->_fragmentShader.getShaderStageInfo() );
            }

            for ( const auto & binding : target.getLayoutBindings() ) {
                this->_descriptorSetLayoutBindings.push_back( binding );
            }

        }
    }

    VulkanDescriptorSetLayoutCreateInfo descriptorSetLayoutCreateInfo {
        .sType          = VulkanStructureType::VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
        .pNext          = nullptr,
        .flags          = VULKAN_NULL_FLAGS,
        .bindingCount   = static_cast < uint32 > ( this->_descriptorSetLayoutBindings.size() ),
        .pBindings      = this->_descriptorSetLayoutBindings.data()
    };

    ENG_RETURN_IF_NOT_SUCCESS(
        vkCreateDescriptorSetLayout (
                this->_pLogicalDevice->data(),
                & descriptorSetLayoutCreateInfo,
                nullptr,
                & this->_descriptorSetLayout
        )
    )

    ENG_RETURN_IF_NOT_SUCCESS(
        this->_pipeline.setup(
            logicalDevice,

            this->_shaderStages.data(),
            static_cast < uint32 > ( this->_shaderStages.size() ),

            & bindingDescription,
            1U,

            attributeDescriptions.data(),
            static_cast < uint32 > ( attributeDescriptions.size() ),

            & this->_descriptorSetLayout,
            1U
        )
    )

    return VulkanResult::VK_SUCCESS;
}

VulkanResult engine::VShader::recreateShader() noexcept {

    auto bindingDescription = VVertex::getBindingDescription();
    auto attributeDescriptions = VVertex::getAttributeDescriptions();
    return this->_pipeline.setup(
        * this->_pLogicalDevice,

        this->_shaderStages.data(),
        static_cast < uint32 > ( this->_shaderStages.size() ),

        & bindingDescription,
        1U,

        attributeDescriptions.data(),
        static_cast < uint32 > ( attributeDescriptions.size() ),

        & this->_descriptorSetLayout,
        1U
    );
}

void engine::VShader::cleanup() noexcept {
    this->_pipeline.cleanup();

    vkDestroyDescriptorSetLayout( this->_pLogicalDevice->data(), this->_descriptorSetLayout, nullptr );

    this->_descriptorSetLayoutBindings.clear();

    this->_fragmentShader.cleanup();
    this->_vertexShader.cleanup();
    this->_shaderStages.clear();
}
