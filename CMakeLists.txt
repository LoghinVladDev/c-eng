cmake_minimum_required(VERSION 3.16)
project(eng1)

set(CMAKE_CXX_STANDARD 20)

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
        src/obj/engine/preCompiledHeaders.h)

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
        src/obj/engine/preCompiledHeaders.h)

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
        src/obj/engine/preCompiledHeaders.h)

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
)

target_link_libraries(libTests -lOpenGL32 -lfreeGLUT -lglu32)