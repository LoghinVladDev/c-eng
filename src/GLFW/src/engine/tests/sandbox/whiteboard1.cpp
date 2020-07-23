//
// Created by vladl on 12/07/2020.
//

#include <iostream>
#include <obj/util/data/Map.h>

using namespace engine;

int main() {
    HashMap<String, String> tokens;

    tokens.put(String("a"), String("bbb"));
    tokens.put(String("b"), String("dddd"));
    tokens.put(String("xyz"), String("eefef"));

    Array<String*> keys = tokens.getKeys();
    Array<String*> values = tokens.getValues();

    for(std::size_t i = 0; i < keys.getLength(); i++) {
        std::cout << (*keys[i]) << ' ';
    }
    std::cout << '\n';

    for(std::size_t i = 0; i < values.getLength(); i++) {
        std::cout << (*values[i]) << ' ';
    }
    std::cout << '\n';

    std::cout << tokens << '\n';
}