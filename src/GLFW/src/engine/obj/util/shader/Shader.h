//
// Created by vladl on 13/07/2020.
//

#ifndef ENG1_SHADER_H
#define ENG1_SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <types.h>

namespace engine {

    class [[maybe_unused]] Shader {
    private:
        static std::string _pathToShadersFolder;

        bool failed { false };

        uint32 ID;

        [[maybe_unused]] static void diagnoseShaderCompilation(int) noexcept;
        [[maybe_unused]] static void diagnoseProgramCompilation(int) noexcept;

    public:
        Shader() = delete;
        ~Shader();

        [[maybe_unused]] static void setShadersFolder(const std::string&) noexcept;
        [[maybe_unused]] static void setShadersFolder(const char*) noexcept;

        [[maybe_unused]] Shader(const char *, const char *, bool = false, bool = false) noexcept;
        [[maybe_unused]] Shader(const std::string&, const std::string&, bool = false, bool = false) noexcept;

        [[maybe_unused]] void use() const noexcept;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-nodiscard"

        [[maybe_unused]] Shader& setBool(const std::string &, bool) noexcept;
        [[maybe_unused]] Shader& setInt(const std::string &, int) noexcept;
        [[maybe_unused]] Shader& setFloat(const std::string &, float) noexcept;
        [[maybe_unused]] Shader& setDouble(const std::string &, double) noexcept;
        [[maybe_unused]] Shader& setVec3(const std::string &, const engine::VectorF&) noexcept;
        [[maybe_unused]] Shader& setVec4(const std::string &, const engine::Vector4F&) noexcept;
        [[maybe_unused]] Shader& setVec3d(const std::string &, const engine::VectorD&) noexcept;
        [[maybe_unused]] Shader& setVec4d(const std::string &, const engine::Vector4D&) noexcept;

#pragma clang diagnostic pop

        [[maybe_unused]] [[nodiscard]] int getID() const noexcept;
    };
}

#endif //ENG1_SHADER_H