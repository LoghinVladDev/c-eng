cmake_minimum_required(VERSION 3.5)
project(c-eng)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
set(OpenGL_GL_PREFERENCE GLVND)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=undefined")

if(MSVC)
    add_compile_options("$<$<CONFIG:RELEASE>:/O2>")
else()
    add_compile_options("$<$<CONFIG:RELEASE>:-O3>")
endif()

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_subdirectory(dependencies/glfw)
add_subdirectory(dependencies/glm)
add_subdirectory(dependencies/meshLoader)

include_directories(dependencies/glm)
include_directories(dependencies/glfw/include)
include_directories(dependencies/stb)
include_directories(dependencies/cds/include)
include_directories(dependencies/meshLoader/include)

find_package(OpenGL REQUIRED)

if(ASSIMP_FOUND)
    include_directories(${ASSIMP_INCLUDE_DIR})
endif()


if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_compile_options(-fprofile-instr-generate -fcoverage-mapping)
    add_link_options(-fprofile-instr-generate)
    #Uncomment in case of linker errors
    #link_libraries(clang_rt.profile-x86_64)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_compile_options(--coverage)
    #Uncomment in case of linker errors
    #if(WIN32)
        link_libraries(gcov)
    #endif()
endif ()

if (WIN32)
    if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:preprocessor")
    endif()
endif()


if(
        NOT $ENV{VULKAN_SDK} STREQUAL "" AND
        NOT $ENV{LD_LIBRARY_PATH} STREQUAL "" AND
        NOT $ENV{VK_LAYER_PATH} STREQUAL ""
)

    include_directories( $ENV{VULKAN_SDK}/include )

    message(-- LOCAL_VULKAN_PATH :   $ENV{VULKAN_SDK} )
    message(-- LOCAL_VULKAN_LIBS :   $ENV{LD_LIBRARY_PATH} )

    set(VK_LD_ITEM vulkan)

else()

    find_package(Vulkan)
    if(Vulkan_FOUND)
        include_directories( ${Vulkan_INCLUDE_DIRS} )

        message(-- VULKAN_PATH :   ${Vulkan_LIBRARY} )

        set(VK_LD_ITEM Vulkan::Vulkan)

    endif()

endif()

set (CMAKE_EXPORT_COMPILE_COMMANDS 1)

set(
        C_ENG_SRC_VARIANT_STANDALONE
        src/engine_v6/src/variant_standalone/TargetStandalone.cpp
        src/engine_v6/src/variant_standalone/TargetConfig.hpp
        src/engine_v6/test/base/shared/LoggerShared.hpp)

file(
        GLOB_RECURSE
        C_ENG_SRC_BASE
        "src/engine_v6/src/base/*.cpp"
)

file(
        GLOB_RECURSE
        C_ENG_SRC_API
        "src/engine_v6/src/api/*.cpp"
)

add_executable(
        Binary.Standalone

        ${C_ENG_SRC_BASE}
        ${C_ENG_SRC_API}
        ${C_ENG_SRC_VARIANT_STANDALONE}
)

target_include_directories(
        Binary.Standalone PRIVATE
        src/engine_v6/src/base
        src/engine_v6/src/api
        src/engine_v6/src/variant_standalone
        src/engine_v6/src/api
)

target_link_libraries(
        Binary.Standalone

        glfw
        ${VK_LD_ITEM}
        ${GLFW_LIBRARIES}
)

add_library(
        StaticLib.EngLoggerEnabled STATIC
        ${C_ENG_SRC_BASE}
        ${C_ENG_SRC_API}
)

target_include_directories(
        StaticLib.EngLoggerEnabled PRIVATE
        src/engine_v6/src/base
        src/engine_v6/src/api
        src/engine_v6/test/shared/LoggerEnabled
)

add_library(
        StaticLib.EngLoggerDisabled STATIC
        ${C_ENG_SRC_BASE}
        ${C_ENG_SRC_API}
)

target_include_directories(
        StaticLib.EngLoggerDisabled PRIVATE
        src/engine_v6/src/base
        src/engine_v6/src/api
        src/engine_v6/test/shared/LoggerDisabled
)

enable_testing()

function(c_eng_test path name libs)
    file(GLOB ${name}_src "src/engine_v6/test/${path}/${name}/*.cpp")
    add_executable(
            TestBinary.${name}
            src/engine_v6/test/Test.hpp
            src/engine_v6/test/SingleTest.cpp
            ${${name}_src}
    )
    target_include_directories(
            TestBinary.${name} PRIVATE
            src/engine_v6/src/base
            src/engine_v6/src/api
            src/engine_v6/src/api
            src/engine_v6/test
            src/engine_v6/test/${path}/${name}
    )
    target_link_libraries(TestBinary.${name} ${libs})
    add_test(NAME Test.${name} COMMAND $<TARGET_FILE:TestBinary.${name}>)
endfunction()

add_library(TestStaticLib.GlfwErrorHandlingStub STATIC src/engine_v6/test/api/glfw/Api.Glfw.ErrorHandling/glfw_stub.c)
target_include_directories(TestStaticLib.GlfwErrorHandlingStub PRIVATE dependencies/glfw/include)

set(GLFW_L_ENA StaticLib.EngLoggerEnabled glfw)
set(GLFW_L_DIS StaticLib.EngLoggerDisabled glfw)
set(GLFW_STUB_L_ENA StaticLib.EngLoggerEnabled TestStaticLib.GlfwErrorHandlingStub)

c_eng_test(base Engine "${GLFW_L_ENA}")
c_eng_test(base LoggerDisabled "${GLFW_L_DIS}")
c_eng_test(base LoggerDisabled.Naming "${GLFW_L_DIS}")
c_eng_test(base LoggerDisabled.MultiOut "${GLFW_L_DIS}")
c_eng_test(base LoggerDisabled.Filter "${GLFW_L_DIS}")
c_eng_test(base LoggerEnabled "${GLFW_L_ENA}")
c_eng_test(base LoggerEnabled.Naming "${GLFW_L_ENA}")
c_eng_test(base LoggerEnabled.MultiOut "${GLFW_L_ENA}")
c_eng_test(base LoggerEnabled.Filter "${GLFW_L_ENA}")
c_eng_test(base Object.Hierarchy "${GLFW_L_ENA}")
c_eng_test(base ResourceTracker "${GLFW_L_ENA}")
c_eng_test(base FlagEnum "${GLFW_L_ENA}")

c_eng_test(base Api "${GLFW_L_ENA}")
c_eng_test(base Api.Component.TestApiComponents "${GLFW_L_ENA}")
c_eng_test(base Api.Component.Audio "${GLFW_L_ENA}")
c_eng_test(base Api.Component.Controller "${GLFW_L_ENA}")
c_eng_test(base Api.Component.Keyboard "${GLFW_L_ENA}")
c_eng_test(base Api.Component.Mouse "${GLFW_L_ENA}")
c_eng_test(base Api.Component.Present "${GLFW_L_ENA}")
c_eng_test(base Api.Component.Render "${GLFW_L_ENA}")
c_eng_test(base Api.Component.System "${GLFW_L_ENA}")

c_eng_test(utils TimeoutTest "")
c_eng_test(utils CrashTest "")

c_eng_test(api/glfw Api.Glfw "${GLFW_L_ENA}")
c_eng_test(api/glfw Api.Glfw.ErrorHandling "${GLFW_STUB_L_ENA}")

c_eng_test(api/unix Api.Unix "${GLFW_L_ENA}")
c_eng_test(apI/unix Api.Unix.Component.System "${GLFW_L_ENA}")

c_eng_test(variant Standalone "")
