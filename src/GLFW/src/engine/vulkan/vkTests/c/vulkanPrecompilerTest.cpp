//
// Created by Vlad on 17/08/2020.
//

#include <engineVulkanPreproc.h>
#include <vkObj/shader/VShaderCompiler.h>
#include <iostream>

using namespace engine;

int main() {

    VShaderCompiler compiler;

    std::cout << compiler.getInputDirectoryPath() << '\n';
    std::cout << compiler.getOutputDirectoryPath() << '\n';

    VShaderCompilerTarget target1 ("fragmentShader.frag");

    return 0;
}