//
// Created by Vlad on 18/08/2020.
//

#include "VShaderModule.hpp"
#include "VShaderModuleDefs.h"
#include <fstream>
#include <vkObj/instance/pipeline/shader/VShaderCompiler.hpp>

static std::vector < int8 > readFile ( const std::string& fileName ) noexcept (false) {
    std::ifstream file ( fileName, std::ios::ate | std::ios::binary );

    if ( ! file.is_open() )
        throw std::runtime_error ( "binary file read error" );

    std::size_t fileSize = ( std::size_t ) file.tellg();
    std::vector < int8 > buffer ( fileSize );

    file.seekg (0);
    file.read( reinterpret_cast<char *> (buffer.data()), fileSize );

    file.close();

    return buffer;
}

static inline void populateShaderModuleCreateInfo (
    VulkanShaderModuleCreateInfo * createInfo,
    const uint32* pCode,
    uint32 codeSize
) noexcept {
    if ( createInfo == nullptr )
        return;

    * createInfo = {};

    createInfo->sType       = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo->codeSize    = codeSize;
    createInfo->pCode       = pCode;
}

VulkanResult engine::VShaderModule::setup( const engine::VLogicalDevice & device ) noexcept {
    if ( this->_byteCode.empty() ||  this->_type == engine::VShaderModule::UNDEFINED )
        return VulkanResult::VK_ERROR_INITIALIZATION_FAILED;

    this->_pLogicalDevice = ( & device );

    VulkanShaderModuleCreateInfo createInfo {};

    populateShaderModuleCreateInfo(
            & createInfo,
            reinterpret_cast < const uint32 * > (this->_byteCode.data()),
            static_cast<uint32>(this->_byteCode.size())
    );

    return vkCreateShaderModule ( this->_pLogicalDevice->data(), & createInfo, nullptr, & this->_handle );
}

engine::VShaderModule::VShaderModule(const std::string & path) noexcept {
    try{
        this->_byteCode = readFile ( path );
    } catch ( std::exception const & exception ) {
        this->_byteCode.clear();
        std::cout << "Caught exception upon reading shader bytecode : " << exception.what() << '\n';
    }
}

engine::VShaderModule::VShaderModule(const engine::VShaderCompilerTarget & target) noexcept {
    try {
        this->_byteCode = readFile ( target.getCompiledPath() );
        this->_type     = target.getType();
    } catch ( std::exception const & exception ) {
        this->_byteCode.clear();
        this->_type     = engine::VShaderModule::UNDEFINED;
        std::cout << "Caught exception upon reading shader bytecode : " << exception.what() << '\n';
    }
}

VulkanResult engine::VShaderModule::setup(const std::string & path, const engine::VLogicalDevice& device ) noexcept {
    try{
        this->_byteCode = readFile ( path );
        return this->setup( device );
    } catch ( std::exception const & exception ) {
        this->_byteCode.clear();
        std::cout << "Caught exception upon reading shader bytecode : " << exception.what() << '\n';
    }

    return VulkanResult::VK_ERROR_INITIALIZATION_FAILED;
}

void engine::VShaderModule::cleanup() noexcept {
    if ( this->_handle == nullptr )
        return;

    vkDestroyShaderModule( this->_pLogicalDevice->data(), this->_handle, nullptr );

}

std::string engine::VShaderModule::shaderTypeToString(engine::VShaderModule::ShaderType type) noexcept {
    switch ( type ) {

        case VERTEX         : return std::string ( ENGINE_VULKAN_SHADER_CONFIG_SHADER_TYPE_VERTEX );
        case TESSELATION    : return std::string ( ENGINE_VULKAN_SHADER_CONFIG_SHADER_TYPE_TESSELATION );
        case GEOMETRY       : return std::string ( ENGINE_VULKAN_SHADER_CONFIG_SHADER_TYPE_GEOMETRY );
        case FRAGMENT       : return std::string ( ENGINE_VULKAN_SHADER_CONFIG_SHADER_TYPE_FRAGMENT );

        case UNDEFINED:
        default:

            return  std::string ( ENGINE_VULKAN_SHADER_CONFIG_SHADER_TYPE_UNDEFINED );
    }
}

engine::VShaderModule::ShaderType engine::VShaderModule::stringToShaderType(const std::string & literal) noexcept {
    if ( std::strcmp ( literal.c_str(), ENGINE_VULKAN_SHADER_CONFIG_SHADER_TYPE_VERTEX ) == 0 )
        return engine::VShaderModule::ShaderType::VERTEX;
    else if ( std::strcmp ( literal.c_str(), ENGINE_VULKAN_SHADER_CONFIG_SHADER_TYPE_GEOMETRY ) == 0 )
        return engine::VShaderModule::ShaderType::GEOMETRY;
    else if ( std::strcmp ( literal.c_str(), ENGINE_VULKAN_SHADER_CONFIG_SHADER_TYPE_TESSELATION ) == 0 )
        return engine::VShaderModule::ShaderType::TESSELATION;
    else if ( std::strcmp ( literal.c_str(), ENGINE_VULKAN_SHADER_CONFIG_SHADER_TYPE_FRAGMENT ) == 0 )
        return engine::VShaderModule::ShaderType::FRAGMENT;
    else {
        return engine::VShaderModule::ShaderType::UNDEFINED;
    }
}

inline VulkanShaderStageFlagBits shaderTypeToShaderStageFlagBits ( engine::VShaderModule::ShaderType type ) noexcept {
    switch ( type ) {
        case engine::VShaderModule::VERTEX:         return VulkanShaderStageFlagBits::VK_SHADER_STAGE_VERTEX_BIT;
//        case engine::VShaderModule::TESSELATION:    return VulkanShaderStageFlagBits::VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT;
        case engine::VShaderModule::GEOMETRY:       return VulkanShaderStageFlagBits::VK_SHADER_STAGE_GEOMETRY_BIT;
        case engine::VShaderModule::FRAGMENT:       return VkShaderStageFlagBits::VK_SHADER_STAGE_FRAGMENT_BIT;
        case engine::VShaderModule::UNDEFINED:
        default:                                    return VulkanShaderStageFlagBits :: VK_SHADER_STAGE_FLAG_BITS_MAX_ENUM;
    }
}

VulkanPipelineShaderStageCreateInfo engine::VShaderModule::getShaderStageInfo() const noexcept (false) {
    VkPipelineShaderStageCreateInfo pipelineCreateInfo {};

    if ( this->_byteCode.empty() || this->_type == engine::VShaderModule::UNDEFINED || this->_handle == nullptr )
        throw engine::EngineVShaderModuleNotInitialized();

    pipelineCreateInfo.sType    = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    pipelineCreateInfo.stage    = shaderTypeToShaderStageFlagBits ( this->_type );
    pipelineCreateInfo.module   = this->_handle;
    pipelineCreateInfo.pName    = "main";

    return pipelineCreateInfo;
}
