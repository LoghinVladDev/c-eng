//
// Created by Vlad on 03/07/2020.
//
#pragma once
#ifndef ENG1_POINT_H
#define ENG1_POINT_H

#include <string>

class Point {
private:
    int _x;
    int _y;
public :
    explicit Point(int x, int y) noexcept :
        _x(x), _y(y) {
    }

    [[maybe_unused]] void setX(int) noexcept;
    [[maybe_unused]] void setY(int) noexcept;

    [[maybe_unused]] [[nodiscard]] int getX() const noexcept {
        return this->_x;
    };

    [[maybe_unused]] [[nodiscard]] int getY() const noexcept {
        return this->_y;
    };

    [[maybe_unused]] operator std::string() const;
};


#endif //ENG1_POINT_H
