cmake_minimum_required(VERSION 3.5)
project(c-eng)

set(CMAKE_CXX_STANDARD 20)
set(OpenGL_GL_PREFERENCE GLVND)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_subdirectory(dependencies/glfw)
#add_subdirectory(dependencies/glad)
add_subdirectory(dependencies/glm)
#add_subdirectory(dependencies/assimp-5.0.1)
add_subdirectory(dependencies/cds)

#include_directories(dependencies/sqlite-autoconf-3320300)
include_directories(dependencies/glm)
include_directories(dependencies/glfw/include)
#include_directories(dependencies/glad1/include)
include_directories(dependencies/stb)
#include_directories(dependencies/JSONCpp/include)
#include_directories(${PROJECT_BINARY_DIR}/dependencies/glad/include)
include_directories(dependencies/cds/include)

set ( CDS_LIB CDS )

find_package(OpenGL REQUIRED)
#find_package(ASSIMP)

if(SQLite3_FOUND)
    include_directories(${SQLite3_INCLUDE_DIRS})
endif()

if(ASSIMP_FOUND)
    include_directories(${ASSIMP_INCLUDE_DIR})
endif()


#if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
#    add_compile_options(-fprofile-instr-generate -fcoverage-mapping)
#    add_link_options(-fprofile-instr-generate)
#elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
#    add_compile_options(--coverage)
#    link_libraries(gcov)
#endif()


# VULKAN extension


include_directories(src/engine)

find_package(Vulkan)

