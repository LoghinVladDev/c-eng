//
// Created by vladl on 07/07/2020.
//

#include "Color.h"

Color::Color(uint8 red, uint8 green, uint8 blue) : _red(red), _green(green), _blue(blue) {

}

Color::Color(const VectorF & colorAsVector) {
    this->set(colorAsVector);
}

