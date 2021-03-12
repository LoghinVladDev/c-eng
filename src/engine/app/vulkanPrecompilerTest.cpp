//
// Created by Vlad on 17/08/2020.
//

/**
 * Shader Precompiler Test Source
 */

#include <engineVulkanPreproc.h>
#include <vkObj/instance/pipeline/shader/VShaderCompiler.h>
#include <iostream>

using namespace engine;

int main() {

    VShaderCompiler compiler;

    std::cout << compiler.getInputDirectoryPath() << '\n';
    std::cout << compiler.getOutputDirectoryPath() << '\n';

    compiler.setConfigurationFileJSON( std::string(__VULKAN_SHADERS_PATH__).append("/config/vkTriangleShaderComp.json") );
    compiler.build();

    for(const auto & target : compiler.getTargets()) {
        auto vect = target.getLayoutBindings();

        for ( const auto & description : vect ) {
            std::cout << description.stageFlags << '\n'
                << description.descriptorCount << '\n'
                << description.descriptorType << '\n'
                << description.binding << "\n\n\n";
        }
    }

    return 0;
}