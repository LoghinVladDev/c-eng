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
add_subdirectory(dependencies/glm)
add_subdirectory(dependencies/cds)

include_directories(dependencies/glm)
include_directories(dependencies/glfw/include)
include_directories(dependencies/stb)
include_directories(dependencies/cds/include)

set ( CDS_LIB CDS )

find_package(OpenGL REQUIRED)

if(SQLite3_FOUND)
    include_directories(${SQLite3_INCLUDE_DIRS})
endif()

if(ASSIMP_FOUND)
    include_directories(${ASSIMP_INCLUDE_DIR})
endif()



# VULKAN extension


include_directories(src/engine)

find_package(Vulkan)

if(Vulkan_FOUND)
    include_directories(src/engine)
    include_directories(src/engine/obj)
    include_directories(src/engine/vulkan)
    include_directories(src/engine/vulkan/vkDefs)
    include_directories(src/engine/vulkan/vkDefs/types)
    include_directories(src/engine/vulkan/vkObj)
    include_directories(src/engine/vulkan/vkObj/abstract)
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
    include_directories(src/engine/vulkan/vkUtils)
    include_directories(src/engine/obj/util/settings)
    include_directories(src/engine/obj/util/proto)
    include_directories(src/engine/app)

    include_directories(src/engine/obj/event)
    include_directories(src/engine/obj/event/key)

    include_directories( ${Vulkan_INCLUDE_DIRS} )

    message(-- VULKAN_PATH :   ${Vulkan_LIBRARY} )

    set(
            V_RENDER_DEFINITIONS_TYPES_SRC

            src/engine/vulkan/vkDefs/types/vkPlatformDefs.cpp
            src/engine/vulkan/vkDefs/types/vulkanExplicitTypes.h
            src/engine/vulkan/vkDefs/types/vulkanShortHandTypes.hpp
    )

    set(
            V_RENDER_DEFINITIONS_SRC

            ${V_RENDER_DEFINITIONS_TYPES_SRC}

            src/engine/vulkan/vkDefs/VInstanceDefinitions.h
            src/engine/vulkan/vkDefs/vkDefinitions.h
            src/engine/vulkan/vkDefs/vkPlatformDefs.h
    )

    set(
            V_RENDER_INSTANCE_DEVICE_QUEUE_SRC

            src/engine/vulkan/vkObj/instance/device/queue/VQueue.cpp
            src/engine/vulkan/vkObj/instance/device/queue/VQueue.hpp
            src/engine/vulkan/vkObj/instance/device/queue/VQueueFamily.cpp
            src/engine/vulkan/vkObj/instance/device/queue/VQueueFamily.hpp
    )

    set(
            V_RENDER_INSTANCE_DEVICE_SRC

            ${V_RENDER_INSTANCE_DEVICE_QUEUE_SRC}

            src/engine/vulkan/vkObj/instance/device/VLogicalDevice.cpp
            src/engine/vulkan/vkObj/instance/device/VLogicalDevice.hpp
            src/engine/vulkan/vkObj/instance/device/VPhysicalDevice.cpp
            src/engine/vulkan/vkObj/instance/device/VPhysicalDevice.hpp
            src/engine/vulkan/vkObj/instance/device/VPhysicalDeviceDefs.h
            src/engine/vulkan/vkObj/instance/device/VSwapChain.cpp
            src/engine/vulkan/vkObj/instance/device/VSwapChain.hpp
            src/engine/vulkan/vkObj/instance/device/VSwapChainDefs.h
    )

    set(
            V_RENDER_INSTANCE_EXTENSION_SRC

            src/engine/vulkan/vkObj/instance/extension/VExtension.cpp
            src/engine/vulkan/vkObj/instance/extension/VExtension.hpp
            src/engine/vulkan/vkObj/instance/extension/VExtensionDefs.h
    )

    set(
            V_RENDER_INSTANCE_DEBUG_MESSENGER_SRC

            src/engine/vulkan/vkObj/instance/messenger/VMessenger.cpp
            src/engine/vulkan/vkObj/instance/messenger/VMessenger.hpp
    )

    set(
            V_RENDER_INSTANCE_PIPELINE_COMMAND_SRC

            src/engine/vulkan/vkObj/instance/pipeline/command/VCommandBuffer.cpp
            src/engine/vulkan/vkObj/instance/pipeline/command/VCommandBuffer.hpp
            src/engine/vulkan/vkObj/instance/pipeline/command/VCommandPool.cpp
            src/engine/vulkan/vkObj/instance/pipeline/command/VCommandPool.hpp
    )

    set(
            V_RENDER_INSTANCE_PIPELINE_SHADER_INPUT_SRC

            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VBuffer.cpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VBuffer.hpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VDescriptorPool.cpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VDescriptorPool.hpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VDescriptorSet.cpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VDescriptorSet.hpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VIndexBuffer.cpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VIndexBuffer.hpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VStagingBuffer.cpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VStagingBuffer.hpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VTexture.cpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VTexture.hpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VTextureDefs.h
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VUniformBuffer.cpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VUniformBuffer.hpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VVertex.cpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VVertex.hpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VVertexBuffer.cpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/input/VVertexBuffer.hpp
    )

    set(
            V_RENDER_INSTANCE_PIPELINE_SHADER_SRC

            ${V_RENDER_INSTANCE_PIPELINE_SHADER_INPUT_SRC}

            src/engine/vulkan/vkObj/instance/pipeline/shader/VShaderCompiler.cpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/VShaderCompiler.hpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/VShaderModule.cpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/VShaderModule.hpp
            src/engine/vulkan/vkObj/instance/pipeline/shader/VShaderModuleDefs.h
    )

    set(
            V_RENDER_INSTANCE_PIPELINE_SYNCHRONIZATION_SRC

            src/engine/vulkan/vkObj/instance/pipeline/synchronization/VFence.cpp
            src/engine/vulkan/vkObj/instance/pipeline/synchronization/VFence.hpp
            src/engine/vulkan/vkObj/instance/pipeline/synchronization/VSemaphore.cpp
            src/engine/vulkan/vkObj/instance/pipeline/synchronization/VSemaphore.hpp
    )

    set(
            V_RENDER_INSTANCE_PIPELINE_SRC

            ${V_RENDER_INSTANCE_PIPELINE_COMMAND_SRC}
            ${V_RENDER_INSTANCE_PIPELINE_SHADER_SRC}
            ${V_RENDER_INSTANCE_PIPELINE_SYNCHRONIZATION_SRC}

            src/engine/vulkan/vkObj/instance/pipeline/VDepthBuffer.cpp
            src/engine/vulkan/vkObj/instance/pipeline/VDepthBuffer.hpp
            src/engine/vulkan/vkObj/instance/pipeline/VFrameBuffer.cpp
            src/engine/vulkan/vkObj/instance/pipeline/VFrameBuffer.hpp
            src/engine/vulkan/vkObj/instance/pipeline/VImageView.cpp
            src/engine/vulkan/vkObj/instance/pipeline/VImageView.hpp
            src/engine/vulkan/vkObj/instance/pipeline/VPipeline.cpp
            src/engine/vulkan/vkObj/instance/pipeline/VPipeline.hpp
            src/engine/vulkan/vkObj/instance/pipeline/VRenderPass.cpp
            src/engine/vulkan/vkObj/instance/pipeline/VRenderPass.hpp
            src/engine/vulkan/vkObj/instance/pipeline/VTextureSampler.cpp
            src/engine/vulkan/vkObj/instance/pipeline/VTextureSampler.hpp
    )

    set(
            V_RENDER_INSTANCE_VALIDATION_LAYER_SRC

            src/engine/vulkan/vkObj/instance/validationLayer/VValidationLayer.cpp
            src/engine/vulkan/vkObj/instance/validationLayer/VValidationLayer.hpp
    )

    set(
            V_RENDER_INSTANCE_SRC

            ${V_RENDER_INSTANCE_DEVICE_SRC}
            ${V_RENDER_INSTANCE_EXTENSION_SRC}
            ${V_RENDER_INSTANCE_DEBUG_MESSENGER_SRC}
            ${V_RENDER_INSTANCE_PIPELINE_SRC}
            ${V_RENDER_INSTANCE_VALIDATION_LAYER_SRC}

            src/engine/vulkan/vkObj/instance/VInstance.cpp
            src/engine/vulkan/vkObj/instance/VInstance.hpp
    )

    set(
            V_RENDER_WINDOW_SURFACE_SRC

            src/engine/vulkan/vkObj/window/surface/VSurface.cpp
            src/engine/vulkan/vkObj/window/surface/VSurface.hpp
    )

    set(
            V_RENDER_WINDOW_SRC

            ${V_RENDER_WINDOW_SURFACE_SRC}
    )

    set(
            V_RENDER_OBJECT_SRC

            ${V_RENDER_INSTANCE_SRC}
            ${V_RENDER_WINDOW_SRC}

            src/engine/vulkan/vkObj/VRenderObject.cpp
            src/engine/vulkan/vkObj/VRenderObject.hpp
    )

    set(
            V_RENDER_UTILS_SRC

            src/engine/vulkan/vkUtils/VStdUtils.cpp
            src/engine/vulkan/vkUtils/VStdUtils.hpp
            src/engine/vulkan/vkUtils/VStdUtilsDefs.h
    )

    set(
            V_RENDER_SRC

            ${V_RENDER_DEFINITIONS_SRC}
            ${V_RENDER_OBJECT_SRC}
            ${V_RENDER_UTILS_SRC}

            src/engine/vulkan/engineVulkanPreproc.hpp
    )

    set(
            V_ENGINE_OBJECT_ENTITY_COMPONENT_MODEL_SRC

            src/engine/obj/ecm/VComponent.cpp
            src/engine/obj/ecm/VComponent.hpp
            src/engine/obj/ecm/VEntity.cpp
            src/engine/obj/ecm/VEntity.hpp
    )

    set(
            V_ENGINE_OBJECT_EVENT_KEY_SRC

            src/engine/obj/event/key/VKeyEvent.cpp
            src/engine/obj/event/key/VKeyEvent.hpp
    )

    set(
            V_ENGINE_OBJECT_EVENT_SRC

            ${V_ENGINE_OBJECT_EVENT_KEY_SRC}

            src/engine/obj/event/VEvent.cpp
            src/engine/obj/event/VEvent.hpp
    )

    set(
            V_ENGINE_OBJECT_MESH_SRC

            src/engine/obj/model/VMesh.cpp
            src/engine/obj/model/VMesh.hpp
            src/engine/obj/model/VMeshRenderer.cpp
            src/engine/obj/model/VMeshRenderer.hpp
    )

    set(
            V_ENGINE_OBJECT_SCENE_SRC

            src/engine/obj/scene/VScene.cpp
            src/engine/obj/scene/VScene.hpp
    )

    set(
            V_ENGINE_OBJECT_SHADER_SRC

            src/engine/obj/shader/VShader.cpp
            src/engine/obj/shader/VShader.hpp
    )

    set(
            V_ENGINE_OBJECT_TRANSFORM_SRC

            src/engine/obj/transform/VRotor.cpp
            src/engine/obj/transform/VRotor.hpp
            src/engine/obj/transform/VTransform.cpp
            src/engine/obj/transform/VTransform.hpp
    )

    set(
            V_ENGINE_OBJECT_UTILITY_PROTOTYPE_SRC

            src/engine/obj/util/proto/VulkanInitTests.cpp
            src/engine/obj/util/proto/VulkanInitTests.hpp
            src/engine/obj/util/proto/VulkanTriangleApplication.cpp
            src/engine/obj/util/proto/VulkanTriangleApplication.hpp
    )

    set(
            V_ENGINE_OBJECT_UTILITY_SETTINGS_SRC

            src/engine/obj/util/settings/VSettingOption.cpp
            src/engine/obj/util/settings/VSettingOption.hpp
            src/engine/obj/util/settings/SettingOptionGraphics.cpp
            src/engine/obj/util/settings/SettingOptionGraphics.hpp
            src/engine/obj/util/settings/SettingsSharedContainer.cpp
            src/engine/obj/util/settings/SettingsSharedContainer.hpp
    )

    set(
            V_ENGINE_OBJECT_UTILITY_SRC

            ${V_ENGINE_OBJECT_UTILITY_PROTOTYPE_SRC}
            ${V_ENGINE_OBJECT_UTILITY_SETTINGS_SRC}
    )

    set(
            V_ENGINE_OBJECT_LOADER_SRC

            src/engine/obj/tools/loader/VMeshLoader.cpp
            src/engine/obj/tools/loader/VMeshLoader.hpp
    )

    set(
            V_ENGINE_OBJECT_TOOLS_SRC

            ${V_ENGINE_OBJECT_LOADER_SRC}
    )

    set(
            V_ENGINE_OBJECT_SRC

            ${V_ENGINE_OBJECT_ENTITY_COMPONENT_MODEL_SRC}
            ${V_ENGINE_OBJECT_EVENT_SRC}
            ${V_ENGINE_OBJECT_MESH_SRC}
            ${V_ENGINE_OBJECT_SCENE_SRC}
            ${V_ENGINE_OBJECT_SHADER_SRC}
            ${V_ENGINE_OBJECT_TRANSFORM_SRC}
            ${V_ENGINE_OBJECT_UTILITY_SRC}
            ${V_ENGINE_OBJECT_TOOLS_SRC}

            src/engine/obj/VCamera.cpp
            src/engine/obj/VCamera.hpp
            src/engine/obj/VGameObject.cpp
            src/engine/obj/VGameObject.hpp
            src/engine/obj/VObject.cpp
            src/engine/obj/VObject.hpp
    )

    set(
            V_ENGINE_SRC

            ${V_RENDER_SRC}
            ${V_ENGINE_OBJECT_SRC}

            src/engine/dataTypes.h
            src/engine/engineDataPaths.h
    )

    add_executable(
            vkTriangle

            ${V_ENGINE_SRC}

            src/engine/app/vulkanTriangle.cpp
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
            src/engine/obj/util/settings/VSettingOption.cpp
            src/engine/obj/util/settings/VSettingOption.hpp
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
            src/engine/obj/ecm/VEntity.cpp
            src/engine/obj/ecm/VEntity.hpp
            src/engine/obj/ecm/VComponent.cpp
            src/engine/obj/ecm/VComponent.hpp
            src/engine/obj/scene/VScene.cpp
            src/engine/obj/scene/VScene.hpp
            src/engine/obj/VGameObject.cpp
            src/engine/obj/VGameObject.hpp

            src/engine/obj/transform/VTransform.cpp
            src/engine/obj/transform/VTransform.hpp

            src/engine/obj/model/VMesh.cpp
            src/engine/obj/model/VMesh.hpp
            src/engine/obj/model/VMeshRenderer.cpp
            src/engine/obj/model/VMeshRenderer.hpp

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

            src/engine/obj/util/settings/VSettingOption.cpp
            src/engine/obj/util/settings/VSettingOption.hpp
            src/engine/obj/util/settings/SettingOptionGraphics.cpp
            src/engine/obj/util/settings/SettingOptionGraphics.hpp
            src/engine/obj/util/settings/SettingsSharedContainer.cpp
            src/engine/obj/util/settings/SettingsSharedContainer.hpp
            src/engine/obj/VCamera.cpp src/engine/obj/VCamera.hpp)

    target_compile_definitions(vk-eng-sandbox1 PUBLIC V_TEXTURE_USE_STBI_INDIVIDUAL)

    target_link_libraries (
            vk-eng-sandbox1 ${CDS_LIB}
    )

    target_link_libraries( vk-eng-sandbox1 Vulkan::Vulkan )

    target_link_libraries( vk-eng-sandbox1 glfw ${GLFW_LIBRARIES} )


    ### ENGINE REWORK

    set (
            ENGINE_REWORK_ENGINE_EVENT_CONTROLLER_SOURCES

            src/engineRework/engine/event/controller/ControllerEvent.cpp
            src/engineRework/engine/event/controller/ControllerEvent.hpp

            src/engineRework/engine/event/controller/ControllerAxisEvent.cpp
            src/engineRework/engine/event/controller/ControllerAxisEvent.hpp

            src/engineRework/engine/event/controller/ControllerButtonPressEvent.cpp
            src/engineRework/engine/event/controller/ControllerButtonPressEvent.hpp

            src/engineRework/engine/event/controller/ControllerButtonReleaseEvent.cpp
            src/engineRework/engine/event/controller/ControllerButtonReleaseEvent.hpp

            src/engineRework/engine/event/controller/ControllerConnectEvent.cpp
            src/engineRework/engine/event/controller/ControllerConnectEvent.hpp

            src/engineRework/engine/event/controller/ControllerDisconnectEvent.cpp
            src/engineRework/engine/event/controller/ControllerDisconnectEvent.hpp

            src/engineRework/engine/event/controller/ControllerHatEvent.cpp
            src/engineRework/engine/event/controller/ControllerHatEvent.hpp
    )

    set (
            ENGINE_REWORK_ENGINE_EVENT_KEY_SOURCES

            src/engineRework/engine/event/key/KeyEvent.cpp
            src/engineRework/engine/event/key/KeyEvent.hpp

            src/engineRework/engine/event/key/KeyPressEvent.cpp
            src/engineRework/engine/event/key/KeyPressEvent.hpp

            src/engineRework/engine/event/key/KeyReleaseEvent.cpp
            src/engineRework/engine/event/key/KeyReleaseEvent.hpp
    )

    set (
            ENGINE_REWORK_ENGINE_EVENT_MOUSE_SOURCES

            src/engineRework/engine/event/mouse/MouseEvent.cpp
            src/engineRework/engine/event/mouse/MouseEvent.hpp

            src/engineRework/engine/event/mouse/MouseMoveEvent.cpp
            src/engineRework/engine/event/mouse/MouseMoveEvent.hpp

            src/engineRework/engine/event/mouse/MouseEnterEvent.cpp
            src/engineRework/engine/event/mouse/MouseEnterEvent.hpp

            src/engineRework/engine/event/mouse/MouseLeaveEvent.cpp
            src/engineRework/engine/event/mouse/MouseLeaveEvent.hpp

            src/engineRework/engine/event/mouse/MouseScrollEvent.cpp
            src/engineRework/engine/event/mouse/MouseScrollEvent.hpp

            src/engineRework/engine/event/mouse/MousePressEvent.cpp
            src/engineRework/engine/event/mouse/MousePressEvent.hpp

            src/engineRework/engine/event/mouse/MouseReleaseEvent.cpp
            src/engineRework/engine/event/mouse/MouseReleaseEvent.hpp
    )

    set (
            ENGINE_REWORK_ENGINE_EVENT_WINDOW_SOURCES

            src/engineRework/engine/event/window/WindowEvent.cpp
            src/engineRework/engine/event/window/WindowEvent.hpp

            src/engineRework/engine/event/window/WindowCloseEvent.cpp
            src/engineRework/engine/event/window/WindowCloseEvent.hpp

            src/engineRework/engine/event/window/WindowContentScaleEvent.cpp
            src/engineRework/engine/event/window/WindowContentScaleEvent.hpp

            src/engineRework/engine/event/window/WindowFrameBufferResizeEvent.cpp
            src/engineRework/engine/event/window/WindowFrameBufferResizeEvent.hpp

            src/engineRework/engine/event/window/WindowGainFocusEvent.cpp
            src/engineRework/engine/event/window/WindowGainFocusEvent.hpp

            src/engineRework/engine/event/window/WindowLoseFocusEvent.cpp
            src/engineRework/engine/event/window/WindowLoseFocusEvent.hpp

            src/engineRework/engine/event/window/WindowMaximizeEvent.cpp
            src/engineRework/engine/event/window/WindowMaximizeEvent.cpp

            src/engineRework/engine/event/window/WindowMinimizeEvent.cpp
            src/engineRework/engine/event/window/WindowMinimizeEvent.hpp

            src/engineRework/engine/event/window/WindowMoveEvent.cpp
            src/engineRework/engine/event/window/WindowMoveEvent.hpp

            src/engineRework/engine/event/window/WindowRefreshRequestEvent.cpp
            src/engineRework/engine/event/window/WindowRefreshRequestEvent.hpp

            src/engineRework/engine/event/window/WindowRestoreEvent.cpp
            src/engineRework/engine/event/window/WindowRestoreEvent.hpp

            src/engineRework/engine/event/window/WindowResizeEvent.cpp
            src/engineRework/engine/event/window/WindowResizeEvent.hpp
    )

    set (
            ENGINE_REWORK_ENGINE_EVENT_SOURCES

            ${ENGINE_REWORK_ENGINE_EVENT_CONTROLLER_SOURCES}
            ${ENGINE_REWORK_ENGINE_EVENT_KEY_SOURCES}
            ${ENGINE_REWORK_ENGINE_EVENT_MOUSE_SOURCES}
            ${ENGINE_REWORK_ENGINE_EVENT_WINDOW_SOURCES}

            src/engineRework/engine/event/EventHandler.cpp
            src/engineRework/engine/event/EventHandler.hpp

            src/engineRework/engine/event/Event.hpp
            src/engineRework/engine/event/Event.cpp
    )

    set (
            ENGINE_REWORK_ENGINE_INPUT_CONTROLLER_SOURCES

            src/engineRework/engine/input/controller/Controller.cpp
            src/engineRework/engine/input/controller/Controller.hpp

            src/engineRework/engine/input/controller/Gamepad.cpp
            src/engineRework/engine/input/controller/Gamepad.hpp

            src/engineRework/engine/input/controller/Joystick.cpp
            src/engineRework/engine/input/controller/Joystick.hpp
    )

    set (
            ENGINE_REWORK_ENGINE_INPUT_SOURCES

            ${ENGINE_REWORK_ENGINE_INPUT_CONTROLLER_SOURCES}
    )

    set (
            ENGINE_REWORK_ENGINE_SOURCES

            ${ENGINE_REWORK_ENGINE_EVENT_SOURCES}
            ${ENGINE_REWORK_ENGINE_INPUT_SOURCES}

            src/engineRework/engine/Core.cpp
            src/engineRework/engine/Core.hpp

            src/engineRework/engine/Engine.cpp
            src/engineRework/engine/Engine.hpp
    )

    set (
            ENGINE_REWORK_UTILITY_LOGGER_SOURCES

            src/engineRework/utility/logger/Logger.cpp
            src/engineRework/utility/logger/Logger.hpp
    )

    set (
            ENGINE_REWORK_UTILITY_PREPROCESS_SOURCES

            src/engineRework/utility/preprocess/Naming.hpp
            src/engineRework/utility/preprocess/Preprocess.hpp
            src/engineRework/utility/preprocess/Compiler.hpp
    )

    set (
            ENGINE_REWORK_UTILITY_SETTINGS_SOURCES

            src/engineRework/utility/settings/Settings.cpp
            src/engineRework/utility/settings/Settings.hpp
    )

    set (
            ENGINE_REWORK_UTILITY_FUNC_SOURCES

            src/engineRework/utility/func/Func.hpp
    )

    set (
            ENGINE_REWORK_UTILITY_SOURCES

            ${ENGINE_REWORK_UTILITY_LOGGER_SOURCES}
            ${ENGINE_REWORK_UTILITY_FUNC_SOURCES}
            ${ENGINE_REWORK_UTILITY_PREPROCESS_SOURCES}
            ${ENGINE_REWORK_UTILITY_SETTINGS_SOURCES}
    )

    set (
            ENGINE_REWORK_RENDER_WINDOW_SOURCES

            src/engineRework/render/window/Window.cpp
            src/engineRework/render/window/Window.hpp

            src/engineRework/render/window/Monitor.cpp
            src/engineRework/render/window/Monitor.hpp
    )

    set (
            ENGINE_REWORK_RENDER_API_VULKAN_CORE_SOURCES

            src/engineRework/render/API/vulkan/core/VulkanCore.cpp
            src/engineRework/render/API/vulkan/core/VulkanCore.hpp

            src/engineRework/render/API/vulkan/core/VulkanAPICalls.hpp
            src/engineRework/render/API/vulkan/core/VulkanAPICalls.cpp

            src/engineRework/render/API/vulkan/core/VulkanAPIExceptions.hpp

            src/engineRework/render/API/vulkan/core/VulkanAPIDetails.hpp
            src/engineRework/render/API/vulkan/core/VulkanAPIExtensionDetails.hpp
            src/engineRework/render/API/vulkan/core/VulkanAPIKhronosExtensionDetails.hpp
            src/engineRework/render/API/vulkan/core/VulkanAPIAMDExtensionDetails.hpp
            src/engineRework/render/API/vulkan/core/VulkanAPINVidiaExtensionDetails.hpp
            src/engineRework/render/API/vulkan/core/VulkanAPIGoogleExtensionDetails.hpp
            src/engineRework/render/API/vulkan/core/VulkanAPIAppleExtensionDetails.hpp
            src/engineRework/render/API/vulkan/core/VulkanAPIIntelExtensionDetails.hpp
            src/engineRework/render/API/vulkan/core/VulkanAPIQualcommExtensionDetails.hpp
            src/engineRework/render/API/vulkan/core/VulkanAPIARMExtensionDetails.hpp
            src/engineRework/render/API/vulkan/core/VulkanAPIValveExtensionDetails.hpp
            src/engineRework/render/API/vulkan/core/VulkanAPIHuaweiExtensionDetails.hpp
            src/engineRework/render/API/vulkan/core/VulkanAPIBlackberryExtensionDetails.hpp
    )

    set (
            ENGINE_REWORK_RENDER_API_VULKAN_INSTANCE_DEVICE_QUEUE_SOURCES

            src/engineRework/render/API/vulkan/instance/device/queue/QueueFamily.cpp
            src/engineRework/render/API/vulkan/instance/device/queue/QueueFamily.hpp
    )

    set (
            ENGINE_REWORK_RENDER_API_VULKAN_INSTANCE_DEVICE_SOURCES

            ${ENGINE_REWORK_RENDER_API_VULKAN_INSTANCE_DEVICE_QUEUE_SOURCES}

            src/engineRework/render/API/vulkan/instance/device/PhysicalDevice.cpp
            src/engineRework/render/API/vulkan/instance/device/PhysicalDevice.hpp
    )

    set (
            ENGINE_REWORK_RENDER_API_VULKAN_INSTANCE_ALLOCATOR_SOURCES

            src/engineRework/render/API/vulkan/instance/allocator/Allocator.cpp
            src/engineRework/render/API/vulkan/instance/allocator/Allocator.hpp
    )

    set (
            ENGINE_REWORK_RENDER_API_VULKAN_INSTANCE_VALIDATION_SOURCES

            src/engineRework/render/API/vulkan/instance/validation/LayerHandler.cpp
            src/engineRework/render/API/vulkan/instance/validation/LayerHandler.hpp
    )

    set (
            ENGINE_REWORK_RENDER_API_VULKAN_INSTANCE_SOURCES

            ${ENGINE_REWORK_RENDER_API_VULKAN_INSTANCE_ALLOCATOR_SOURCES}
            ${ENGINE_REWORK_RENDER_API_VULKAN_INSTANCE_VALIDATION_SOURCES}
            ${ENGINE_REWORK_RENDER_API_VULKAN_INSTANCE_DEVICE_SOURCES}

            src/engineRework/render/API/vulkan/instance/Instance.cpp
            src/engineRework/render/API/vulkan/instance/Instance.hpp
    )

    set (
            ENGINE_REWORK_RENDER_API_VULKAN_SOURCES

            ${ENGINE_REWORK_RENDER_API_VULKAN_CORE_SOURCES}
            ${ENGINE_REWORK_RENDER_API_VULKAN_INSTANCE_SOURCES}

            src/engineRework/render/API/vulkan/VulkanRenderEngine.cpp
            src/engineRework/render/API/vulkan/VulkanRenderEngine.hpp
    )

    set (
            ENGINE_REWORK_RENDER_API_SOURCES

            ${ENGINE_REWORK_RENDER_API_VULKAN_SOURCES}

            src/engineRework/render/API/RenderEngine.cpp
            src/engineRework/render/API/RenderEngine.hpp
            src/engineRework/render/API/RenderEngineTypes.hpp
    )

    set (
            ENGINE_REWORK_RENDER_SOURCES

            ${ENGINE_REWORK_RENDER_WINDOW_SOURCES}
            ${ENGINE_REWORK_RENDER_API_SOURCES}
    )

    set (
            ENGINE_REWORK_SOURCES

            ${ENGINE_REWORK_ENGINE_SOURCES}
            ${ENGINE_REWORK_UTILITY_SOURCES}
            ${ENGINE_REWORK_RENDER_SOURCES}

            src/engineRework/runnables/engineMainTestApplication.cpp
    )

    add_executable (
            engine_main_test_application

            ${ENGINE_REWORK_SOURCES}
    )

    target_link_libraries (
            engine_main_test_application

            Vulkan::Vulkan
            glfw
            ${GLFW_LIBRARIES}
    )

    target_include_directories (
            engine_main_test_application

            PRIVATE

            src/engineRework

            src/engineRework/engine

            src/engineRework/engine/input
            src/engineRework/engine/input/controller

            src/engineRework/engine/event
            src/engineRework/engine/event/key
            src/engineRework/engine/event/mouse
            src/engineRework/engine/event/window
            src/engineRework/engine/event/controller

            src/engineRework/utility
            src/engineRework/utility/logger
            src/engineRework/utility/preprocess
            src/engineRework/utility/settings
            src/engineRework/utility/func

            src/engineRework/render
            src/engineRework/render/window
            src/engineRework/render/API
            src/engineRework/render/API/vulkan
            src/engineRework/render/API/vulkan/extension
            src/engineRework/render/API/vulkan/core
            src/engineRework/render/API/vulkan/instance
            src/engineRework/render/API/vulkan/instance/validation
            src/engineRework/render/API/vulkan/instance/allocator
            src/engineRework/render/API/vulkan/instance/device
            src/engineRework/render/API/vulkan/instance/device/queue
    )

endif()
