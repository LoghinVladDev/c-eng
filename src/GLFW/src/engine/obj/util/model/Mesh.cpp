//
// Created by loghin on 7/20/20.
//

#include "Mesh.h"
#include <cstddef>

engine::Mesh::Mesh() noexcept = default;

engine::Mesh::Mesh(const std::vector<SVertex> & vertices, const std::vector<uint32> & indices, const std::vector<STexture> & textures) noexcept(false) :
    _verticesPtr(new std::vector<SVertex>(vertices)),
    _indicesPtr(new std::vector<uint32>(indices)),
//    _texturesPtr(new std::vector<STexture>(textures)),
    _verticesLoaded(true),
    _indicesLoaded(true),
    _texturesLoaded(true),
    _loaded(true) {
    if(textures.size() > engine::Mesh::_TEXTURE_LIMIT)
        throw engine::MeshTextureLimitReached();

    this->_texturesPtr = new std::vector<STexture>(textures);

    this->setupMesh();
}

engine::Mesh::~Mesh() noexcept {
    delete this->_verticesPtr;
    delete this->_indicesPtr;
    delete this->_texturesPtr;

    glDeleteVertexArrays(1, &this->_VAO);
    glDeleteBuffers(1, &this->_VBO);
    glDeleteBuffers(1, &this->_EBO);
}

[[maybe_unused]] engine::Mesh& engine::Mesh::setVertices(const std::vector<SVertex> & vertices) noexcept {
    delete this->_verticesPtr;

    this->_verticesPtr = new std::vector<SVertex>(vertices);
    this->_verticesLoaded = true;

//    if(this->_indicesLoaded && this->_texturesLoaded)
//        this->_loaded = true;

    return *this;
}

[[maybe_unused]] engine::Mesh& engine::Mesh::setIndices(const std::vector<uint32> & indices) noexcept {
    delete this->_indicesPtr;

    this->_indicesPtr = new std::vector<uint32>(indices);
    this->_indicesLoaded = true;

//    if(this->_verticesLoaded && this->_texturesLoaded)
//        this->_loaded = true;

    return *this;
}

[[maybe_unused]] engine::Mesh& engine::Mesh::setTextures(const std::vector<STexture> & textures) noexcept (false) {
    if(textures.size() > engine::Mesh::_TEXTURE_LIMIT)
        throw engine::MeshTextureLimitReached();

    delete this->_texturesPtr;

    this->_texturesPtr = new std::vector<STexture>(textures);
    this->_texturesLoaded = true;

//    if(this->_verticesLoaded && this->_indicesLoaded)
//        this->_loaded = true;

    return *this;
}

void engine::Mesh::setupMesh() noexcept {
    glGenVertexArrays(1, &this->_VAO);
    glGenBuffers(1, &this->_VBO);
    glGenBuffers(1, &this->_EBO);

    glBindVertexArray(this->_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->_VBO);

    glBufferData(GL_ARRAY_BUFFER, this->_verticesPtr->size() * sizeof(SVertex), & ((*this->_verticesPtr)[0]), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->_indicesPtr->size() * sizeof(uint32), & ((*this->_indicesPtr)[0]), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SVertex), (void*)offsetof(SVertex, position));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(SVertex), (void*)offsetof(SVertex, normal));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(SVertex), (void*)offsetof(SVertex, coordinates));

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(SVertex), (void*)offsetof(SVertex, tangent));

    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(SVertex), (void*)offsetof(SVertex, bitangent));

    glBindVertexArray(0);
}

void engine::Mesh::load() noexcept (false) {
    this->_loaded = this->_verticesLoaded && this->_indicesLoaded && this->_texturesLoaded;

    if(!this->_loaded)
        throw engine::MeshDataNotLoaded();

    this->setupMesh();
}

/**
 * TODO : implement dynamic generation of shader defines for Material Struct
 * @param shader
 */
void engine::Mesh::draw(Shader & shader) noexcept (false) {
    if(!this->_loaded)
        throw engine::MeshDataNotLoaded();

    uint8 diffuseTexturesCount = 0U;
    uint8 specularTexturesCount = 0U;
    uint8 normalTexturesCount = 0U;
    uint8 ambientTexturesCount = 0U;

    std::string number;
    std::string type;
    std::string attributeTag;

    for(std::size_t i = 0, length = std::min(this->_texturesPtr->size(), _TEXTURE_LIMIT); i < length; i++) {
        glActiveTexture(GL_TEXTURE0 + i);

        attributeTag = "material.";

        type = (*this->_texturesPtr)[i].type;
        if(type == _TEXTURE_TYPE_DIFFUSE)
            number = std::to_string(diffuseTexturesCount++);
        else if(type == _TEXTURE_TYPE_SPECULAR)
            number = std::to_string(specularTexturesCount++);
        else if(type == _TEXTURE_TYPE_NORMAL)
            number = std::to_string(normalTexturesCount++);
        else if(type == _TEXTURE_TYPE_AMBIENT)
            number = std::to_string(ambientTexturesCount++);

        attributeTag += type + number;

        shader.setInt(attributeTag, i);
        glBindTexture(GL_TEXTURE_2D, (*this->_texturesPtr)[i].id);
    }
    glActiveTexture(GL_TEXTURE0);

    glBindVertexArray(this->_VAO);
    glDrawElements(GL_TRIANGLES, this->_indicesPtr->size(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);

    glActiveTexture(GL_TEXTURE0);
}