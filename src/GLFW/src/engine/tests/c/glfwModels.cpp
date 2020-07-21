//
// Created by loghin on 7/20/20.
//

#include <types.h>
#include <iostream>
#include <obj/util/shader/Shader.h>
#include <obj/util/data/String.h>

using namespace engine;

int main(int argc, char ** argv){

    Shader::setShadersFolder(__SHADERS_PATH__);

//    String test("\"bcde e \"");

//    test.trim("e \"");

//    std::cout << test << '\n';
//
    auto* shader = new Shader("triangle.vert", "triangle.frag", true, true);

    delete shader;

    return 0;
}