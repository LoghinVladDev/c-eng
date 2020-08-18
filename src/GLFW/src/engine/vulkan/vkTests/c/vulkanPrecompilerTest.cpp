//
// Created by Vlad on 17/08/2020.
//

#include <engineVulkanPreproc.h>
#include <vkObj/instance/pipeline/shader/VShaderCompiler.h>
#include <iostream>

using namespace engine;

int main() {

    VShaderCompiler compiler;

    std::cout << compiler.getInputDirectoryPath() << '\n';
    std::cout << compiler.getOutputDirectoryPath() << '\n';

    compiler.setConfigurationFileJSON( std::string(__VULKAN_SHADERS_PATH__).append("/config/vkTriangleShaderComp.json") );

//    VShaderCompilerTarget target1 ("fragmentShader.frag");
//    VShaderCompilerTarget target2 ("vertexShader.vert");

//    compiler.addTarget( target1 );
//    compiler.addTarget( target2 );

//    compiler.build();

    compiler.build();

    return 0;
}