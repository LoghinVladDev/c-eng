//
// Created by vladl on 06/07/2020.
//

#include "../../obj/engine/util/dataStructures/Array.h"
#include <iostream>

using namespace EngineUtility;

int main(int argc, char** argv) {
    Array<std::string> array;

    array += "tag1";
    std::cout << array << '\n';
    array += "tag2";

    std::cout << array << '\n';
    array[3] = "tag4";
    std::cout << array << '\n';
    array[4] = "tag5";
    std::cout << array << '\n';
    array[2] = "tag3";

    std::cout << array << '\n';

    return 0;
}