//
// Created by Vlad on 03/07/2020.
//
#pragma once
#ifndef ENG1_POINT_H
#define ENG1_POINT_H


class Point {
private:
    int _x;
    int _y;
public:
    explicit Point(int x, int y) : _x(x), _y(y) { }

    [[maybe_unused]] inline void setX(int x) noexcept { this->_x = x; }
    [[maybe_unused]] inline void setY(int y) noexcept { this->_y = y; }

    [[maybe_unused]] [[nodiscard]] inline int getX() const noexcept { return this->_x; }
    [[maybe_unused]] [[nodiscard]] inline int getY() const noexcept { return this->_y; }
};


#endif //ENG1_POINT_H
