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

include_directories(dependencies/glm)
include_directories(dependencies/glfw/include)
include_directories(dependencies/stb)
include_directories(dependencies/cds/include)

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
    if(WIN32)
        link_libraries(gcov)
    endif()
endif ()


# VULKAN extension

find_package(Vulkan)

if(Vulkan_FOUND)
    include_directories( ${Vulkan_INCLUDE_DIRS} )

    message(-- VULKAN_PATH :   ${Vulkan_LIBRARY} )

    set (
            ENGINE_EVENT_CONTROLLER_SOURCES

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
            ENGINE_EVENT_KEY_SOURCES

            src/engineRework/engine/event/key/KeyEvent.cpp
            src/engineRework/engine/event/key/KeyEvent.hpp

            src/engineRework/engine/event/key/KeyPressEvent.cpp
            src/engineRework/engine/event/key/KeyPressEvent.hpp

            src/engineRework/engine/event/key/KeyReleaseEvent.cpp
            src/engineRework/engine/event/key/KeyReleaseEvent.hpp
    )

    set (
            ENGINE_EVENT_MOUSE_SOURCES

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
            ENGINE_EVENT_WINDOW_SOURCES

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
            ENGINE_EVENT_SOURCES

            ${ENGINE_EVENT_CONTROLLER_SOURCES}
            ${ENGINE_EVENT_KEY_SOURCES}
            ${ENGINE_EVENT_MOUSE_SOURCES}
            ${ENGINE_EVENT_WINDOW_SOURCES}

            src/engineRework/engine/event/EventHandler.cpp
            src/engineRework/engine/event/EventHandler.hpp

            src/engineRework/engine/event/Event.hpp
            src/engineRework/engine/event/Event.cpp
    )

    set (
            ENGINE_INPUT_CONTROLLER_SOURCES

            src/engineRework/engine/input/controller/Controller.cpp
            src/engineRework/engine/input/controller/Controller.hpp

            src/engineRework/engine/input/controller/Gamepad.cpp
            src/engineRework/engine/input/controller/Gamepad.hpp

            src/engineRework/engine/input/controller/Joystick.cpp
            src/engineRework/engine/input/controller/Joystick.hpp
    )

    set (
            ENGINE_INPUT_SOURCES

            ${ENGINE_INPUT_CONTROLLER_SOURCES}
    )

    set (
            ENGINE_SOURCES

            ${ENGINE_EVENT_SOURCES}
            ${ENGINE_INPUT_SOURCES}

            src/engineRework/engine/Core.cpp
            src/engineRework/engine/Core.hpp

            src/engineRework/engine/Engine.cpp
            src/engineRework/engine/Engine.hpp
    )

    set (
            UTILITY_LOGGER_SOURCES

            src/engineRework/utility/logger/Logger.cpp
            src/engineRework/utility/logger/Logger.hpp
    )

    set (
            UTILITY_PREPROCESS_SOURCES

            src/engineRework/utility/preprocess/Naming.hpp
            src/engineRework/utility/preprocess/Preprocess.hpp
            src/engineRework/utility/preprocess/Compiler.hpp
    )

    set (
            UTILITY_SETTINGS_SOURCES

            src/engineRework/utility/settings/Settings.cpp
            src/engineRework/utility/settings/Settings.hpp
    )

    set (
            UTILITY_FUNC_SOURCES

            src/engineRework/utility/func/Func.hpp
    )

    set (
            UTILITY_SOURCES

            ${UTILITY_LOGGER_SOURCES}
            ${UTILITY_FUNC_SOURCES}
            ${UTILITY_PREPROCESS_SOURCES}
            ${UTILITY_SETTINGS_SOURCES}
    )

    set (
            RENDER_WINDOW_SOURCES

            src/engineRework/render/window/Window.cpp
            src/engineRework/render/window/Window.hpp

            src/engineRework/render/window/Monitor.cpp
            src/engineRework/render/window/Monitor.hpp
    )

    set (
            RENDER_API_VULKAN_CORE_SOURCES

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
            RENDER_API_VULKAN_INSTANCE_DEVICE_QUEUE_SOURCES

            src/engineRework/render/API/vulkan/instance/device/queue/Queue.cpp
            src/engineRework/render/API/vulkan/instance/device/queue/Queue.hpp

            src/engineRework/render/API/vulkan/instance/device/queue/QueueFamily.cpp
            src/engineRework/render/API/vulkan/instance/device/queue/QueueFamily.hpp
    )

    set (
            RENDER_API_VULKAN_INSTANCE_DEVICE_SOURCES

            ${RENDER_API_VULKAN_INSTANCE_DEVICE_QUEUE_SOURCES}

            src/engineRework/render/API/vulkan/instance/device/PhysicalDevice.cpp
            src/engineRework/render/API/vulkan/instance/device/PhysicalDevice.hpp

            src/engineRework/render/API/vulkan/instance/device/Device.cpp
            src/engineRework/render/API/vulkan/instance/device/Device.hpp
    )

    set (
            RENDER_API_VULKAN_INSTANCE_ALLOCATOR_SOURCES

            src/engineRework/render/API/vulkan/instance/allocator/Allocator.cpp
            src/engineRework/render/API/vulkan/instance/allocator/Allocator.hpp
    )

    set (
            RENDER_API_VULKAN_INSTANCE_VALIDATION_SOURCES

            src/engineRework/render/API/vulkan/instance/validation/LayerHandler.cpp
            src/engineRework/render/API/vulkan/instance/validation/LayerHandler.hpp
    )

    set (
            RENDER_API_VULKAN_INSTANCE_PRESENT_SWAP_SOURCES

            src/engineRework/render/API/vulkan/instance/present/swap/SwapChain.cpp
            src/engineRework/render/API/vulkan/instance/present/swap/SwapChain.hpp
    )

    set (
            RENDER_API_VULKAN_INSTANCE_PRESENT_SOURCES

            ${RENDER_API_VULKAN_INSTANCE_PRESENT_SWAP_SOURCES}

            src/engineRework/render/API/vulkan/instance/present/SwapChainPresentHandler.cpp
            src/engineRework/render/API/vulkan/instance/present/SwapChainPresentHandler.hpp

            src/engineRework/render/API/vulkan/instance/present/PresentHandler.cpp
            src/engineRework/render/API/vulkan/instance/present/PresentHandler.hpp
    )

    set (
            RENDER_API_VULKAN_INSTANCE_SOURCES

            ${RENDER_API_VULKAN_INSTANCE_ALLOCATOR_SOURCES}
            ${RENDER_API_VULKAN_INSTANCE_VALIDATION_SOURCES}
            ${RENDER_API_VULKAN_INSTANCE_DEVICE_SOURCES}
            ${RENDER_API_VULKAN_INSTANCE_PRESENT_SOURCES}

            src/engineRework/render/API/vulkan/instance/Instance.cpp
            src/engineRework/render/API/vulkan/instance/Instance.hpp
    )

    set (
            RENDER_API_VULKAN_SOURCES

            ${RENDER_API_VULKAN_CORE_SOURCES}
            ${RENDER_API_VULKAN_INSTANCE_SOURCES}

            src/engineRework/render/API/vulkan/VulkanRenderEngine.cpp
            src/engineRework/render/API/vulkan/VulkanRenderEngine.hpp
    )

    set (
            RENDER_API_SOURCES

            ${RENDER_API_VULKAN_SOURCES}

            src/engineRework/render/API/RenderEngine.cpp
            src/engineRework/render/API/RenderEngine.hpp
            src/engineRework/render/API/RenderEngineTypes.hpp
    )

    set (
            RENDER_SOURCES

            ${RENDER_WINDOW_SOURCES}
            ${RENDER_API_SOURCES}
    )

    set (
            _SOURCES

            ${ENGINE_SOURCES}
            ${UTILITY_SOURCES}
            ${RENDER_SOURCES}

            src/engineRework/runnables/engineMainTestApplication.cpp
    )

    add_executable (
            engine_main_test_application

            ${_SOURCES}
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
            src/engineRework/render/API/vulkan/instance/present
            src/engineRework/render/API/vulkan/instance/present/swap
            src/engineRework/render/API/vulkan/instance/allocator
            src/engineRework/render/API/vulkan/instance/device
            src/engineRework/render/API/vulkan/instance/device/queue
    )

endif()
