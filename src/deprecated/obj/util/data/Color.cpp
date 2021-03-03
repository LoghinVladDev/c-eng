//
// Created by vladl on 07/07/2020.
//

#include "Color.h"

engine::Color::Color(uint8 red, uint8 green, uint8 blue, uint8 alpha) : _red(red), _green(green), _blue(blue), _alpha(alpha) {

}

engine::Color::Color(const VectorF & colorAsVector) {
    this->set(colorAsVector);
}

engine::Color::Color(const VectorD & colorAsVector) {
    this->set(colorAsVector);
}

engine::Color::Color(const Vector4F & colorAsVector) {
    this->set(colorAsVector);
}

engine::Color::Color(const Vector4D & colorAsVector) {
    this->set(colorAsVector);
}

