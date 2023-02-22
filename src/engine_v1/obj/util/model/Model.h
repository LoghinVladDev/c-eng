//
// Created by vladl on 31/07/2020.
//

#ifndef ENG1_MODEL_H
#define ENG1_MODEL_H

#include <vector>
#include <obj/util/struct/meshStructs.h>
#include <obj/util/model/Mesh.h>
#include <assimp/scene.h>

namespace engine {

    class EngineModelNotLoaded : public std::exception {
    public:
        [[nodiscard]] const char * what() const noexcept override{
            return "Model not properly loaded from given path";
        }
    };

    class EngineModelPathError : public std::exception {
    public:
        [[nodiscard]] const char * what() const noexcept override{
            return "Path not given/wrong";
        }
    };

    class Model {
    private:
        std::vector<STexture> * _loadedTexturesPtr  { new std::vector<STexture>() };
        std::vector<Mesh>     * _meshesPtr          { new std::vector<Mesh>() };

        std::string _modelDirectory {std::string()};
        std::string _path {std::string()};
        bool _gammaCorrection { false };
        bool _pathGiven { false };
        bool _loaded {false};

    public:
        Model() noexcept;
        explicit Model(std::string const&, bool = false) noexcept;

        ~Model() noexcept;

        Model& setPath(std::string const&) noexcept;
        Model& setGammaCorrection(bool) noexcept;

        void draw(Shader &) noexcept(false);

        void load() noexcept;
    private:

        void _load() noexcept(false);
        void _processNode(aiNode*, const aiScene*) noexcept;
        Mesh _processMesh(aiMesh*, const aiScene*) noexcept;
        std::vector<STexture> _loadMaterialTextures(aiMaterial*, aiTextureType, const char*) noexcept;
    };

}

#endif //ENG1_MODEL_H
