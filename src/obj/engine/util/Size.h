//
// Created by Vlad on 03/07/2020.
//
#pragma once
#ifndef ENG1_SIZE_H
#define ENG1_SIZE_H


class Size {
private:
    int _height;
    int _width;
public:
    explicit Size(int width, int height) noexcept : _width(width), _height(height) { }

    [[maybe_unused]] [[nodiscard]] inline int getHeight() const noexcept { return this->_height; }
    [[maybe_unused]] [[nodiscard]] inline int getWidth()  const noexcept { return this->_width; }

    [[maybe_unused]] inline void setHeight (int height) noexcept { this->_height = height; }
    [[maybe_unused]] inline void setWidth  (int width)  noexcept { this->_width = width; }
};


#endif //ENG1_SIZE_H
