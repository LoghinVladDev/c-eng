//
// Created by Vlad on 17/08/2020.
//

#include "VShaderCompiler.h"

//const std::string engine::VShaderCompiler::defaultInputDirectoryPath    = __VULKAN_SHADERS_PATH__;
//const std::string engine::VShaderCompiler::defaultOutputDirectoryPath   = std::string ( __VULKAN_SHADERS_PATH__ ).append( "./out" );


engine::VShaderCompiler::VShaderCompiler() noexcept (false) {
    this->_inputDirectoryPath     = __VULKAN_SHADERS_PATH__;
    this->_outputDirectoryPath    = std::string( __VULKAN_SHADERS_PATH__ ).append("/out");
}

engine::VShaderCompiler::VShaderCompiler(const std::string & inputFolderPath, const std::string & outputFolderPath) noexcept(false) {
    this->_inputDirectoryPath     = inputFolderPath;
    this->_outputDirectoryPath    = ( outputFolderPath.empty() ? std::string(__VULKAN_SHADERS_PATH__).append("/out") : outputFolderPath );
}

engine::VShaderCompiler &engine::VShaderCompiler::addTarget(engine::VShaderCompilerTarget & target, bool calledFromWithin) {
    if ( ! calledFromWithin )
        target.setCompiler( *this, true );

    this->_targets.push_back( target );

    return *this;
}

engine::VShaderCompiler &engine::VShaderCompiler::addTarget(std::string &) {
    return *this;
}

engine::VShaderCompiler &engine::VShaderCompiler::addTargets(std::vector<VShaderCompilerTarget> &) {
    return *this;
}

engine::VShaderCompiler &engine::VShaderCompiler::addTargets(std::vector<std::string> &) {
    return *this;
}

void engine::VShaderCompiler::build() noexcept {

}

void engine::VShaderCompilerTarget::compile() noexcept {

}

engine::VShaderCompilerTarget & engine::VShaderCompilerTarget::setCompiler(engine::VShaderCompiler &compiler, bool calledFromWithin) noexcept {

    this->_pCompiler = & compiler;

    if ( ! calledFromWithin )
        compiler.addTarget( * this , true);

    return *this;
}
