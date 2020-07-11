//
// Created by vladl on 07/07/2020.
//

#include "Color.h"

engine::Color::Color(uint8 red, uint8 green, uint8 blue) : _red(red), _green(green), _blue(blue) {

}

engine::Color::Color(const VectorF & colorAsVector) {
    this->set(colorAsVector);
}

