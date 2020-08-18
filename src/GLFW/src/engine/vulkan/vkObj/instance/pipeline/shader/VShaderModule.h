//
// Created by Vlad on 18/08/2020.
//

#ifndef ENG1_VSHADERMODULE_H
#define ENG1_VSHADERMODULE_H

#include <engineVulkanPreproc.h>
#include <string>
#include <vector>
#include <vkObj/instance/device/VLogicalDevice.h>
#include <vkObj/instance/pipeline/shader/VShaderCompiler.h>

namespace engine {

    class VShaderCompilerTarget;

    class EngineVShaderModuleNotInitialized : public std::exception {
    public:
        [[nodiscard]] const char * what () const noexcept override {
            return "Tried to acquire pipeline create info without valid shader module";
        }
    };

    class VShaderModule {
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
        std::vector < int8 >    _byteCode;
        VulkanShaderModule      _handle         {nullptr};
        ShaderType              _type           {ShaderType::UNDEFINED};

        const VLogicalDevice *  _pLogicalDevice {nullptr};
        //// private functions

    public:

        //// public variables

        //// public functions
        explicit VShaderModule ( const std::string& ) noexcept;
        explicit VShaderModule ( const engine::VShaderCompilerTarget& ) noexcept;

        VulkanResult setup ( const engine::VLogicalDevice & ) noexcept;
        VulkanResult setup ( const std::string&, const engine::VLogicalDevice & ) noexcept;

        void cleanup() noexcept;

        engine::VShaderModule & setType ( ShaderType type ) noexcept {
            this->_type = type;
            return *this;
        }

        VulkanPipelineShaderStageCreateInfo getShaderStageInfo () const noexcept (false);

        [[nodiscard]] static std::string shaderTypeToString ( ShaderType ) noexcept;
        [[nodiscard]] static ShaderType stringToShaderType ( const std::string & ) noexcept;
    };

}


#endif //ENG1_VSHADERMODULE_H
