//
// Created by Vlad on 03/07/2020.
//

#include "Point.h"

[[maybe_unused]] inline void engine::Point::setX(int x) noexcept {
    this->_x = x;
}

[[maybe_unused]] inline void engine::Point::setY(int y) noexcept {
    this->_y = y;
}

[[maybe_unused]] engine::Point::operator std::string() const {
    return "Point = { x = " +
           std::to_string(this->_x) +
           ", y = " +
           std::to_string(this->_y) +
           " }";
}
