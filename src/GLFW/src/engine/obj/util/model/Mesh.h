//
// Created by loghin on 7/20/20.
//

#ifndef ENG1_MESH_H
#define ENG1_MESH_H

#include <types.h>
#include <vector>
#include <src/GLFW/src/engine/obj/util/shader/Shader.h>
#include <glad/glad.h>

//#define _TEXTURE_LIMIT 32U

namespace engine {
    class MeshDataNotLoaded : public std::exception {
    public:
        [[nodiscard]] const char * what() const noexcept override {
            return "For drawing, vertices, indices & textures have to be loaded";
        }
    };

    class MeshTextureLimitReached : public std::exception {
    public:
        [[nodiscard]] const char * what() const noexcept override {
            return "Textures limited to 32 per mesh!";
        }
    };

    class Mesh{
    private:

#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-reserved-identifier"
        constexpr static std::size_t _TEXTURE_LIMIT = 32U;
#pragma clang diagnostic pop

        bool _verticesLoaded {false};
        bool _indicesLoaded  {false};
        bool _texturesLoaded {false};
        bool _loaded         {false};

        std::vector<SVertex>*    _verticesPtr    {nullptr};
        std::vector<uint32>*     _indicesPtr     {nullptr};
        std::vector<STexture>*   _texturesPtr    {nullptr};

#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-reserved-identifier"
        uint32 _VAO {0};
        uint32 _VBO {0};
        uint32 _EBO {0};
#pragma clang diagnostic pop

        void setupMesh() noexcept;

    public:
        Mesh() noexcept;
        Mesh(const std::vector<SVertex> &, const std::vector<uint32>&, const std::vector<STexture>&) noexcept(false);
        ~Mesh() noexcept;

        void draw(Shader&) noexcept (false);
        void load() noexcept (false);

        [[maybe_unused]] Mesh& setVertices(const std::vector<SVertex> &) noexcept;

        [[maybe_unused]] Mesh& setIndices(const std::vector<uint32> &) noexcept;

        [[maybe_unused]] Mesh& setTextures(const std::vector<STexture> &) noexcept (false);

        [[maybe_unused]] [[nodiscard]] const std::vector <SVertex>  * getVertices  () const { return this->_verticesPtr; }
        [[maybe_unused]] [[nodiscard]] const std::vector <uint32>   * getIndices   () const { return this->_indicesPtr; }
        [[maybe_unused]] [[nodiscard]] const std::vector <STexture> * getTextures  () const { return this->_texturesPtr; }
        [[maybe_unused]] [[nodiscard]] int getVertexArrayObject     () const { return this->_VAO; }
        [[maybe_unused]] [[nodiscard]] int getVertexBufferObject    () const { return this->_VBO; }
        [[maybe_unused]] [[nodiscard]] int getElementBufferObject   () const { return this->_EBO; }
    };
}


#endif //ENG1_MESH_H
