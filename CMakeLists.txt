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
)

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
)

target_link_libraries(inputTest -lOpenGL32 -lfreeGLUT -lglu32)