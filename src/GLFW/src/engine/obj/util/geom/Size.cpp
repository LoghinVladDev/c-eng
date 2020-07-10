//
// Created by Vlad on 03/07/2020.
//

#include "Size.h"

[[maybe_unused]] inline void engine::Size::setHeight (int height) noexcept {
    this->_height = height;
}

[[maybe_unused]] inline void engine::Size::setWidth (int width) noexcept {
    this->_width = width;
}

[[maybe_unused]] engine::Size::operator std::string() const {
    return "Size = { width = " +
        std::to_string(this->_width) +
        ", height = " +
        std::to_string(this->_height) +
        " }";
}