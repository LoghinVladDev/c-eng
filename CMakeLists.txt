cmake_minimum_required(VERSION 3.5)
project(eng1)

set(CMAKE_CXX_STANDARD 20)
set(OpenGL_GL_PREFERENCE GLVND)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

#set(CMAKE_PREFIX_PATH "D:\\QT\\5.14.1\\mingw73_64\\")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
#set(CMAKE_C_COMPILE_OBJECT g++)

#set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTOUIC ON)
#set(CMAKE_AUTORCC ON)

add_subdirectory(src/glfw_src)
add_subdirectory(glad)
add_subdirectory(glm)
add_subdirectory(assimp-5.0.1)
#add_subdirectory(messengerOffline)
#add_subdirectory(messengerOffline/src)
#add_subdirectory(glm/glm)

#include_directories(glm/glm)
include_directories(assimp-5.0.1/include)
include_directories(glm)
include_directories(src/glfw_src/include)
include_directories(src/GLFW/src/engine)
include_directories(glad/include)
include_directories(stb_image)
include_directories(messengerOffline/include)

find_package(OpenGL REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

if(ANDROID)
    add_library( editorHelloWorld SHARED
            src/editor/main.cpp
            src/editor/mainwindow.cpp
            src/editor/mainwindow.h
            src/editor/mainwindow.ui
    )
else()
    add_executable( editorHelloWorld
            src/editor/main.cpp
            src/editor/mainwindow.cpp
            src/editor/mainwindow.h
            src/editor/mainwindow.ui
    )
endif()

target_link_libraries( editorHelloWorld PRIVATE Qt5::Widgets )

#add_executable(
#        editorHelloWorld src/editor/tests/helloWorld.cpp
#        src/editor/obj/window/mainWindow.cpp
#        src/editor/obj/window/mainWindow.h
#)

#target_link_libraries(editorHelloWorld Qt5::Widgets)

add_executable(
        sandbox src/exec/sandbox.cpp
        src/GLFW/src/engine/obj/util/data/Array.cpp
        src/GLFW/src/engine/obj/util/data/Array.h
)

add_executable( drawReshapeTest
        src/exec/tests/drawReshapeTest.cpp
        src/obj/engine/window/Window.cpp
        src/obj/engine/window/Window.h
        src/obj/engine/util/Size.cpp
        src/obj/engine/util/Size.h
        src/obj/engine/util/geom/Point.cpp
        src/obj/engine/util/geom/Point.h
        src/obj/engine/util/defs/types.h
        src/obj/engine/Engine.cpp
        src/obj/engine/Engine.h
        src/obj/engine/preCompiledHeaders.h
)

target_link_libraries(drawReshapeTest -lOpenGL32 -lfreeGLUT -lglu32)

add_executable( animateTest
        src/exec/tests/animateTest.cpp
        src/obj/engine/window/Window.cpp
        src/obj/engine/window/Window.h
        src/obj/engine/util/Size.cpp
        src/obj/engine/util/Size.h
        src/obj/engine/util/geom/Point.cpp
        src/obj/engine/util/geom/Point.h
        src/obj/engine/util/defs/types.h
        src/obj/engine/Engine.cpp
        src/obj/engine/Engine.h
        src/obj/engine/util/event/KeyListener.cpp
        src/obj/engine/util/event/KeyListener.h
        src/obj/engine/util/obj/standardObj/Camera.cpp
        src/obj/engine/util/obj/standardObj/Camera.h
        src/obj/engine/util/obj/standardObj/Sphere.cpp
        src/obj/engine/util/obj/standardObj/Sphere.h
        src/obj/engine/util/dataStructures/Array.cpp
        src/obj/engine/util/dataStructures/Array.h
        src/obj/engine/preCompiledHeaders.h
        src/GLFW/src/engine/enginePreproc.h src/GLFW/src/engine/obj/util/func/KeyFunctions.cpp src/GLFW/src/engine/obj/util/func/KeyFunctions.h)

target_link_libraries(animateTest -lOpenGL32 -lfreeGLUT -lglu32)

add_executable( inputTest
        src/exec/tests/inputTest.cpp
        src/obj/engine/window/Window.cpp
        src/obj/engine/window/Window.h
        src/obj/engine/util/Size.cpp
        src/obj/engine/util/Size.h
        src/obj/engine/util/geom/Point.cpp
        src/obj/engine/util/geom/Point.h
        src/obj/engine/util/defs/types.h
        src/obj/engine/Engine.cpp
        src/obj/engine/Engine.h
        src/obj/engine/util/event/KeyListener.cpp
        src/obj/engine/util/event/KeyListener.h
        src/obj/engine/preCompiledHeaders.h
        src/obj/engine/util/dataStructures/Color.cpp
        src/obj/engine/util/dataStructures/Color.h
)

target_link_libraries(inputTest -lOpenGL32 -lfreeGLUT -lglu32)

add_executable( cameraMovement
        src/exec/tests/cameraMovement.cpp
        src/obj/engine/window/Window.cpp
        src/obj/engine/window/Window.h
        src/obj/engine/util/geom/Vector.cpp
        src/obj/engine/util/geom/Vector.h
        src/obj/engine/util/Size.cpp
        src/obj/engine/util/Size.h
        src/obj/engine/util/geom/Point.cpp
        src/obj/engine/util/geom/Point.h
        src/obj/engine/util/defs/types.h
        src/obj/engine/Engine.cpp
        src/obj/engine/Engine.h
        src/obj/engine/util/event/KeyListener.cpp
        src/obj/engine/util/event/KeyListener.h
        src/obj/engine/util/obj/Transform.cpp
        src/obj/engine/util/obj/Transform.h
        src/obj/engine/util/obj/GameObject.cpp
        src/obj/engine/util/obj/GameObject.h
        src/obj/engine/preCompiledHeaders.h
        src/obj/engine/util/obj/standardObj/Camera.cpp
        src/obj/engine/util/obj/standardObj/Camera.h
)

target_link_libraries(cameraMovement -lOpenGL32 -lfreeGLUT -lglu32)


add_executable( libTests
        src/obj/engine/util/Size.cpp
        src/obj/engine/util/Size.h
        src/obj/engine/util/geom/Point.cpp
        src/obj/engine/util/geom/Point.h
        src/obj/engine/window/Window.cpp
        src/obj/engine/window/Window.h
        src/obj/engine/util/defs/types.h
        src/obj/engine/Engine.cpp
        src/obj/engine/Engine.h
        src/obj/engine/util/event/KeyListener.cpp
        src/obj/engine/util/event/KeyListener.h
        src/obj/engine/util/geom/Vector.cpp
        src/obj/engine/util/geom/Vector.h
        src/obj/engine/util/obj/Transform.cpp
        src/obj/engine/util/obj/Transform.h
        src/obj/engine/util/obj/GameObject.cpp
        src/obj/engine/util/obj/GameObject.h
        src/obj/engine/util/dataStructures/Array.h
        src/obj/engine/util/dataStructures/Array.cpp
        src/exec/tests/libTest.cpp
        src/obj/engine/preCompiledHeaders.h
        src/exec/tests/objectTests.cpp
        src/exec/tests/UITests.cpp)

target_link_libraries(libTests -lOpenGL32 -lfreeGLUT -lglu32)

add_executable( cameraMovement2
        src/exec/tests/cameraMovementTypeTwo.cpp
        src/obj/engine/window/Window.cpp
        src/obj/engine/window/Window.h
        src/obj/engine/util/geom/Vector.cpp
        src/obj/engine/util/geom/Vector.h
        src/obj/engine/util/Size.cpp
        src/obj/engine/util/Size.h
        src/obj/engine/util/geom/Point.cpp
        src/obj/engine/util/geom/Point.h
        src/obj/engine/util/defs/types.h
        src/obj/engine/Engine.cpp
        src/obj/engine/Engine.h
        src/obj/engine/util/event/KeyListener.cpp
        src/obj/engine/util/event/KeyListener.h
        src/obj/engine/util/obj/Transform.cpp
        src/obj/engine/util/obj/Transform.h
        src/obj/engine/util/obj/GameObject.cpp
        src/obj/engine/util/obj/GameObject.h
        src/obj/engine/preCompiledHeaders.h
        src/obj/engine/util/obj/standardObj/Camera.cpp
        src/obj/engine/util/obj/standardObj/Camera.h
)

target_link_libraries(cameraMovement2 -lOpenGL32 -lfreeGLUT -lglu32)

add_executable( objectTests
        src/exec/tests/objectTests.cpp
        src/obj/engine/window/Window.cpp
        src/obj/engine/window/Window.h
        src/obj/engine/util/geom/Vector.cpp
        src/obj/engine/util/geom/Vector.h
        src/obj/engine/util/Size.cpp
        src/obj/engine/util/Size.h
        src/obj/engine/util/geom/Point.cpp
        src/obj/engine/util/geom/Point.h
        src/obj/engine/util/defs/types.h
        src/obj/engine/Engine.cpp
        src/obj/engine/Engine.h
        src/obj/engine/util/event/KeyListener.cpp
        src/obj/engine/util/event/KeyListener.h
        src/obj/engine/util/obj/Transform.cpp
        src/obj/engine/util/obj/Transform.h
        src/obj/engine/util/obj/GameObject.cpp
        src/obj/engine/util/obj/GameObject.h
        src/obj/engine/preCompiledHeaders.h
        src/obj/engine/util/obj/standardObj/Camera.cpp
        src/obj/engine/util/obj/standardObj/Camera.h
        src/obj/engine/util/dataStructures/Color.cpp
        src/obj/engine/util/dataStructures/Color.h
        src/obj/engine/util/obj/standardObj/Sphere.cpp
        src/obj/engine/util/obj/standardObj/Sphere.h
        src/obj/engine/util/event/MouseListener.cpp
        src/obj/engine/util/event/MouseListener.h
        src/obj/engine/util/event/InputListener.cpp
        src/obj/engine/util/event/InputListener.h
)

target_link_libraries(objectTests -lOpenGL32 -lfreeGLUT -lglu32)

add_executable( UITests
        src/exec/tests/UITests.cpp
        src/obj/engine/window/Window.cpp
        src/obj/engine/window/Window.h
        src/obj/engine/util/geom/Vector.cpp
        src/obj/engine/util/geom/Vector.h
        src/obj/engine/util/Size.cpp
        src/obj/engine/util/Size.h
        src/obj/engine/util/geom/Point.cpp
        src/obj/engine/util/geom/Point.h
        src/obj/engine/util/defs/types.h
        src/obj/engine/Engine.cpp
        src/obj/engine/Engine.h
        src/obj/engine/util/event/KeyListener.cpp
        src/obj/engine/util/event/KeyListener.h
        src/obj/engine/util/obj/Transform.cpp
        src/obj/engine/util/obj/Transform.h
        src/obj/engine/util/obj/GameObject.cpp
        src/obj/engine/util/obj/GameObject.h
        src/obj/engine/preCompiledHeaders.h
        src/obj/engine/util/obj/standardObj/Camera.cpp
        src/obj/engine/util/obj/standardObj/Camera.h
        src/obj/engine/util/dataStructures/Color.cpp
        src/obj/engine/util/dataStructures/Color.h
        src/obj/engine/util/obj/standardObj/Sphere.cpp
        src/obj/engine/util/obj/standardObj/Sphere.h
        src/obj/engine/util/event/MouseListener.cpp
        src/obj/engine/util/event/MouseListener.h
        src/obj/engine/util/event/InputListener.cpp
        src/obj/engine/util/event/InputListener.h
)

target_link_libraries(UITests -lOpenGL32 -lfreeGLUT -lglu32)

add_executable( GLFWInitWindow
        src/GLFW/src/engine/tests/c/testInitWindow.cpp
        src/GLFW/src/engine/obj/util/diag/Diagnostic.cpp src/GLFW/src/engine/obj/util/diag/Diagnostic.h src/GLFW/src/engine/enginePreproc.h src/GLFW/src/engine/types.h src/GLFW/src/engine/tests/h/lighting.h)

target_link_libraries( GLFWInitWindow glfw ${GLFW_LIBRARIES} )

add_executable( GLFWPortOfFreeGLUT
        glad/src/glad.c
        glad/include/glad/glad.h
        glad/include/KHR/khrplatform.h
        src/GLFW/src/engine/tests/c/mainPort.cpp
        src/GLFW/src/engine/obj/window/Window.cpp
        src/GLFW/src/engine/obj/window/Window.h
        src/GLFW/src/engine/obj/util/func/KeyFunctions.cpp
        src/GLFW/src/engine/obj/util/func/KeyFunctions.h
        src/GLFW/src/engine/obj/util/geom/Size.cpp
        src/GLFW/src/engine/obj/util/geom/Size.h
        src/GLFW/src/engine/obj/util/geom/Point.cpp
        src/GLFW/src/engine/obj/util/geom/Point.h
        src/GLFW/src/engine/obj/util/geom/Vector.cpp
        src/GLFW/src/engine/obj/util/geom/Vector.h
        src/GLFW/src/engine/obj/util/geom/Vector4.cpp
        src/GLFW/src/engine/obj/util/geom/Vector4.h
        src/GLFW/src/engine/obj/util/event/InputListener.cpp
        src/GLFW/src/engine/obj/util/event/InputListener.h
        src/GLFW/src/engine/obj/util/event/KeyListener.cpp
        src/GLFW/src/engine/obj/util/event/KeyListener.h
        src/GLFW/src/engine/Engine.cpp
        src/GLFW/src/engine/Engine.h
        src/GLFW/src/engine/types.h
        src/GLFW/src/engine/enginePreproc.h
        src/GLFW/src/engine/obj/util/event/MouseListener.cpp
        src/GLFW/src/engine/obj/util/event/MouseListener.h
        src/GLFW/src/engine/obj/util/struct/inputAxisFunc.h
        src/GLFW/src/engine/obj/util/struct/inputAxisFunc.c
        src/GLFW/src/engine/obj/util/obj/Transform.cpp
        src/GLFW/src/engine/obj/util/obj/Transform.h
        src/GLFW/src/engine/obj/util/obj/GameObject.cpp
        src/GLFW/src/engine/obj/util/obj/GameObject.h
        src/GLFW/src/engine/obj/util/data/Color.cpp
        src/GLFW/src/engine/obj/util/data/Color.h
        src/GLFW/src/engine/obj/util/data/Array.cpp
        src/GLFW/src/engine/obj/util/data/Array.h
        src/GLFW/src/engine/obj/util/obj/stdObj/Camera.cpp
        src/GLFW/src/engine/obj/util/obj/stdObj/Camera.h
        src/GLFW/src/engine/obj/util/shader/Shader.cpp
        src/GLFW/src/engine/obj/util/shader/Shader.h stb_image/stb-image.h src/GLFW/src/engine/obj/util/geom/Vector2.cpp src/GLFW/src/engine/obj/util/geom/Vector2.h src/GLFW/src/engine/obj/util/data/Matrix.cpp src/GLFW/src/engine/obj/util/data/Matrix.h)

target_link_libraries( GLFWPortOfFreeGLUT glfw ${GLFW_LIBRARIES} )

add_executable( drawTests src/GLFW/src/engine/tests/c/drawTests.cpp
        glad/src/glad.c
        glad/include/glad/glad.h
        glad/include/KHR/khrplatform.h
        src/GLFW/src/engine/obj/util/shader/Shader.cpp
        src/GLFW/src/engine/obj/util/shader/Shader.h
        src/GLFW/src/engine/obj/util/diag/Diagnostic.cpp
        src/GLFW/src/engine/obj/util/diag/Diagnostic.h
        stb_image/stb-image.h
        src/GLFW/src/engine/obj/util/geom/Vector2.cpp
        src/GLFW/src/engine/obj/util/geom/Vector2.h
        src/GLFW/src/engine/obj/util/data/Matrix.cpp
        src/GLFW/src/engine/obj/util/data/Matrix.h
)

target_link_libraries( drawTests glfw ${GLFW_LIBRARIES} )

add_executable( glfwSandbox
        src/GLFW/src/engine/tests/c/glfwSandbox.cpp
        src/GLFW/src/engine/obj/util/data/Matrix.h
        src/GLFW/src/engine/obj/util/data/Matrix.cpp
        src/GLFW/src/engine/obj/util/shader/Shader.cpp
        src/GLFW/src/engine/obj/util/shader/Shader.h
        src/GLFW/src/engine/obj/util/diag/Diagnostic.cpp
        src/GLFW/src/engine/obj/util/diag/Diagnostic.h
        stb_image/stb-image.h
    )

add_executable( glfwSandbox2
        glad/src/glad.c
        glad/include/glad/glad.h
        glad/include/KHR/khrplatform.h
        src/GLFW/src/engine/tests/sandbox/glfwSandbox2.cpp
        src/GLFW/src/engine/obj/util/shader/Shader.cpp
        src/GLFW/src/engine/obj/util/shader/Shader.h
        src/GLFW/src/engine/obj/util/diag/Diagnostic.cpp
        src/GLFW/src/engine/obj/util/diag/Diagnostic.h
        stb_image/stb-image.h
)

target_link_libraries( glfwSandbox2 glfw ${GLFW_LIBRARIES} )

add_executable( glfwWhiteboard1
        glad/src/glad.c
        glad/include/glad/glad.h
        glad/include/KHR/khrplatform.h
        src/GLFW/src/engine/tests/sandbox/whiteboard1.cpp
        src/GLFW/src/engine/obj/util/shader/Shader.cpp
        src/GLFW/src/engine/obj/util/shader/Shader.h
        src/GLFW/src/engine/obj/util/diag/Diagnostic.cpp
        src/GLFW/src/engine/obj/util/diag/Diagnostic.h
        src/GLFW/src/engine/obj/util/obj/GameObject.cpp
        src/GLFW/src/engine/obj/util/obj/GameObject.h
        src/GLFW/src/engine/obj/util/obj/Transform.cpp
        src/GLFW/src/engine/obj/util/obj/Transform.h
        src/GLFW/src/engine/obj/util/geom/Vector.cpp
        src/GLFW/src/engine/obj/util/geom/Vector.h
        src/GLFW/src/engine/Engine.cpp
        src/GLFW/src/engine/Engine.h
        src/GLFW/src/engine/obj/window/Window.cpp
        src/GLFW/src/engine/obj/window/Window.h
        src/GLFW/src/engine/obj/util/struct/inputAxisFunc.c
        src/GLFW/src/engine/obj/util/struct/inputAxisFunc.h
        src/GLFW/src/engine/obj/util/data/String.cpp
        src/GLFW/src/engine/obj/util/data/String.h
        src/GLFW/src/engine/obj/util/data/Array.cpp
        src/GLFW/src/engine/obj/util/data/Array.h
        src/GLFW/src/engine/obj/util/data/Pair.cpp
        src/GLFW/src/engine/obj/util/data/Pair.h
        src/GLFW/src/engine/obj/util/data/Map.cpp
        src/GLFW/src/engine/obj/util/data/Map.h
        stb_image/stb-image.h
)

target_link_libraries( glfwWhiteboard1 glfw ${GLFW_LIBRARIES} )

add_executable( glfwWhiteboard2
        glad/src/glad.c
        glad/include/glad/glad.h
        glad/include/KHR/khrplatform.h
        src/GLFW/src/engine/tests/sandbox/whiteboard2.cpp
        src/GLFW/src/engine/obj/util/shader/Shader.cpp
        src/GLFW/src/engine/obj/util/shader/Shader.h
        src/GLFW/src/engine/obj/util/diag/Diagnostic.cpp
        src/GLFW/src/engine/obj/util/diag/Diagnostic.h
        stb_image/stb-image.h
        src/GLFW/src/engine/obj/util/data/Array.cpp
        src/GLFW/src/engine/obj/util/data/Array.h
        src/GLFW/src/engine/obj/util/data/String.cpp
        src/GLFW/src/engine/obj/util/data/String.h
)

target_link_libraries( glfwWhiteboard2 glfw ${GLFW_LIBRARIES} )


add_executable( glfwLightning
        src/GLFW/src/engine/tests/c/lightingTest.cpp
        glad/src/glad.c
        glad/include/glad/glad.h
        glad/include/KHR/khrplatform.h
        src/GLFW/src/engine/obj/util/shader/Shader.cpp
        src/GLFW/src/engine/obj/util/shader/Shader.h
        src/GLFW/src/engine/obj/util/diag/Diagnostic.cpp
        src/GLFW/src/engine/obj/util/diag/Diagnostic.h
        src/GLFW/src/engine/obj/util/obj/GameObject.cpp
        src/GLFW/src/engine/obj/util/obj/GameObject.h
        src/GLFW/src/engine/obj/util/obj/Transform.cpp
        src/GLFW/src/engine/obj/util/obj/Transform.h
        src/GLFW/src/engine/obj/util/geom/Vector.cpp
        src/GLFW/src/engine/obj/util/geom/Vector.h
        src/GLFW/src/engine/Engine.cpp
        src/GLFW/src/engine/Engine.h
        src/GLFW/src/engine/obj/window/Window.cpp
        src/GLFW/src/engine/obj/window/Window.h
        src/GLFW/src/engine/obj/util/struct/inputAxisFunc.c
        src/GLFW/src/engine/obj/util/struct/inputAxisFunc.h
        stb_image/stb-image.h
)

target_link_libraries( glfwLightning glfw ${GLFW_LIBRARIES} )

add_executable( glfwDiffuseMaps
        src/GLFW/src/engine/tests/c/diffuseMaps.cpp
        glad/src/glad.c
        glad/include/glad/glad.h
        glad/include/KHR/khrplatform.h
        src/GLFW/src/engine/obj/util/shader/Shader.cpp
        src/GLFW/src/engine/obj/util/shader/Shader.h
        src/GLFW/src/engine/obj/util/diag/Diagnostic.cpp
        src/GLFW/src/engine/obj/util/diag/Diagnostic.h
        src/GLFW/src/engine/obj/util/obj/GameObject.cpp
        src/GLFW/src/engine/obj/util/obj/GameObject.h
        src/GLFW/src/engine/obj/util/obj/Transform.cpp
        src/GLFW/src/engine/obj/util/obj/Transform.h
        src/GLFW/src/engine/obj/util/geom/Vector.cpp
        src/GLFW/src/engine/obj/util/geom/Vector.h
        src/GLFW/src/engine/Engine.cpp
        src/GLFW/src/engine/Engine.h
        src/GLFW/src/engine/obj/window/Window.cpp
        src/GLFW/src/engine/obj/window/Window.h
        src/GLFW/src/engine/obj/util/struct/inputAxisFunc.c
        src/GLFW/src/engine/obj/util/struct/inputAxisFunc.h
        stb_image/stb-image.h
)

target_link_libraries( glfwDiffuseMaps glfw ${GLFW_LIBRARIES} )

#set_target_properties(
#        drawTests
#        GLFWPortOfFreeGLUT
#
#        PROPERTIES
#
#        RUNTIME_OUTPUT_DIRECTORY "/build/bin/"
#        ARCHIVE_OUTPUT_DIRECTORY "/build/lib/"
#        LIBRARY_OUTPUT_DIRECTORY "/build/lib/"
#)


add_executable( glfwLightcasting
        src/GLFW/src/engine/tests/c/lightCasting.cpp
        glad/src/glad.c
        glad/include/glad/glad.h
        glad/include/KHR/khrplatform.h
        src/GLFW/src/engine/obj/util/shader/Shader.cpp
        src/GLFW/src/engine/obj/util/shader/Shader.h
        src/GLFW/src/engine/obj/util/diag/Diagnostic.cpp
        src/GLFW/src/engine/obj/util/diag/Diagnostic.h
        src/GLFW/src/engine/obj/util/obj/GameObject.cpp
        src/GLFW/src/engine/obj/util/obj/GameObject.h
        src/GLFW/src/engine/obj/util/obj/Transform.cpp
        src/GLFW/src/engine/obj/util/obj/Transform.h
        src/GLFW/src/engine/obj/util/geom/Vector.cpp
        src/GLFW/src/engine/obj/util/geom/Vector.h
        src/GLFW/src/engine/Engine.cpp
        src/GLFW/src/engine/Engine.h
        src/GLFW/src/engine/obj/window/Window.cpp
        src/GLFW/src/engine/obj/window/Window.h
        src/GLFW/src/engine/obj/util/struct/inputAxisFunc.c
        src/GLFW/src/engine/obj/util/struct/inputAxisFunc.h
        stb_image/stb-image.h
        )

target_link_libraries( glfwLightcasting glfw ${GLFW_LIBRARIES} )


add_executable( glfwSpotlights
        src/GLFW/src/engine/tests/c/spotlightTest.cpp
        glad/src/glad.c
        glad/include/glad/glad.h
        glad/include/KHR/khrplatform.h
        src/GLFW/src/engine/obj/util/shader/Shader.cpp
        src/GLFW/src/engine/obj/util/shader/Shader.h
        src/GLFW/src/engine/obj/util/diag/Diagnostic.cpp
        src/GLFW/src/engine/obj/util/diag/Diagnostic.h
        src/GLFW/src/engine/obj/util/obj/GameObject.cpp
        src/GLFW/src/engine/obj/util/obj/GameObject.h
        src/GLFW/src/engine/obj/util/obj/Transform.cpp
        src/GLFW/src/engine/obj/util/obj/Transform.h
        src/GLFW/src/engine/obj/util/geom/Vector.cpp
        src/GLFW/src/engine/obj/util/geom/Vector.h
        src/GLFW/src/engine/Engine.cpp
        src/GLFW/src/engine/Engine.h
        src/GLFW/src/engine/obj/window/Window.cpp
        src/GLFW/src/engine/obj/window/Window.h
        src/GLFW/src/engine/obj/util/struct/inputAxisFunc.c
        src/GLFW/src/engine/obj/util/struct/inputAxisFunc.h
        stb_image/stb-image.h
        )

target_link_libraries( glfwSpotlights glfw ${GLFW_LIBRARIES} )

add_executable( glfwMultLights
        src/GLFW/src/engine/tests/c/multipleLights.cpp
        glad/src/glad.c
        glad/include/glad/glad.h
        glad/include/KHR/khrplatform.h
        src/GLFW/src/engine/obj/util/shader/Shader.cpp
        src/GLFW/src/engine/obj/util/shader/Shader.h
        src/GLFW/src/engine/obj/util/diag/Diagnostic.cpp
        src/GLFW/src/engine/obj/util/diag/Diagnostic.h
        src/GLFW/src/engine/obj/util/obj/GameObject.cpp
        src/GLFW/src/engine/obj/util/obj/GameObject.h
        src/GLFW/src/engine/obj/util/obj/Transform.cpp
        src/GLFW/src/engine/obj/util/obj/Transform.h
        src/GLFW/src/engine/obj/util/geom/Vector.cpp
        src/GLFW/src/engine/obj/util/geom/Vector.h
        src/GLFW/src/engine/Engine.cpp
        src/GLFW/src/engine/Engine.h
        src/GLFW/src/engine/obj/window/Window.cpp
        src/GLFW/src/engine/obj/window/Window.h
        src/GLFW/src/engine/obj/util/struct/inputAxisFunc.c
        src/GLFW/src/engine/obj/util/struct/inputAxisFunc.h
        stb_image/stb-image.h
        )

target_link_libraries( glfwMultLights glfw ${GLFW_LIBRARIES} )

add_executable( glfwModels
        src/GLFW/src/engine/tests/c/glfwModels.cpp
        glad/src/glad.c
        glad/include/glad/glad.h
        glad/include/KHR/khrplatform.h
        src/GLFW/src/engine/obj/util/shader/Shader.cpp
        src/GLFW/src/engine/obj/util/shader/Shader.h
        src/GLFW/src/engine/obj/util/diag/Diagnostic.cpp
        src/GLFW/src/engine/obj/util/diag/Diagnostic.h
        src/GLFW/src/engine/obj/util/obj/GameObject.cpp
        src/GLFW/src/engine/obj/util/obj/GameObject.h
        src/GLFW/src/engine/obj/util/obj/Transform.cpp
        src/GLFW/src/engine/obj/util/obj/Transform.h
        src/GLFW/src/engine/obj/util/geom/Vector.cpp
        src/GLFW/src/engine/obj/util/geom/Vector.h
        src/GLFW/src/engine/Engine.cpp
        src/GLFW/src/engine/Engine.h
        src/GLFW/src/engine/obj/window/Window.cpp
        src/GLFW/src/engine/obj/window/Window.h
        src/GLFW/src/engine/obj/util/struct/inputAxisFunc.c
        src/GLFW/src/engine/obj/util/struct/inputAxisFunc.h
        stb_image/stb-image.h
        src/GLFW/src/engine/obj/util/struct/meshStructs.h
        src/GLFW/src/engine/obj/util/model/Mesh.cpp
        src/GLFW/src/engine/obj/util/model/Mesh.h
        src/GLFW/src/engine/obj/util/data/String.cpp
        src/GLFW/src/engine/obj/util/data/String.h
        src/GLFW/src/engine/obj/util/data/Array.cpp
        src/GLFW/src/engine/obj/util/data/Array.h
        src/GLFW/src/engine/obj/util/data/Set.cpp src/GLFW/src/engine/obj/util/data/Set.h src/GLFW/src/engine/obj/util/data/Map.cpp src/GLFW/src/engine/obj/util/data/Map.h)

target_link_libraries( glfwModels glfw ${GLFW_LIBRARIES} )


add_executable( Sandbox3
        src/GLFW/src/engine/tests/sandbox/sandbox3.cpp
        src/GLFW/src/engine/obj/util/data/Array.cpp
        src/GLFW/src/engine/obj/util/data/Array.h
        src/GLFW/src/engine/obj/util/data/String.cpp
        src/GLFW/src/engine/obj/util/data/String.h
        src/GLFW/src/engine/obj/util/data/Set.cpp
        src/GLFW/src/engine/obj/util/data/Set.h
        src/GLFW/src/engine/obj/util/data/Pair.cpp src/GLFW/src/engine/obj/util/data/Pair.h)