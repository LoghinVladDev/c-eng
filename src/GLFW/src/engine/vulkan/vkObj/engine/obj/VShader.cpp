//
// Created by vladl on 10/9/2020.
//

#include "VShader.h"
#include <vkUtils/VStdUtilsDefs.h>
#include <VVertex.h>

VulkanResult engine::VShader::setup(
        const engine::VLogicalDevice    & logicalDevice,
        const engine::VShaderCompiler   & shaderCompiler,
        const std::string               & shaderTag
) noexcept {
    this->_pLogicalDevice = & logicalDevice;
    std::vector < VulkanPipelineShaderStageCreateInfo > shaderStages;
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

                shaderStages.push_back( this->_vertexShader.getShaderStageInfo() );
            } else if ( target.getType() == VShaderModule::FRAGMENT ) {
                this->_fragmentShader.setType( VShaderModule::FRAGMENT );

                ENG_RETURN_IF_NOT_SUCCESS(
                        this->_fragmentShader.setup(
                            target.getCompiledPath(),
                            logicalDevice
                        )
                )

                shaderStages.push_back( this->_fragmentShader.getShaderStageInfo() );
            }
        }
    }

    ENG_RETURN_IF_NOT_SUCCESS(
        this->_pipeline.setup(
            logicalDevice,

            shaderStages.data(),
            static_cast < uint32 > ( shaderStages.size() ),

            & bindingDescription,
            1U,

            attributeDescriptions.data(),
            static_cast < uint32 > ( attributeDescriptions.size() ),


        )
    )

    return VK_ERROR_INITIALIZATION_FAILED;
}

void engine::VShader::cleanup() noexcept {

}
