//
// Created by vladl on 8/27/2020.
//

#ifndef ENG1_VVERTEX_HPP
#define ENG1_VVERTEX_HPP

#include <engineVulkanPreproc.hpp>
#include <vkDefs/types/vulkanExplicitTypes.h>
#include <vkObj/instance/device/VLogicalDevice.hpp>
#include <glm/glm.hpp>
#include <array>
#include <type_traits>

namespace engine {

    class VVertex : public VObject {
    public:

        typedef struct {
            glm::vec3 position;
            glm::vec3 color;
            glm::vec2 textureCoordinates;
        } SVertexPack;

    private:
        //// private variables
        SVertexPack _vertexPack {
            .position           = {0.0f, 0.0f, 0.0f},
            .color              = {0.0f, 0.0f, 0.0f},
            .textureCoordinates = {0.0f, 0.0f}
        };

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
            else __GEN_SHADER_VAR_FORMAT_CASE( T, sint32, INT)
            else __GEN_SHADER_VAR_FORMAT_CASE( T, double, DOUBLE)
            else __GEN_SHADER_VAR_FORMAT_CASE( T, uint64, LUINT)
            else __GEN_SHADER_VAR_FORMAT_CASE( T, sint64, LINT)

            return VVertex::UNKNOWN_FORMAT;
        }

#undef __GEN_SHADER_VAR_FORMAT_CASE

        VVertex() noexcept = default;
        VVertex(
                glm::vec3 const & position,
                glm::vec3 const & color,
                glm::vec2 const & textureCoordinates
        ) noexcept :
            VObject(),
            _vertexPack ( { position, color, textureCoordinates } ) {

        }

        VVertex(
                glm::vec3 const & position,
                glm::vec3 const & color
        ) noexcept :
            VObject(),
            _vertexPack ( { position, color, glm::vec2 { 0.0f, 0.0f } } ) {

        }

        VVertex(
                glm::vec3 const & position,
                glm::vec2 const & textureCoordinates
        ) noexcept :
            VObject(),
            _vertexPack ( { position, glm::vec3 {0.0f, 0.0f, 0.0f }, textureCoordinates } ) {

        }

        explicit VVertex( glm::vec3 const & position ) noexcept :
            VObject(),
            _vertexPack ( { position, glm::vec3 { 0.0f, 0.0f, 0.0f }, glm::vec2 { 0.0f, 0.0f } } ) {

        }

        explicit VVertex( VVertex::SVertexPack const & pack ) noexcept :
            VObject(),
            _vertexPack ( pack ) {

        }

        ~VVertex () noexcept override = default;

        [[nodiscard]] constexpr auto getPackedData () const noexcept -> SVertexPack const & {
            return this->_vertexPack;
        }

        [[nodiscard]] constexpr auto getPosition () const noexcept -> glm::vec3 const & {
            return this->_vertexPack.position;
        }

        [[nodiscard]] constexpr auto getTextureCoordinates () const noexcept -> glm::vec2 const & {
            return this->_vertexPack.textureCoordinates;
        }

        [[nodiscard]] constexpr auto getColor () const noexcept -> glm::vec3 const & {
            return this->_vertexPack.color;
        }

        GLM_CONSTEXPR inline auto setPosition ( glm::vec3 const & position ) noexcept -> void {
            this->_vertexPack.position = position;
        }

        GLM_CONSTEXPR inline auto setColor ( glm::vec3 const & color ) noexcept -> void {
            this->_vertexPack.color = color;
        }

        GLM_CONSTEXPR inline auto setTextureCoordinates ( glm::vec2 const & textureCoordinates ) noexcept -> void {
            this->_vertexPack.textureCoordinates = textureCoordinates;
        }

        static auto getBindingDescription () noexcept -> VulkanVertexInputBindingDescription;
        static auto getAttributeDescriptions () noexcept -> std::array < VulkanVertexInputAttributeDescription, engine::VVertex::PACK_PROPERTIES_COUNT >;

        [[nodiscard]] auto toString () const noexcept -> String override;

        [[nodiscard]] auto operator == (VVertex const & o) const noexcept -> bool {
            if ( this == & o ) return true;

            return
                this->_vertexPack.position              == o._vertexPack.position  &&
                this->_vertexPack.color                 == o._vertexPack.color     &&
                this->_vertexPack.textureCoordinates    == o._vertexPack.textureCoordinates;
        }

        [[nodiscard]] auto equals (Object const & o) const noexcept -> bool override {
            if ( this == & o ) return true;
            auto p = dynamic_cast < decltype ( this ) > ( & o );
            if ( p == nullptr ) return false;

            return this->operator==( *p );
        }

        [[nodiscard]] auto hash () const noexcept -> Index override {
            return
                dataTypes::hash(this->_vertexPack.position) * 10000 +
                dataTypes::hash(this->_vertexPack.color)    * 100   +
                dataTypes::hash(this->_vertexPack.textureCoordinates);
        }

        [[nodiscard]] auto copy () const noexcept -> VVertex * override {
            return new VVertex(*this);
        }
    };

}

#endif //ENG1_VVERTEX_HPP
