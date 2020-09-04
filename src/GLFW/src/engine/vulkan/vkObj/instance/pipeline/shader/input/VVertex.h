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

namespace engine {

    class VVertex {
    public:

        typedef struct {
            glm::vec2 position;
            glm::vec3 color;
        } SVertexPack;

    private:
        //// private variables
        SVertexPack _vertexPack;

        constexpr static uint32 PACK_PROPERTIES_COUNT = 2U;

        //// private functions

    public:
        //// public variables
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
        VVertex() noexcept = default;
        VVertex( const glm::vec2 & position, const glm::vec3 & color ) noexcept :
            _vertexPack ( { position, color } ) {

        }

        explicit VVertex( const VVertex::SVertexPack & pack ) noexcept :
            _vertexPack ( pack ) {

        }

        [[nodiscard]] const SVertexPack & getPackedData () const noexcept {
            return this->_vertexPack;
        }

        [[nodiscard]] const glm::vec2 & getPosition () const noexcept {
            return this->_vertexPack.position;
        }

        [[nodiscard]] const glm::vec3 & getColor () const noexcept {
            return this->_vertexPack.color;
        }

        void setPosition ( const glm::vec2 & position ) noexcept {
            this->_vertexPack.position = position;
        }

        void setColor ( const glm::vec3 & color ) noexcept {
            this->_vertexPack.color = color;
        }

        static VulkanVertexInputBindingDescription                                                           getBindingDescription ()    noexcept;
        static std::array < VulkanVertexInputAttributeDescription, engine::VVertex::PACK_PROPERTIES_COUNT >  getAttributeDescriptions () noexcept;
    };

}

#endif //ENG1_VVERTEX_H
