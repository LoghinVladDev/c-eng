//
// Created by vladl on 8/27/2020.
//

#ifndef ENG1_VVERTEX_H
#define ENG1_VVERTEX_H

#include <engineVulkanPreproc.h>
#include <vkDefs/types/vulkanExplicitTypes.h>
#include <vkObj/instance/device/VLogicalDevice.h>
#include <glm/glm.hpp>
#include <array>
#include <type_traits>

namespace engine {

    class VVertex {
    public:

        typedef struct {
            glm::vec3 position;
            glm::vec3 color;
            glm::vec2 textureCoordinates;
        } SVertexPack;

    private:
        //// private variables
        SVertexPack _vertexPack;

        constexpr static uint32 PACK_PROPERTIES_COUNT = 3U;

        //// private functions

    public:
        //// public variables
        constexpr static VulkanFormat UNKNOWN_FORMAT        = VulkanFormat::VK_FORMAT_UNDEFINED;

        constexpr static VulkanFormat FLOAT_FORMAT          = VulkanFormat::VK_FORMAT_R32_SFLOAT;
        constexpr static VulkanFormat FLOAT_VEC2_FORMAT     = VulkanFormat::VK_FORMAT_R32G32_SFLOAT;
        constexpr static VulkanFormat FLOAT_VEC3_FORMAT     = VulkanFormat::VK_FORMAT_R32G32B32_SFLOAT;
        constexpr static VulkanFormat FLOAT_VEC4_FORMAT     = VulkanFormat::VK_FORMAT_R32G32B32A32_SFLOAT;

        constexpr static VulkanFormat UINT_FORMAT           = VulkanFormat::VK_FORMAT_R32_UINT;
        constexpr static VulkanFormat UINT_VEC2_FORMAT      = VulkanFormat::VK_FORMAT_R32G32_UINT;
        constexpr static VulkanFormat UINT_VEC3_FORMAT      = VulkanFormat::VK_FORMAT_R32G32B32_UINT;
        constexpr static VulkanFormat UINT_VEC4_FORMAT      = VulkanFormat::VK_FORMAT_R32G32B32A32_UINT;

        constexpr static VulkanFormat INT_FORMAT            = VulkanFormat::VK_FORMAT_R32_SINT;
        constexpr static VulkanFormat INT_VEC2_FORMAT       = VulkanFormat::VK_FORMAT_R32G32_SINT;
        constexpr static VulkanFormat INT_VEC3_FORMAT       = VulkanFormat::VK_FORMAT_R32G32B32_SINT;
        constexpr static VulkanFormat INT_VEC4_FORMAT       = VulkanFormat::VK_FORMAT_R32G32B32A32_SINT;

        constexpr static VulkanFormat DOUBLE_FORMAT         = VulkanFormat::VK_FORMAT_R64_SFLOAT;
        constexpr static VulkanFormat DOUBLE_VEC2_FORMAT    = VulkanFormat::VK_FORMAT_R64G64_SFLOAT;
        constexpr static VulkanFormat DOUBLE_VEC3_FORMAT    = VulkanFormat::VK_FORMAT_R64G64B64_SFLOAT;
        constexpr static VulkanFormat DOUBLE_VEC4_FORMAT    = VulkanFormat::VK_FORMAT_R64G64B64A64_SFLOAT;

        constexpr static VulkanFormat LUINT_FORMAT          = VulkanFormat::VK_FORMAT_R64_UINT;
        constexpr static VulkanFormat LUINT_VEC2_FORMAT     = VulkanFormat::VK_FORMAT_R64G64_UINT;
        constexpr static VulkanFormat LUINT_VEC3_FORMAT     = VulkanFormat::VK_FORMAT_R64G64B64_UINT;
        constexpr static VulkanFormat LUINT_VEC4_FORMAT     = VulkanFormat::VK_FORMAT_R64G64B64A64_UINT;

