//
// Created by Vlad on 17/08/2020.
//

#ifndef ENG1_VSHADERCOMPILER_HPP
#define ENG1_VSHADERCOMPILER_HPP

#include <VObject.hpp>
#include <vkDefs/vkPlatformDefs.h>
#include <vector>
#include <CDS/JSON>
#include <VShaderModule.hpp>

namespace engine {

    class VShaderCompiler;

    class VShaderCompilerTarget : public VObject {
        friend class VShaderCompiler;
    private:
        std::string                         _path;
        std::string                         _targetName;
        std::string                         _outputPath;
        std::string                         _tag;

        engine::VShaderModule::ShaderType   _shaderType { engine::VShaderModule::UNDEFINED };

        VShaderCompiler      const mutable * _pCompiler {nullptr};

        auto setDefaultTargetName () noexcept -> void {
            if( this->_path.find('/') != std::string::npos )
                this->_targetName = this->_path.substr( this->_path.find_last_of('/'), this->_path.find_last_of('.') ).append(".spv");
            else
                this->_targetName = this->_path.substr( 0, this->_path.find_last_of('.') ).append(".spv");
        }
    public:
        VShaderCompilerTarget() noexcept = default;

        explicit VShaderCompilerTarget ( std::string path ) noexcept (false) : VObject(), _path(std::move(path)) {
            this->setDefaultTargetName();
        }

        ~VShaderCompilerTarget() noexcept override = default;

        auto setPath ( std::string path ) noexcept (false) -> VShaderCompilerTarget & {
            this->_path = std::move ( path );

            if( this->_targetName.empty() )
                this->setDefaultTargetName();

            return *this;
        }

        auto setTargetName ( std::string name ) noexcept (false) -> VShaderCompilerTarget & {
            this->_targetName = std::move ( name ).append(".spv");
            return *this;
        }

        auto setTag ( std::string tag ) noexcept (false) -> VShaderCompilerTarget & {
            this->_tag = std::move ( tag );
            return *this;
        }

        [[nodiscard]] constexpr auto getType () const noexcept -> engine::VShaderModule::ShaderType {
            return this->_shaderType;
        }

        [[nodiscard]] constexpr auto getTag() const noexcept -> std::string const & {
            return this->_tag;
        }

        [[nodiscard]] constexpr auto getCompiledPath () const noexcept -> std::string const & {
            return this->_outputPath;
        }

        [[nodiscard]] auto getLayoutBindings() const noexcept -> std::vector < VulkanDescriptorSetLayoutBinding >;

        [[nodiscard]] constexpr auto getRelativePath () const noexcept -> std::string const & {
            return this->_path;
        }

        auto compile () noexcept -> void;

        [[nodiscard]] auto toString() const noexcept -> String override;

        [[nodiscard]] auto operator == (VShaderCompilerTarget const & o) const noexcept -> bool {
            if ( this == & o ) return true;

            return this->_tag == o._tag && this->_shaderType == o._shaderType;
        }

        [[nodiscard]] auto equals (Object const & o) const noexcept -> bool override {
            if ( this == & o ) return true;
            auto p = dynamic_cast < decltype (this) > (& o);
            if ( p == nullptr ) return false;
            return this->operator==(*p);
        }

        [[nodiscard]] auto hash () const noexcept -> Index override {
            return String(this->_tag).hash() + dataTypes::hash(static_cast<uint32>(this->_shaderType)) * 64;
        }

        [[nodiscard]] auto copy () const noexcept -> VShaderCompilerTarget * override {
            return new VShaderCompilerTarget(*this);
        }
    };

    class VShaderCompiler : public VObject {
    private:
        //// private variables
        std::string                             _outputDirectoryPath;
        std::string                             _inputDirectoryPath;
        std::vector < VShaderCompilerTarget >   _targets;

        //// private functions

    public:
        //// public variables

        //// public functions
        VShaderCompiler () noexcept;
        explicit VShaderCompiler ( std::string const &, std::string const & = "" ) noexcept;

        ~VShaderCompiler() noexcept override = default;

        auto addTarget ( VShaderCompilerTarget const & ) noexcept -> VShaderCompiler & ;
        auto addTarget ( std::string const & ) noexcept -> VShaderCompiler & ;
        auto addTargets ( std::vector < VShaderCompilerTarget > const & ) noexcept -> VShaderCompiler & ;
        auto addTargets ( std::vector < std::string > const & ) noexcept -> VShaderCompiler & ;

        auto setConfigurationFile ( JSON const & ) noexcept -> VShaderCompiler &;
        auto setConfigurationFileJSON ( std::string const & ) noexcept -> VShaderCompiler &;

        [[nodiscard]] constexpr auto getOutputDirectoryPath () const noexcept -> std::string const & {
            return this->_outputDirectoryPath;
        }

        [[nodiscard]] constexpr auto getInputDirectoryPath () const noexcept -> std::string const & {
            return this->_inputDirectoryPath;
        }

        [[nodiscard]] constexpr auto getTargets () const noexcept -> std::vector < VShaderCompilerTarget > const & {
            return this->_targets;
        }

        auto build () noexcept -> void;

        [[nodiscard]] auto toString () const noexcept -> String override;

        [[nodiscard]] auto operator == (VShaderCompiler const & o) const noexcept -> bool {
            if ( this == & o ) return true;

            return this->_inputDirectoryPath == o._inputDirectoryPath && this->_outputDirectoryPath == o._outputDirectoryPath && this->_targets == o._targets;
        }

        [[nodiscard]] auto equals (Object const & o) const noexcept -> bool override {
            if ( this == & o ) return true;
            auto p = dynamic_cast < decltype(this) > ( & o );
            if ( p == nullptr ) return false;

            return this->operator==(*p);
        }

        [[nodiscard]] auto hash () const noexcept -> Index override {
            return dataTypes::hash(this->_targets.size());
        }

        [[nodiscard]] auto copy () const noexcept -> VShaderCompiler * override {
            return new VShaderCompiler(*this);
        }
    };

}


#endif //ENG1_VSHADERCOMPILER_HPP
