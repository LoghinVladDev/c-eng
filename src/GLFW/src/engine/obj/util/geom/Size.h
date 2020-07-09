#pragma once

#ifndef ENG1_SIZE_H
#define ENG1_SIZE_H

#include <string>

class Size {
private:
    int _width;
    int _height;

public:

    explicit Size(int width, int height) noexcept :
        _width(width), _height(height) {

    }

    [[nodiscard]] int getWidth() const noexcept {
        return this->_width;
    }

    [[nodiscard]] int getHeight() const noexcept {
        return this->_height;
    }

    [[maybe_unused]] void setHeight (int) noexcept;
    [[maybe_unused]] void setWidth  (int)  noexcept;

    [[maybe_unused]] explicit operator std::string () const;
};


#endif //ENG1_SIZE_H
