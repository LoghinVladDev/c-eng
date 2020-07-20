//
// Created by loghin on 7/20/20.
//

#include <types.h>
#include <iostream>
#include <obj/util/shader/Shader.h>

using namespace engine;

int main(int argc, char ** argv){

    Shader::setShadersFolder(__SHADERS_PATH__);

    auto* shader = new Shader("triangle.vert", "triangle.frag", true, true);

    delete shader;

    return 0;
}