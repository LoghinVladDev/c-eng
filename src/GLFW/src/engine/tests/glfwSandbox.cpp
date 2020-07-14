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

    std::cout << ( A * B ) << '\n';

    engine::Matrix<int> C(3, 3);
    engine::Matrix<int> D(3, 3);

    C[0][0] = 4;
    C[0][1] = 2;
    C[0][2] = 0;

    C[1][0] = 0;
    C[1][1] = 8;
    C[1][2] = 1;

    C[2][0] = 0;
    C[2][1] = 1;
    C[2][2] = 0;


    D[0][0] = 4;
    D[0][1] = 2;
    D[0][2] = 1;

    D[1][0] = 2;
    D[1][1] = 0;
    D[1][2] = 4;

    D[2][0] = 9;
    D[2][1] = 4;
    D[2][2] = 2;

    std::cout << C * D << '\n';

//    engine::Matrix<int> E = engine::Matrix<int>::identity(4);
}