if(Vulkan_FOUND)
    include_directories(src/engine)
    include_directories(src/engine/obj)
    include_directories(src/engine/vulkan)
    include_directories(src/engine/vulkan/vkDefs)
    include_directories(src/engine/vulkan/vkDefs/types)
    include_directories(src/engine/vulkan/vkObj/instance)
    include_directories(src/engine/vulkan/vkObj/instance/device)
    include_directories(src/engine/vulkan/vkObj/instance/device/queue)
    include_directories(src/engine/vulkan/vkObj/instance/extension)
    include_directories(src/engine/vulkan/vkObj/instance/messenger)
    include_directories(src/engine/vulkan/vkObj/instance/validationLayer)
    include_directories(src/engine/vulkan/vkObj/instance/pipeline)
    include_directories(src/engine/vulkan/vkObj/instance/pipeline/command)
    include_directories(src/engine/vulkan/vkObj/instance/pipeline/shader)
    include_directories(src/engine/vulkan/vkObj/instance/pipeline/shader/input)
    include_directories(src/engine/vulkan/vkObj/instance/pipeline/synchronization)
    include_directories(src/engine/vulkan/vkObj/window/surface)
    include_directories(src/engine/vulkan/vkObj/engine)
    include_directories(src/engine/vulkan/vkObj/engine/obj)
    include_directories(src/engine/gobj/space)
    include_directories(src/engine/gobj)
    include_directories(src/engine/vulkan/vkUtils)
    include_directories(src/engine/obj/util/settings)
    include_directories(src/engine/obj/util/proto)
    include_directories(src/engine/app)

    include_directories( ${Vulkan_INCLUDE_DIRS} )

    message(-- VULKAN_PATH :   ${Vulkan_LIBRARY} )

    add_executable( vkTriangle
#            dependencies/cds/src/primitive/String.cpp
            src/engine/app/vulkanTriangle.cpp
            src/engine/obj/util/proto/VulkanTriangleApplication.cpp
            src/engine/obj/util/proto/VulkanTriangleApplication.hpp
            src/engine/obj/util/proto/VulkanInitTests.cpp
            src/engine/obj/util/proto/VulkanInitTests.hpp
            src/engine/vulkan/engineVulkanPreproc.hpp
            src/engine/vulkan/vkDefs/types/vulkanExplicitTypes.h
            src/engine/vulkan/vkDefs/vkDefinitions.h
            src/engine/vulkan/vkObj/instance/validationLayer/VValidationLayer.cpp
            src/engine/vulkan/vkObj/instance/validationLayer/VValidationLayer.hpp
            src/engine/vulkan/vkObj/instance/VInstance.cpp
            src/engine/vulkan/vkObj/instance/VInstance.hpp
            src/engine/vulkan/vkObj/instance/messenger/VMessenger.cpp
            src/engine/vulkan/vkObj/instance/messenger/VMessenger.hpp
            src/engine/vulkan/vkObj/instance/extension/VExtension.cpp
            src/engine/vulkan/vkObj/instance/extension/VExtension.hpp
            src/engine/vulkan/vkUtils/VStdUtils.cpp
            src/engine/vulkan/vkUtils/VStdUtils.hpp
            src/engine/vulkan/vkUtils/VStdUtilsDefs.h
            src/engine/vulkan/vkObj/instance/device/VPhysicalDevice.cpp
            src/engine/vulkan/vkObj/instance/device/VPhysicalDevice.hpp
            src/engine/vulkan/vkObj/instance/device/VPhysicalDeviceDefs.h
            src/engine/vulkan/vkObj/instance/device/queue/VQueueFamily.cpp
            src/engine/vulkan/vkObj/instance/device/queue/VQueueFamily.hpp
            src/engine/vulkan/vkObj/instance/device/VLogicalDevice.cpp
            src/engine/vulkan/vkObj/instance/device/VLogicalDevice.hpp
            src/engine/vulkan/vkObj/instance/device/queue/VQueue.cpp
            src/engine/vulkan/vkObj/instance/device/queue/VQueue.hpp
            src/engine/vulkan/vkObj/window/surface/VSurface.cpp
            src/engine/vulkan/vkObj/window/surface/VSurface.hpp
            src/engine/vulkan/vkDefs/types/vkPlatformDefs.cpp
            src/engine/vulkan/vkDefs/types/vulkanShortHandTypes.hpp
            src/engine/vulkan/vkObj/instance/device/VSwapChainDefs.h
            src/engine/obj/util/settings/SettingsSharedContainer.cpp
            src/engine/obj/util/settings/SettingsSharedContainer.hpp
            src/engine/obj/util/settings/SettingOption.cpp
            src/engine/obj/util/settings/SettingOption.hpp
            src/engine/obj/util/settings/SettingOptionGraphics.cpp
            src/engine/obj/util/settings/SettingOptionGraphics.hpp
            src/engine/vulkan/vkObj/instance/device/VSwapChain.cpp
            src/engine/vulkan/vkObj/instance/device/VSwapChain.hpp
            src/engine/vulkan/vkObj/instance/pipeline/VImageView.cpp
            src/engine/vulkan/vkObj/instance/pipeline/VImageView.hpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/VShaderCompiler.cpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/VShaderCompiler.hpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/VShaderModule.cpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/VShaderModule.hpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/VShaderModuleDefs.h
            src/engine/vulkan/vkObj/instance/pipeline/VPipeline.cpp
            src/engine/vulkan/vkObj/instance/pipeline/VPipeline.hpp
            src/engine/vulkan/vkObj/instance/pipeline/VRenderPass.cpp
            src/engine/vulkan/vkObj/instance/pipeline/VRenderPass.hpp
            src/engine/vulkan/vkObj/instance/pipeline/VFrameBuffer.cpp
            src/engine/vulkan/vkObj/instance/pipeline/VFrameBuffer.hpp
            src/engine/vulkan/vkObj/instance/pipeline/command/VCommandBuffer.cpp
            src/engine/vulkan/vkObj/instance/pipeline/command/VCommandBuffer.hpp
            src/engine/vulkan/vkObj/instance/pipeline/command/VCommandPool.cpp
            src/engine/vulkan/vkObj/instance/pipeline/command/VCommandPool.hpp
            src/engine/vulkan/vkObj/instance/pipeline/synchronization/VSemaphore.cpp
            src/engine/vulkan/vkObj/instance/pipeline/synchronization/VSemaphore.hpp
            src/engine/vulkan/vkObj/instance/pipeline/synchronization/VFence.cpp
            src/engine/vulkan/vkObj/instance/pipeline/synchronization/VFence.hpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VVertex.cpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VVertex.hpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VVertexBuffer.cpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VVertexBuffer.hpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VBuffer.cpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VBuffer.hpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VStagingBuffer.cpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VStagingBuffer.hpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VIndexBuffer.cpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VIndexBuffer.hpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VUniformBuffer.cpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VUniformBuffer.hpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VDescriptorPool.cpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VDescriptorPool.hpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VDescriptorSet.cpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VDescriptorSet.hpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VTexture.cpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VTexture.hpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VTextureDefs.h
            src/engine/vulkan/vkObj/instance/pipeline/VTextureSampler.cpp
            src/engine/vulkan/vkObj/instance/pipeline/VTextureSampler.hpp
            src/engine/vulkan/vkObj/instance/pipeline/VDepthBuffer.cpp
            src/engine/vulkan/vkObj/instance/pipeline/VDepthBuffer.hpp
            src/engine/gobj/transform/VTransform.cpp
            src/engine/gobj/transform/VTransform.hpp
            src/engine/gobj/model/VMesh.cpp
            src/engine/gobj/model/VMesh.hpp
            src/engine/gobj/shader/VShader.cpp
            src/engine/gobj/shader/VShader.hpp
            src/engine/gobj/model/VMeshRenderer.cpp
            src/engine/gobj/model/VMeshRenderer.hpp
            src/engine/gobj/ecm/VComponent.cpp
            src/engine/gobj/ecm/VComponent.hpp
            src/engine/gobj/ecm/VEntity.cpp
            src/engine/gobj/ecm/VEntity.hpp

            src/engine/gobj/VGameObject.cpp
            src/engine/gobj/VGameObject.hpp

            src/engine/gobj/scene/VScene.cpp
            src/engine/gobj/scene/VScene.hpp
    )


    set_target_properties(
        vkTriangle
        PROPERTIES 
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/build"
    )

    target_link_libraries( vkTriangle Vulkan::Vulkan )

    target_link_libraries( vkTriangle glfw ${GLFW_LIBRARIES} )

    add_executable( vkPrecompiler
            ${JSONCpp_SOURCE}
            src/engine/app/vulkanPrecompilerTest.cpp
            src/engine/obj/util/proto/VulkanInitTests.cpp
            src/engine/obj/util/proto/VulkanInitTests.hpp
            src/engine/vulkan/engineVulkanPreproc.hpp
            src/engine/vulkan/vkDefs/types/vulkanExplicitTypes.h
            src/engine/vulkan/vkDefs/vkDefinitions.h
            src/engine/vulkan/vkObj/instance/validationLayer/VValidationLayer.cpp
            src/engine/vulkan/vkObj/instance/validationLayer/VValidationLayer.hpp
            src/engine/vulkan/vkObj/instance/VInstance.cpp
            src/engine/vulkan/vkObj/instance/VInstance.hpp
            src/engine/vulkan/vkObj/instance/messenger/VMessenger.cpp
            src/engine/vulkan/vkObj/instance/messenger/VMessenger.hpp
            src/engine/vulkan/vkObj/instance/extension/VExtension.cpp
            src/engine/vulkan/vkObj/instance/extension/VExtension.hpp
            src/engine/vulkan/vkUtils/VStdUtils.cpp
            src/engine/vulkan/vkUtils/VStdUtils.hpp
            src/engine/vulkan/vkUtils/VStdUtilsDefs.h
            src/engine/vulkan/vkObj/instance/device/VPhysicalDevice.cpp
            src/engine/vulkan/vkObj/instance/device/VPhysicalDevice.hpp
            src/engine/vulkan/vkObj/instance/device/VPhysicalDeviceDefs.h
            src/engine/vulkan/vkObj/instance/device/queue/VQueueFamily.cpp
            src/engine/vulkan/vkObj/instance/device/queue/VQueueFamily.hpp
            src/engine/vulkan/vkObj/instance/device/VLogicalDevice.cpp
            src/engine/vulkan/vkObj/instance/device/VLogicalDevice.hpp
            src/engine/vulkan/vkObj/instance/device/queue/VQueue.cpp
            src/engine/vulkan/vkObj/instance/device/queue/VQueue.hpp
            src/engine/vulkan/vkObj/window/surface/VSurface.cpp
            src/engine/vulkan/vkObj/window/surface/VSurface.hpp
            src/engine/vulkan/vkDefs/types/vkPlatformDefs.cpp
            src/engine/vulkan/vkDefs/types/vulkanShortHandTypes.hpp
            src/engine/vulkan/vkObj/instance/device/VSwapChainDefs.h
            src/engine/obj/util/settings/SettingsSharedContainer.cpp
            src/engine/obj/util/settings/SettingsSharedContainer.hpp
            src/engine/obj/util/settings/SettingOption.cpp
            src/engine/obj/util/settings/SettingOption.hpp
            src/engine/obj/util/settings/SettingOptionGraphics.cpp
            src/engine/obj/util/settings/SettingOptionGraphics.hpp
            src/engine/vulkan/vkObj/instance/device/VSwapChain.cpp
            src/engine/vulkan/vkObj/instance/device/VSwapChain.hpp
            src/engine/vulkan/vkObj/instance/pipeline/VImageView.cpp
            src/engine/vulkan/vkObj/instance/pipeline/VImageView.hpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/VShaderCompiler.cpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/VShaderCompiler.hpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/VShaderModule.cpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/VShaderModule.hpp
    )


    target_link_libraries( vkPrecompiler Vulkan::Vulkan )

    target_link_libraries( vkPrecompiler glfw ${GLFW_LIBRARIES} )


    add_executable (
            vk-eng-sandbox1
            src/engine/app/sandbox/sandbox1.cpp
            src/engine/gobj/ecm/VEntity.cpp
            src/engine/gobj/ecm/VEntity.hpp
            src/engine/gobj/ecm/VComponent.cpp
            src/engine/gobj/ecm/VComponent.hpp
            src/engine/gobj/scene/VScene.cpp
            src/engine/gobj/scene/VScene.hpp
            src/engine/gobj/VGameObject.cpp
            src/engine/gobj/VGameObject.hpp

            src/engine/gobj/transform/VTransform.cpp
            src/engine/gobj/transform/VTransform.hpp

            src/engine/gobj/model/VMesh.cpp
            src/engine/gobj/model/VMesh.hpp
            src/engine/gobj/model/VMeshRenderer.cpp
            src/engine/gobj/model/VMeshRenderer.hpp

            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VBuffer.cpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VBuffer.hpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VVertexBuffer.cpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VVertexBuffer.hpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VIndexBuffer.cpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VIndexBuffer.hpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VTexture.cpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VTexture.hpp

            src/engine/vulkan/vkObj/instance/device/VLogicalDevice.cpp
            src/engine/vulkan/vkObj/instance/device/VLogicalDevice.hpp
            src/engine/vulkan/vkObj/instance/device/VPhysicalDevice.cpp
            src/engine/vulkan/vkObj/instance/device/VPhysicalDevice.hpp

            src/engine/vulkan/vkObj/instance/extension/VExtension.cpp
            src/engine/vulkan/vkObj/instance/extension/VExtension.hpp

            src/engine/vulkan/vkObj/instance/validationLayer/VValidationLayer.cpp
            src/engine/vulkan/vkObj/instance/validationLayer/VValidationLayer.hpp

            src/engine/vulkan/vkObj/instance/pipeline/command/VCommandBuffer.cpp
            src/engine/vulkan/vkObj/instance/pipeline/command/VCommandBuffer.hpp
            src/engine/vulkan/vkObj/instance/pipeline/command/VCommandPool.cpp
            src/engine/vulkan/vkObj/instance/pipeline/command/VCommandPool.hpp

            src/engine/vulkan/vkObj/instance/pipeline/VImageView.cpp
            src/engine/vulkan/vkObj/instance/pipeline/VImageView.hpp

            src/engine/vulkan/vkObj/instance/device/queue/VQueue.cpp
            src/engine/vulkan/vkObj/instance/device/queue/VQueueFamily.cpp
            src/engine/vulkan/vkObj/instance/device/queue/VQueue.hpp
            src/engine/vulkan/vkObj/instance/device/queue/VQueueFamily.hpp

            src/engine/vulkan/vkObj/instance/device/VSwapChain.cpp
            src/engine/vulkan/vkObj/instance/device/VSwapChain.hpp

            src/engine/obj/util/settings/SettingOption.cpp
            src/engine/obj/util/settings/SettingOption.hpp
            src/engine/obj/util/settings/SettingOptionGraphics.cpp
            src/engine/obj/util/settings/SettingOptionGraphics.hpp
            src/engine/obj/util/settings/SettingsSharedContainer.cpp
            src/engine/obj/util/settings/SettingsSharedContainer.hpp
            src/engine/gobj/VCamera.cpp src/engine/gobj/VCamera.hpp)

    target_compile_definitions(vk-eng-sandbox1 PUBLIC V_TEXTURE_USE_STBI_INDIVIDUAL)

    target_link_libraries (
            vk-eng-sandbox1 ${CDS_LIB}
    )

    target_link_libraries( vk-eng-sandbox1 Vulkan::Vulkan )

    target_link_libraries( vk-eng-sandbox1 glfw ${GLFW_LIBRARIES} )
endif()
