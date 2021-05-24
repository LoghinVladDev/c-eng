//
// Created by Vlad on 17/08/2020.
//

#include "VShaderCompiler.hpp"

//const std::string engine::VShaderCompiler::defaultInputDirectoryPath    = __VULKAN_SHADERS_PATH__;
//const std::string engine::VShaderCompiler::defaultOutputDirectoryPath   = std::string ( __VULKAN_SHADERS_PATH__ ).append( "./out" );

#include <fstream>
#include <sstream>

#ifdef ENGINE_OS_WINDOWS_32_64
#include <windows.h>

static inline auto platformDependantCompilation ( std::string const & input, std::string const & output ) noexcept (false) -> void {
    std::cout << "\t" << input << '\n';
    std::cout << "\t" << output << '\n';

    STARTUPINFO startupInfo;
    PROCESS_INFORMATION processInformation;

    memset ( & startupInfo, 0, sizeof( startupInfo ) );
    memset ( & processInformation, 0, sizeof( processInformation ) );
    startupInfo.cb = sizeof( startupInfo );

    std::string app = WINDOWS_VULKAN_GLSL_COMPILER;
    std::string arg = input + " -o " + output;

    std::wstring wApp ( app.length(), L' ' );
    std::copy ( app.begin(), app.end(), wApp.begin() );

    std::wstring wArg ( arg.length(), L' ' );
    std::copy ( arg.begin(), arg.end(), wArg.begin() );

    std::wstring wInput = wApp + L" " + wArg;
    auto * pConstArg = const_cast < wchar_t * > ( wInput.c_str() );
    const wchar_t* pConstApp = wApp.c_str();


//    if( ! CreateProcessA (
//            pConstApp,
//            pConstArg,
//            NULL,
//            NULL,
//            FALSE,
//            0,
//            NULL,
//            NULL,
//            & startupInfo,
//            & processInformation
//        )
//    ) {
//        std::printf("Create Process failed (%d).\n", GetLastError() );
//        throw std::runtime_error("compilation of target failed");
//
//    }

    system ( std::string ( WINDOWS_VULKAN_GLSL_COMPILER ).append(" ").append( input ).append(" -o ").append(output).c_str() );

}

#endif

#if defined(ENGINE_OS_LINUX)

#include <unistd.h>
#include <wait.h>

static inline auto platformDependantCompilation ( std::string const & input, std::string const & output ) noexcept (false) -> void {
    std::cout << input << '\n';
    std::cout << output << '\n';

    pid_t processID = fork ();

    if ( processID == 0 ) {
        if ( -1 == execlp (
            LINUX_VULKAN_GLSL_COMPILER,
            LINUX_VULKAN_GLSL_COMPILER,
            input.c_str(),
            LINUX_VULKAN_GLSL_COMPILER_OUTPUT_ARGUMENT,
            output.c_str(),
            nullptr
            )
        ) {
            std::cerr << "Compilation Failed\n";
            exit (LINUX_VULKAN_GLSL_COMPILATION_FAILED_RETURN_VALUE);
        }
    } else if ( processID > 0 ) {
        int childProcessReturnStatus = 0U;
        if ( -1 == waitpid( processID, & childProcessReturnStatus, 0) )
            throw std::runtime_error ( "Compile process failure" );
        if ( childProcessReturnStatus == LINUX_VULKAN_GLSL_COMPILATION_FAILED_CHILD_RETURN_VALUE ) {
            throw std::runtime_error ( "Compilation failed in child process" );
        }
    }
}

#endif

static inline auto getShaderStageFlagBits ( engine::VShaderModule::ShaderType shaderType ) noexcept -> VulkanShaderStageFlagBits {
    switch ( shaderType ) {
        case engine::VShaderModule::VERTEX:         return VulkanShaderStageFlagBits::VK_SHADER_STAGE_VERTEX_BIT;
        case engine::VShaderModule::GEOMETRY:       return VulkanShaderStageFlagBits::VK_SHADER_STAGE_GEOMETRY_BIT;
        case engine::VShaderModule::FRAGMENT:       return VulkanShaderStageFlagBits::VK_SHADER_STAGE_FRAGMENT_BIT;
        case engine::VShaderModule::TESSELATION:
        case engine::VShaderModule::UNDEFINED:
        default:                                    return VulkanShaderStageFlagBits::VK_SHADER_STAGE_ALL;
    }
}

auto engine::VShaderCompilerTarget::getLayoutBindings() const noexcept -> std::vector < VulkanDescriptorSetLayoutBinding > {
    std::string fullPath = this->_pCompiler->getInputDirectoryPath() + "/" + this->_path;

    std::ifstream shaderFile;
    std::stringstream stream;
    shaderFile.open(fullPath);

    stream << shaderFile.rdbuf();

    std::string code = stream.str();
    std::size_t previousIndex = 0U;
    std::size_t currentIndex = 0U;
    bool start = true;

    std::vector < VulkanDescriptorSetLayoutBinding > bindings;

    while ( ( currentIndex = code.find(" uniform ", start ? 0U : previousIndex + std::string(" uniform ").length() ) ) != std::string::npos ) {

        bindings.push_back(
            VulkanDescriptorSetLayoutBinding {
                .binding            = static_cast< uint32 > ( std::strtol( code.substr ( code.find ( '=', code.rfind("binding", currentIndex) ) + 1 ).c_str(), nullptr, 10 ) ),
                .descriptorType     = code.find( " uniform sampler2D ", currentIndex ) == currentIndex
                        ? VulkanDescriptorType::VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER
                        : VulkanDescriptorType::VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
                .descriptorCount    = 1U,
                .stageFlags         = static_cast<VkShaderStageFlags>(getShaderStageFlagBits( this->_shaderType )),
                .pImmutableSamplers = nullptr
            }
        );

        previousIndex = currentIndex;
        start = false;
    }

//    std::cout << code << '\n';

    return bindings;
}