        constexpr static VulkanFormat LINT_FORMAT           = VulkanFormat::VK_FORMAT_R64_SINT;
        constexpr static VulkanFormat LINT_VEC2_FORMAT      = VulkanFormat::VK_FORMAT_R64G64_SINT;
        constexpr static VulkanFormat LINT_VEC3_FORMAT      = VulkanFormat::VK_FORMAT_R64G64B64_SINT;
        constexpr static VulkanFormat LINT_VEC4_FORMAT      = VulkanFormat::VK_FORMAT_R64G64B64A64_SINT;

        //// public functions

#define __GEN_SHADER_VAR_FORMAT_CASE(_type1, _type2, _normLabel) \
    if constexpr ( std::is_same_v < _type1, _type2 > ) \
        return _normLabel ## _FORMAT;               \
    else if constexpr ( std::is_same_v < _type1, glm::vec < 2, _type2, glm::defaultp > > ) \
        return _normLabel ## _VEC2_FORMAT;                                     \
    else if constexpr ( std::is_same_v < _type1, glm::vec < 3, _type2, glm::defaultp > > ) \
        return _normLabel ## _VEC3_FORMAT;                                     \
    else if constexpr ( std::is_same_v < _type1, glm::vec < 4, _type2, glm::defaultp > > ) \
        return _normLabel ## _VEC4_FORMAT;

        template <class T>
        constexpr static VulkanFormat getShaderVariableFormat( T ) noexcept {
            __GEN_SHADER_VAR_FORMAT_CASE( T, float, FLOAT )
            else __GEN_SHADER_VAR_FORMAT_CASE( T, uint32, UINT )
            else __GEN_SHADER_VAR_FORMAT_CASE( T, int32, INT)
            else __GEN_SHADER_VAR_FORMAT_CASE( T, double, DOUBLE)
            else __GEN_SHADER_VAR_FORMAT_CASE( T, uint64, LUINT)
            else __GEN_SHADER_VAR_FORMAT_CASE( T, int64, LINT)

            return VVertex::UNKNOWN_FORMAT;
        }

#undef __GEN_SHADER_VAR_FORMAT_CASE

        VVertex() noexcept = default;
        VVertex( const glm::vec3 & position, const glm::vec3 & color, const glm::vec2 & textureCoordinates ) noexcept :
            _vertexPack ( { position, color, textureCoordinates } ) {

        }

        VVertex( const glm::vec3 & position, const glm::vec3 & color ) noexcept :
            _vertexPack ( { position, color, glm::vec2 { 0.0f, 0.0f } } ) {

        }

        VVertex( const glm::vec3 & position, const glm::vec2 & textureCoordinates ) noexcept :
            _vertexPack ( { position, glm::vec3 {0.0f, 0.0f, 0.0f }, textureCoordinates } ) {

        }

        VVertex( const glm::vec3 & position ) noexcept :
            _vertexPack ( { position, glm::vec3 { 0.0f, 0.0f, 0.0f }, glm::vec2 { 0.0f, 0.0f } } ) {

        }

        VVertex( const VVertex::SVertexPack & pack ) noexcept :
            _vertexPack ( pack ) {

        }

        [[nodiscard]] const SVertexPack & getPackedData () const noexcept {
            return this->_vertexPack;
        }

        [[nodiscard]] const glm::vec3 & getPosition () const noexcept {
            return this->_vertexPack.position;
        }

        [[nodiscard]] const glm::vec2 & getTextureCoordinates () const noexcept {
            return this->_vertexPack.textureCoordinates;
        }

        [[nodiscard]] const glm::vec3 & getColor () const noexcept {
            return this->_vertexPack.color;
        }

        void setPosition ( const glm::vec3 & position ) noexcept {
            this->_vertexPack.position = position;
        }

        void setColor ( const glm::vec3 & color ) noexcept {
            this->_vertexPack.color = color;
        }

        void setTextureCoordinates ( const glm::vec2 & textureCoordinates ) noexcept {
            this->_vertexPack.textureCoordinates = textureCoordinates;
        }

        static VulkanVertexInputBindingDescription                                                           getBindingDescription ()    noexcept;
        static std::array < VulkanVertexInputAttributeDescription, engine::VVertex::PACK_PROPERTIES_COUNT >  getAttributeDescriptions () noexcept;
    };

}

#endif //ENG1_VVERTEX_H
