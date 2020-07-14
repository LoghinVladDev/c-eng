//
// Created by vladl on 14/07/2020.
//

#include <iostream>
#include <obj/util/data/Matrix.h>

int main(){
    engine::Matrix<float> A(2, 2);
    engine::Matrix<float> B(2, 2);

    A[0][0] = 1;
    A[0][1] = 2;
    A[1][0] = 3;
    A[1][1] = 4;

    B[0][0] = 5;
    B[0][1] = 6;
    B[1][0] = 7;
    B[1][1] = 8;

    std::cout << (A + B) << '\n';
}
