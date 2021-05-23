//
// Created by Vlad on 18/08/2020.
//

#ifndef ENG1_VSHADERMODULE_HPP
#define ENG1_VSHADERMODULE_HPP

#include <VRenderObject.hpp>
#include <string>
#include <vector>
#include <VLogicalDevice.hpp>

namespace engine {

    class VShaderCompilerTarget;

    class EngineVShaderModuleNotInitialized : public std::exception {
    public:
        [[nodiscard]] auto what () const noexcept -> StringLiteral override {
            return "Tried to acquire pipeline create info without valid shader module";
        }
    };


    class VShaderModule : public VRenderObject {
    public:
        typedef enum {
            VERTEX,
            TESSELATION,
            GEOMETRY,
            FRAGMENT,

            UNDEFINED
        } ShaderType;
    private:
        //// private variables
        std::vector < sint8 >   _byteCode;
        VulkanShaderModule      _handle         {nullptr};
        ShaderType              _type           {ShaderType::UNDEFINED};

        VLogicalDevice  const * _pLogicalDevice {nullptr};
        //// private functions

    public:

        //// public variables

        //// public functions
        VShaderModule () noexcept = default;
        explicit VShaderModule ( const std::string& ) noexcept;
        explicit VShaderModule ( const engine::VShaderCompilerTarget& ) noexcept;
        ~VShaderModule() noexcept override = default;

        auto setup ( engine::VLogicalDevice const & ) noexcept -> VulkanResult;
        auto setup ( std::string const &, engine::VLogicalDevice const & ) noexcept -> VulkanResult;

        auto clear() noexcept -> void override;

        engine::VShaderModule & setType ( ShaderType type ) noexcept {
            this->_type = type;
            return *this;
        }

        [[nodiscard]] VulkanPipelineShaderStageCreateInfo getShaderStageInfo () const noexcept (false);

        [[nodiscard]] static std::string shaderTypeToString ( ShaderType ) noexcept;
        [[nodiscard]] static ShaderType stringToShaderType ( const std::string & ) noexcept;
    };

}


#endif //ENG1_VSHADERMODULE_HPP
