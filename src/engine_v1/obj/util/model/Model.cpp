//
// Created by vladl on 31/07/2020.
//

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include "Model.h"
#include <obj/util/func/TextureManager.h>

engine::Model::Model() noexcept = default;

engine::Model::~Model() noexcept {
    delete this->_loadedTexturesPtr;
    delete this->_meshesPtr;
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-pass-by-value"
engine::Model::Model(const std::string & path, bool enableGammaCorrection) noexcept :
    _gammaCorrection(enableGammaCorrection),
    _pathGiven(true),
    _path(path){
    this->_load();
}
#pragma clang diagnostic pop

void engine::Model::load() noexcept {
    if(this->_pathGiven)
        if(!this->_loaded)
            this->_load();
}

engine::Model& engine::Model::setPath(std::string const& path) noexcept {
    this->_pathGiven = true;
    this->_path = path;
}

engine::Model& engine::Model::setGammaCorrection(bool toggle) noexcept {
    this->_gammaCorrection = toggle;
}

void engine::Model::draw(Shader &shader) noexcept (false) {
    if(!this->_loaded)
        throw EngineModelNotLoaded();

    for(Mesh & mesh : (*(this->_meshesPtr)) ) {
        mesh.draw(shader);
    }
}

void engine::Model::_load() noexcept (false) {
    if(!this->_pathGiven)
        throw EngineModelPathError();

    Assimp::Importer importer;

    //aiProcess_OptimizeMeshes for clamping meshes into a bigger mesh for faster loads -> more RAM used
    const aiScene* scene = importer.ReadFile(this->_path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if( scene == nullptr || scene->mFlags & (uint8)AI_SCENE_FLAGS_INCOMPLETE || scene->mRootNode == nullptr ) {
        std::cout << "Assimp Load Error : " << importer.GetErrorString() << '\n';
        return;
    }

    this->_modelDirectory = this->_path.substr(0, this->_path.find_last_of('/'));
    this->_processNode(scene->mRootNode, scene);
}

void engine::Model::_processNode(aiNode * node, const aiScene * scene) noexcept {
    for(uint32 it = 0; it < node->mNumMeshes; it++) {
        aiMesh * mesh = scene->mMeshes[node->mMeshes[it]];
        this->_meshesPtr->push_back(this->_processMesh(mesh, scene));
    }
    for(uint32 it = 0; it < node->mNumChildren; it++) {
        this->_processNode(node->mChildren[it], scene);
    }
}

engine::Mesh engine::Model::_processMesh(aiMesh * mesh, const aiScene * scene) noexcept {
    std::vector<SVertex>    vertices;
    std::vector<uint32>     indices;
    std::vector<STexture>   textures;

    for(uint32 i = 0; i < mesh->mNumVertices; i++) {
        vertices.push_back(
            SVertex{
                glm::vec3(mesh->mVertices[i].x,mesh->mVertices[i].y,mesh->mVertices[i].z),
                glm::vec3(mesh->mNormals[i].x,mesh->mNormals[i].y,mesh->mNormals[i].z),
                mesh->mTextureCoords[0] == nullptr ?
                    glm::vec2(0.0f, 0.0f) :
                    glm::vec2(mesh->mTextureCoords[0][i].x,mesh->mTextureCoords[0][i].y),
                glm::vec3(mesh->mTangents[i].x,mesh->mTangents[i].y,mesh->mTangents[i].z),
                glm::vec3(mesh->mBitangents[i].x,mesh->mBitangents[i].y,mesh->mBitangents[i].z)
            }
        );
    }

    for(uint32 i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];

        for(uint32 j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    aiMaterial * material = scene->mMaterials[mesh->mMaterialIndex];

    std::vector<STexture> diffuseMaps   = this->_loadMaterialTextures(material, aiTextureType_DIFFUSE, _TEXTURE_TYPE_DIFFUSE);
    std::vector<STexture> specularMaps  = this->_loadMaterialTextures(material, aiTextureType_SPECULAR, _TEXTURE_TYPE_SPECULAR);
    std::vector<STexture> normalMaps    = this->_loadMaterialTextures(material, aiTextureType_NORMALS, _TEXTURE_TYPE_NORMAL);
    std::vector<STexture> ambientMaps   = this->_loadMaterialTextures(material, aiTextureType_AMBIENT, _TEXTURE_TYPE_AMBIENT);

    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    textures.insert(textures.end(), ambientMaps.begin(), ambientMaps.end());

    return engine::Mesh(vertices, indices, textures);
}

std::vector <STexture> engine::Model::_loadMaterialTextures(aiMaterial * material, aiTextureType type, const char * typeName) noexcept {
    std::vector <STexture> textures;

    for(uint32 i = 0; i < material->GetTextureCount(type); i++) {
        aiString string;
        material->GetTexture(type, i, &string);
        bool textureAlreadyLoaded = false;
        for(STexture & texture : (*this->_loadedTexturesPtr)) {
            if(std::strcmp(texture.path.c_str(), string.C_Str()) == 0) {
                textures.push_back(texture);
                textureAlreadyLoaded = true;
                break;
            }
        }
        if( ! textureAlreadyLoaded ) {
            STexture texture {
                engine::TextureManager::loadTextureFromFile(string.C_Str(), this->_modelDirectory, this->_gammaCorrection),
                typeName,
                string.C_Str(),
            };

            textures.push_back(texture);
            this->_loadedTexturesPtr->push_back(texture);
        }
    }

    return textures;
}
