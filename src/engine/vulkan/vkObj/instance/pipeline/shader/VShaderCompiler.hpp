//
// Created by Vlad on 17/08/2020.
//

#ifndef ENG1_VSHADERCOMPILER_HPP
#define ENG1_VSHADERCOMPILER_HPP

#include <engineVulkanPreproc.hpp>
#include <engineDataPaths.h>
#include <vkDefs/vkPlatformDefs.h>
#include <vector>
#include <CDS/JSON>
#include <vkObj/instance/pipeline/shader/VShaderModule.hpp>

namespace engine {

    class VShaderCompiler;

    class VShaderCompilerTarget {
        friend class VShaderCompiler;
    private:
        std::string                         _path;
        std::string                         _targetName;
        std::string                         _outputPath;
        std::string                         _tag;

        engine::VShaderModule::ShaderType   _shaderType { engine::VShaderModule::UNDEFINED };

        const VShaderCompiler * _pCompiler {nullptr};

        void setDefaultTargetName () noexcept {
            if( this->_path.find('/') != std::string::npos )
                this->_targetName = this->_path.substr( this->_path.find_last_of('/'), this->_path.find_last_of('.') ).append(".spv");
            else
                this->_targetName = this->_path.substr( 0, this->_path.find_last_of('.') ).append(".spv");
        }
    public:
        VShaderCompilerTarget() noexcept = default;

        explicit VShaderCompilerTarget ( std::string path ) noexcept (false) : _path(std::move(path)) {
            this->setDefaultTargetName();
        }

        VShaderCompilerTarget & setPath ( std::string path ) noexcept (false) {
            this->_path = std::move ( path );

            if( this->_targetName.empty() )
                this->setDefaultTargetName();

            return *this;
        }

        VShaderCompilerTarget & setTargetName ( std::string name ) noexcept (false) {
            this->_targetName = std::move ( name ).append(".spv");
            return *this;
        }

        VShaderCompilerTarget & setTag ( std::string tag ) noexcept (false) {
            this->_tag = std::move ( tag );
            return *this;
        }

        [[nodiscard]] engine::VShaderModule::ShaderType getType () const noexcept {
            return this->_shaderType;
        }

        [[nodiscard]] const std::string & getTag() const noexcept {
            return this->_tag;
        }

//        VShaderCompilerTarget & setCompiler ( VShaderCompiler & compiler, bool = false) noexcept;

        [[nodiscard]] const std::string& getCompiledPath () const noexcept {
            return this->_outputPath;
        }

        [[nodiscard]] std::vector < VulkanDescriptorSetLayoutBinding > getLayoutBindings() const noexcept;

        [[nodiscard]] const std::string& getRelativePath () const noexcept {
            return this->_path;
        }

        void compile () noexcept;
    };

    class VShaderCompiler {
    private:
        //// private variables
        std::string                             _outputDirectoryPath;
        std::string                             _inputDirectoryPath;
        std::vector < VShaderCompilerTarget >   _targets;

        //// private functions

    public:
        //// public variables

        //// public functions
        VShaderCompiler () noexcept (false);
        explicit VShaderCompiler ( const std::string &, const std::string& = "" ) noexcept ( false );

        VShaderCompiler & addTarget     ( VShaderCompilerTarget & );
        VShaderCompiler & addTarget     ( std::string& );
        VShaderCompiler & addTargets    ( std::vector < VShaderCompilerTarget > & );
        VShaderCompiler & addTargets    ( std::vector < std::string > & );

        VShaderCompiler & setConfigurationFile ( const JSON& );
        VShaderCompiler & setConfigurationFileJSON ( const std::string& );

        [[nodiscard]] const std::string & getOutputDirectoryPath () const noexcept {
            return this->_outputDirectoryPath;
        }

        [[nodiscard]] const std::string & getInputDirectoryPath () const noexcept {
            return this->_inputDirectoryPath;
        }

        [[nodiscard]] const std::vector < VShaderCompilerTarget > & getTargets () const noexcept {
            return this->_targets;
        }

        void build () noexcept;
    };

}


#endif //ENG1_VSHADERCOMPILER_HPP
