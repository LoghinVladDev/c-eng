//
// Created by loghin on 7/22/20.
//

#include <obj/util/data/String.h>
#include <obj/util/data/Set.h>

#include <iostream>

using namespace engine;

template <class T>
void operandTests(Set<T> A, Set<T> B) {
    std::cout << "A + B : " << A + B << '\n';
    std::cout << "A - B : " << A - B << '\n';
    std::cout << "B - A : " << B - A << '\n';

    std::cout << "A * B : " << A * B << '\n';

    std::cout << "A ^ B : " << Set<String>::intersection(A, B) << '\n';
    std::cout << "A u B : " << Set<String>::unity(A, B) << '\n';
    std::cout << "A !^ B : " << Set<String>::outerIntersection(A, B) << '\n';


}

int main() {
    Set<String> A {
        String("str1"),
        String("str2"),
        String("str6"),
        String("str3")
    };

    Set<String> B = {
        String("str3"),
        String("str5"),
        String("str2"),
        String("str4"),
        String("str6")
    };

    std::cout << A << '\n' << B << '\n';

    operandTests(A, B);
}