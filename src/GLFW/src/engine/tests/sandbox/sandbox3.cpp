//
// Created by loghin on 7/22/20.
//

#include <obj/util/data/String.h>
#include <obj/util/data/Set.h>

#include <iostream>

using namespace engine;

int main() {
    Set<String> defineKeys;

    String a("abc");
    String b("abcd");
    String c("ABVC");
    String d("abc");

    defineKeys.insert(a);
    defineKeys.insert(b);
    defineKeys.insert(a);
    defineKeys.insert(c);
    defineKeys.insert(d);

    std::cout << defineKeys;
}