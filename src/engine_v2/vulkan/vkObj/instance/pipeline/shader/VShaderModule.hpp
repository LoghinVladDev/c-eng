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
        explicit VShaderModule ( std::string const & ) noexcept;
        explicit VShaderModule ( engine::VShaderCompilerTarget const & ) noexcept;
        ~VShaderModule() noexcept override = default;

        auto setup ( engine::VLogicalDevice const & ) noexcept -> VulkanResult;
        auto setup ( std::string const &, engine::VLogicalDevice const & ) noexcept -> VulkanResult;

        auto clear() noexcept -> void override;

        constexpr auto setType ( ShaderType type ) noexcept -> engine::VShaderModule & {
            this->_type = type;
            return *this;
        }

        [[nodiscard]] auto getShaderStageInfo () const noexcept (false) -> VulkanPipelineShaderStageCreateInfo;

        [[nodiscard]] static auto shaderTypeToString ( ShaderType ) noexcept -> std::string;
        [[nodiscard]] static auto stringToShaderType ( std::string const & ) noexcept -> ShaderType;

        [[nodiscard]] auto toString () const noexcept -> String override;

        [[nodiscard]] auto operator == (VShaderModule const & o) const noexcept -> bool {
            if ( this == & o ) return true;

            return this->_type == o._type && this->_handle == o._handle;
        }

        [[nodiscard]] auto equals (Object const & o) const noexcept -> bool override {
            if ( this == & o ) return true;
            auto p = dynamic_cast < decltype ( this ) > (& o);
            if ( p == nullptr ) return false;

            return this->operator==(*p);
        }

        [[nodiscard]] auto hash () const noexcept -> Index override {
            return dataTypes::hash(reinterpret_cast<AddressValueType>(this->_handle));
        }

        [[nodiscard]] auto copy () const noexcept -> VShaderModule * override {
            return new VShaderModule(*this);
        }
    };

}


#endif //ENG1_VSHADERMODULE_HPP
