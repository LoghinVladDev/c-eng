cmake_minimum_required(VERSION 3.5)
project(eng1)

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
            src/engine/obj/util/proto/VulkanTriangleApplication.h
            src/engine/obj/util/proto/VulkanInitTests.cpp
            src/engine/obj/util/proto/VulkanInitTests.h
            src/engine/vulkan/engineVulkanPreproc.h
            src/engine/vulkan/vkDefs/types/vulkanExplicitTypes.h
            src/engine/vulkan/vkDefs/vkDefinitions.h
            src/engine/vulkan/vkObj/instance/validationLayer/VValidationLayer.cpp
            src/engine/vulkan/vkObj/instance/validationLayer/VValidationLayer.h
            src/engine/vulkan/vkObj/instance/VInstance.cpp
            src/engine/vulkan/vkObj/instance/VInstance.h
            src/engine/vulkan/vkObj/instance/messenger/VMessenger.cpp
            src/engine/vulkan/vkObj/instance/messenger/VMessenger.h
            src/engine/vulkan/vkObj/instance/extension/VExtension.cpp
            src/engine/vulkan/vkObj/instance/extension/VExtension.h
            src/engine/vulkan/vkUtils/VStdUtils.cpp
            src/engine/vulkan/vkUtils/VStdUtils.h
            src/engine/vulkan/vkUtils/VStdUtilsDefs.h
            src/engine/vulkan/vkObj/instance/device/VPhysicalDevice.cpp
            src/engine/vulkan/vkObj/instance/device/VPhysicalDevice.h
            src/engine/vulkan/vkObj/instance/device/VPhysicalDeviceDefs.h
            src/engine/vulkan/vkObj/instance/device/queue/VQueueFamily.cpp
            src/engine/vulkan/vkObj/instance/device/queue/VQueueFamily.h
            src/engine/vulkan/vkObj/instance/device/VLogicalDevice.cpp
            src/engine/vulkan/vkObj/instance/device/VLogicalDevice.h
            src/engine/vulkan/vkObj/instance/device/queue/VQueue.cpp
            src/engine/vulkan/vkObj/instance/device/queue/VQueue.h
            src/engine/vulkan/vkObj/window/surface/VSurface.cpp
            src/engine/vulkan/vkObj/window/surface/VSurface.h
            src/engine/vulkan/vkDefs/types/vkPlatformDefs.cpp
            src/engine/vulkan/vkDefs/types/vulkanShortHandTypes.h
            src/engine/vulkan/vkObj/instance/device/VSwapChainDefs.h
            src/engine/obj/util/settings/SettingsSharedContainer.cpp
            src/engine/obj/util/settings/SettingsSharedContainer.h
            src/engine/obj/util/settings/SettingOption.cpp
            src/engine/obj/util/settings/SettingOption.h
            src/engine/obj/util/settings/SettingOptionGraphics.cpp
            src/engine/obj/util/settings/SettingOptionGraphics.h
            src/engine/vulkan/vkObj/instance/device/VSwapChain.cpp
            src/engine/vulkan/vkObj/instance/device/VSwapChain.h
            src/engine/vulkan/vkObj/instance/pipeline/VImageView.cpp
            src/engine/vulkan/vkObj/instance/pipeline/VImageView.h
            src/engine/vulkan/vkObj/instance/pipeline/shader/VShaderCompiler.cpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/VShaderCompiler.h
            src/engine/vulkan/vkObj/instance/pipeline/shader/VShaderModule.cpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/VShaderModule.h
            src/engine/vulkan/vkObj/instance/pipeline/shader/VShaderModuleDefs.h
            src/engine/vulkan/vkObj/instance/pipeline/VPipeline.cpp
            src/engine/vulkan/vkObj/instance/pipeline/VPipeline.h
            src/engine/vulkan/vkObj/instance/pipeline/VRenderPass.cpp
            src/engine/vulkan/vkObj/instance/pipeline/VRenderPass.h
            src/engine/vulkan/vkObj/instance/pipeline/VFrameBuffer.cpp
            src/engine/vulkan/vkObj/instance/pipeline/VFrameBuffer.h
            src/engine/vulkan/vkObj/instance/pipeline/command/VCommandBuffer.cpp
            src/engine/vulkan/vkObj/instance/pipeline/command/VCommandBuffer.h
            src/engine/vulkan/vkObj/instance/pipeline/command/VCommandPool.cpp
            src/engine/vulkan/vkObj/instance/pipeline/command/VCommandPool.h
            src/engine/vulkan/vkObj/instance/pipeline/synchronization/VSemaphore.cpp
            src/engine/vulkan/vkObj/instance/pipeline/synchronization/VSemaphore.h
            src/engine/vulkan/vkObj/instance/pipeline/synchronization/VFence.cpp
            src/engine/vulkan/vkObj/instance/pipeline/synchronization/VFence.h
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VVertex.cpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VVertex.h
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VVertexBuffer.cpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VVertexBuffer.h
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VBuffer.cpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VBuffer.h
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VStagingBuffer.cpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VStagingBuffer.h
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VIndexBuffer.cpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VIndexBuffer.h
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VUniformBuffer.cpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VUniformBuffer.h
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VDescriptorPool.cpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VDescriptorPool.h
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VDescriptorSet.cpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VDescriptorSet.h
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VTexture.cpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VTexture.h
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VTextureDefs.h
            src/engine/vulkan/vkObj/instance/pipeline/VTextureSampler.cpp
            src/engine/vulkan/vkObj/instance/pipeline/VTextureSampler.h
            src/engine/vulkan/vkObj/instance/pipeline/VDepthBuffer.cpp
            src/engine/vulkan/vkObj/instance/pipeline/VDepthBuffer.h
            src/engine/gobj/transform/VTransform.cpp
            src/engine/gobj/transform/VTransform.h
            src/engine/gobj/model/VMesh.cpp
            src/engine/gobj/model/VMesh.h
            src/engine/gobj/shader/VShader.cpp
            src/engine/gobj/shader/VShader.h
            src/engine/gobj/model/VMeshRenderer.cpp
            src/engine/gobj/model/VMeshRenderer.h
            src/engine/gobj/ecm/VComponent.cpp
            src/engine/gobj/ecm/VComponent.h
            src/engine/gobj/ecm/VEntity.cpp
            src/engine/gobj/ecm/VEntity.h
    )


    set_target_properties(
        vkTriangle
        PROPERTIES 
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/build"
    )

    target_link_libraries( vkTriangle Vulkan::Vulkan )

    target_link_libraries( vkTriangle glfw ${GLFW_LIBRARIES} CDS )

    add_executable( vkPrecompiler
            ${JSONCpp_SOURCE}
            src/engine/app/vulkanPrecompilerTest.cpp
            src/engine/obj/util/proto/VulkanInitTests.cpp
            src/engine/obj/util/proto/VulkanInitTests.h
            src/engine/vulkan/engineVulkanPreproc.h
            src/engine/vulkan/vkDefs/types/vulkanExplicitTypes.h
            src/engine/vulkan/vkDefs/vkDefinitions.h
            src/engine/vulkan/vkObj/instance/validationLayer/VValidationLayer.cpp
            src/engine/vulkan/vkObj/instance/validationLayer/VValidationLayer.h
            src/engine/vulkan/vkObj/instance/VInstance.cpp
            src/engine/vulkan/vkObj/instance/VInstance.h
            src/engine/vulkan/vkObj/instance/messenger/VMessenger.cpp
            src/engine/vulkan/vkObj/instance/messenger/VMessenger.h
            src/engine/vulkan/vkObj/instance/extension/VExtension.cpp
            src/engine/vulkan/vkObj/instance/extension/VExtension.h
            src/engine/vulkan/vkUtils/VStdUtils.cpp
            src/engine/vulkan/vkUtils/VStdUtils.h
            src/engine/vulkan/vkUtils/VStdUtilsDefs.h
            src/engine/vulkan/vkObj/instance/device/VPhysicalDevice.cpp
            src/engine/vulkan/vkObj/instance/device/VPhysicalDevice.h
            src/engine/vulkan/vkObj/instance/device/VPhysicalDeviceDefs.h
            src/engine/vulkan/vkObj/instance/device/queue/VQueueFamily.cpp
            src/engine/vulkan/vkObj/instance/device/queue/VQueueFamily.h
            src/engine/vulkan/vkObj/instance/device/VLogicalDevice.cpp
            src/engine/vulkan/vkObj/instance/device/VLogicalDevice.h
            src/engine/vulkan/vkObj/instance/device/queue/VQueue.cpp
            src/engine/vulkan/vkObj/instance/device/queue/VQueue.h
            src/engine/vulkan/vkObj/window/surface/VSurface.cpp
            src/engine/vulkan/vkObj/window/surface/VSurface.h
            src/engine/vulkan/vkDefs/types/vkPlatformDefs.cpp
            src/engine/vulkan/vkDefs/types/vulkanShortHandTypes.h
            src/engine/vulkan/vkObj/instance/device/VSwapChainDefs.h
            src/engine/obj/util/settings/SettingsSharedContainer.cpp
            src/engine/obj/util/settings/SettingsSharedContainer.h
            src/engine/obj/util/settings/SettingOption.cpp
            src/engine/obj/util/settings/SettingOption.h
            src/engine/obj/util/settings/SettingOptionGraphics.cpp
            src/engine/obj/util/settings/SettingOptionGraphics.h
            src/engine/vulkan/vkObj/instance/device/VSwapChain.cpp
            src/engine/vulkan/vkObj/instance/device/VSwapChain.h
            src/engine/vulkan/vkObj/instance/pipeline/VImageView.cpp
            src/engine/vulkan/vkObj/instance/pipeline/VImageView.h
            src/engine/vulkan/vkObj/instance/pipeline/shader/VShaderCompiler.cpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/VShaderCompiler.h
            src/engine/vulkan/vkObj/instance/pipeline/shader/VShaderModule.cpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/VShaderModule.h
    )


    target_link_libraries( vkPrecompiler Vulkan::Vulkan )

    target_link_libraries( vkPrecompiler glfw ${GLFW_LIBRARIES} )


    add_executable (
            vk-eng-sandbox1
            src/engine/app/sandbox/sandbox1.cpp
            src/engine/gobj/ecm/VEntity.cpp
            src/engine/gobj/ecm/VEntity.h
            src/engine/gobj/ecm/VComponent.cpp
            src/engine/gobj/ecm/VComponent.h
            src/engine/gobj/scene/VScene.cpp
            src/engine/gobj/scene/VScene.h
            src/engine/gobj/VGameObject.cpp
            src/engine/gobj/VGameObject.h

            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VBuffer.cpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VBuffer.h
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VVertexBuffer.cpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VVertexBuffer.h
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VIndexBuffer.cpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VIndexBuffer.h
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VTexture.cpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VTexture.h

            src/engine/vulkan/vkObj/instance/device/VLogicalDevice.cpp
            src/engine/vulkan/vkObj/instance/device/VLogicalDevice.h
            src/engine/vulkan/vkObj/instance/device/VPhysicalDevice.cpp
            src/engine/vulkan/vkObj/instance/device/VPhysicalDevice.h

            src/engine/vulkan/vkObj/instance/extension/VExtension.cpp
            src/engine/vulkan/vkObj/instance/extension/VExtension.h

            src/engine/vulkan/vkObj/instance/validationLayer/VValidationLayer.cpp
            src/engine/vulkan/vkObj/instance/validationLayer/VValidationLayer.h

            src/engine/vulkan/vkObj/instance/pipeline/command/VCommandBuffer.cpp
            src/engine/vulkan/vkObj/instance/pipeline/command/VCommandBuffer.h
            src/engine/vulkan/vkObj/instance/pipeline/command/VCommandPool.cpp
            src/engine/vulkan/vkObj/instance/pipeline/command/VCommandPool.h

            src/engine/vulkan/vkObj/instance/pipeline/VImageView.cpp
            src/engine/vulkan/vkObj/instance/pipeline/VImageView.h

            src/engine/vulkan/vkObj/instance/device/queue/VQueue.cpp
            src/engine/vulkan/vkObj/instance/device/queue/VQueueFamily.cpp
            src/engine/vulkan/vkObj/instance/device/queue/VQueue.h
            src/engine/vulkan/vkObj/instance/device/queue/VQueueFamily.h

            src/engine/vulkan/vkObj/instance/device/VSwapChain.cpp
            src/engine/vulkan/vkObj/instance/device/VSwapChain.h

            src/engine/obj/util/settings/SettingOption.cpp
            src/engine/obj/util/settings/SettingOption.h
            src/engine/obj/util/settings/SettingOptionGraphics.cpp
            src/engine/obj/util/settings/SettingOptionGraphics.h
            src/engine/obj/util/settings/SettingsSharedContainer.cpp
            src/engine/obj/util/settings/SettingsSharedContainer.h
    )

    target_compile_definitions(vk-eng-sandbox1 PUBLIC V_TEXTURE_USE_STBI_INDIVIDUAL)

    target_link_libraries (
            vk-eng-sandbox1 ${CDS_LIB}
    )

    target_link_libraries( vk-eng-sandbox1 Vulkan::Vulkan )

    target_link_libraries( vk-eng-sandbox1 glfw ${GLFW_LIBRARIES} )
endif()