#include <engineDataPaths.h>
engine::VShaderCompiler::VShaderCompiler() noexcept : VObject() {
    this->_inputDirectoryPath     = __VULKAN_SHADERS_PATH__;
    this->_outputDirectoryPath    = std::string( __VULKAN_SHADERS_PATH__ ).append("/out");
}

engine::VShaderCompiler::VShaderCompiler(
        std::string const & inputFolderPath,
        std::string const & outputFolderPath
) noexcept : VObject() {
    this->_inputDirectoryPath     = inputFolderPath;
    this->_outputDirectoryPath    = ( outputFolderPath.empty() ? std::string(__VULKAN_SHADERS_PATH__).append("/out") : outputFolderPath );
}

auto engine::VShaderCompiler::addTarget(engine::VShaderCompilerTarget const & target) noexcept -> engine::VShaderCompiler & {
    target._pCompiler = this;
    this->_targets.push_back( target );

    return *this;
}

auto engine::VShaderCompiler::addTarget(std::string const &) noexcept -> engine::VShaderCompiler & {
    return *this;
}

auto engine::VShaderCompiler::addTargets(std::vector < VShaderCompilerTarget > const &) noexcept -> engine::VShaderCompiler & {
    return *this;
}

auto engine::VShaderCompiler::addTargets(std::vector < std::string > const &) noexcept -> engine::VShaderCompiler & {
    return *this;
}

auto engine::VShaderCompiler::build() noexcept -> void {
    for ( auto & target : this->_targets )
        target.compile();
}

auto engine::VShaderCompiler::setConfigurationFile(JSON const & json) noexcept -> engine::VShaderCompiler & {
    JSON configuration = json.getJSON( "compilerConfig" );

    this->_targets.clear();
    this->_inputDirectoryPath = std::string("./").append( configuration.getString("compilerInputDir").toStdString() );
    this->_outputDirectoryPath = std::string("./").append( configuration.getString("compilerOutputDir").toStdString() );

    auto targets = configuration.getArray("sources");

    for( uint32 index = 0; index < targets.length(); index++ ) {
        JSON targetJSON = targets.getJSON ( index );

        engine::VShaderCompilerTarget target;

        target.setPath( targetJSON.getString("path").toStdString() );
        target.setTargetName( targetJSON.getString("outputName").toStdString() );
        target.setTag( targetJSON.getString("tag").toStdString() );
        target._pCompiler = this;
        target._shaderType = engine::VShaderModule::stringToShaderType( targetJSON.getString( "type" ).toStdString() );

        this->_targets.push_back( target );
    }

    std::cout.flush();

    return *this;
}

auto engine::VShaderCompiler::setConfigurationFileJSON(std::string const & path) noexcept -> engine::VShaderCompiler & {
    std::ifstream inputFile;
    std::stringstream fileDataStream;
    inputFile.open( path );

    fileDataStream << inputFile.rdbuf();
    inputFile.close();

    try {
        return this->setConfigurationFile(JSON::parse(fileDataStream.str()));
    } catch ( std::exception const & ex ) {
        std::cout.flush();
        std::cout << ex.what() << '\n';
    }

    return *this;
}

auto engine::VShaderCompilerTarget::compile() noexcept -> void {
    static uint32 targetIndex = 0U;

    std::cout << "Target " << (targetIndex++) << '\n';

    std::string fullPath = this->_pCompiler->getInputDirectoryPath() + "/" + this->_path;
    this->_outputPath = this->_pCompiler->getOutputDirectoryPath() + "/" + this->_targetName;

    std::cout << "\tName: " << this->_targetName << '\n';
    try {
        platformDependantCompilation( fullPath, this->_outputPath );
    } catch ( std::exception const & exception ) {
        std::cout << exception.what() << '\n';
    }
}


//engine::VShaderCompilerTarget & engine::VShaderCompilerTarget::setCompiler(engine::VShaderCompiler &compiler, bool calledFromWithin) noexcept {

//    this->_pCompiler = & compiler;

//    if ( ! calledFromWithin )
//        compiler.addTarget( * this , true);

//    return *this;
//}

#include <sstream>

auto engine::VShaderCompilerTarget::toString() const noexcept -> String {
    std::stringstream oss;

    oss << "VShaderCompilerTarget { " <<
        "targetName = " << this->_targetName <<
        ", tag = " << this->_tag <<
        ", shaderType = " << VShaderModule::shaderTypeToString(this->_shaderType) <<
        ", path = " << this->_path <<
        ", outputPath = " << this->_outputPath <<
        ", pCompiler = 0x" << std::hex << reinterpret_cast<AddressValueType>(this->_pCompiler) << " }";

    return oss.str();
}

auto engine::VShaderCompiler::toString() const noexcept -> String {
    std::stringstream oss;

    oss << "VShaderCompiler { " <<
        "inputDirectoryPath = " << this->_inputDirectoryPath <<
        ", outputDirectoryPath = " << this->_outputDirectoryPath <<
        ", targets = [ ";

    for (auto const & item : this->_targets)
        oss << item.toString() << ", ";
    auto s = oss.str();

    return s.substr(s.size() - 2).append(" ]}");
}