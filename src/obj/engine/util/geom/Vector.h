//
// Created by vladl on 05/07/2020.
//

#pragma once

#ifndef ENG1_VECTOR_H
#define ENG1_VECTOR_H

#include <string>
#include <cmath>
#include <exception>

class [[maybe_unused]] EngineVectorDivByZero : public std::exception {
    [[nodiscard]] const char * what() const noexcept override {
        return "Tried dividing by zero!";
    }
};

class [[maybe_unused]] VectorF {
private:
    float _x {0.0f};
    float _y {0.0f};
    float _z {0.0f};

public:
    [[maybe_unused]] VectorF() noexcept;
    [[maybe_unused]] VectorF(float x, float y, float z) noexcept :
        _x(x), _y(y), _z(y) {

    }
    [[maybe_unused]] VectorF(const VectorF&) noexcept;

    [[maybe_unused]] [[nodiscard]] bool isNull() const noexcept;

    [[maybe_unused]] VectorF& setX(float x) noexcept {
        this->_x = x;
        return *this;
    }

    [[maybe_unused]] VectorF& setY(float y) noexcept{
        this->_y = y;
        return *this;
    }

    [[maybe_unused]] VectorF& setZ(float z) noexcept{
        this->_z = z;
        return *this;
    }

    [[maybe_unused]] [[nodiscard]] float getX() const noexcept{
        return this->_x;
    }

    [[maybe_unused]] [[nodiscard]] float getY() const noexcept{
        return this->_y;
    }

    [[maybe_unused]] [[nodiscard]] float getZ() const noexcept{
        return this->_z;
    }

    [[maybe_unused]] [[nodiscard]] std::string toString() const noexcept;
    [[maybe_unused]] explicit operator std::string () const;

    friend VectorF operator+ (const VectorF&, const VectorF&) noexcept;
    friend VectorF operator- (const VectorF&, const VectorF&) noexcept;
    friend VectorF operator* (const VectorF&, float) noexcept;
    friend VectorF operator* (const VectorF&, int) noexcept;
    friend VectorF operator/ (const VectorF&, float) noexcept(false);
    friend VectorF operator/ (const VectorF&, int) noexcept(false);
    friend VectorF operator^ (const VectorF&, float) noexcept;
    friend VectorF operator^ (const VectorF&, int) noexcept;

    VectorF& operator= (const VectorF&) noexcept;
    VectorF& operator+= (const VectorF&) noexcept;
    VectorF& operator-= (const VectorF&) noexcept;
    VectorF& operator*= (float) noexcept;
    VectorF& operator*= (int) noexcept;
    VectorF& operator/= (float) noexcept(false);
    VectorF& operator/= (int) noexcept(false);
    VectorF& operator^= (float) noexcept;
    VectorF& operator^= (int) noexcept;

    friend bool operator == (const VectorF&, const VectorF&) noexcept;
    friend bool operator != (const VectorF&, const VectorF&) noexcept;
};

class [[maybe_unused]] VectorD {
private:
    double _x {0.0f};
    double _y {0.0f};
    double _z {0.0f};

public:
    [[maybe_unused]] VectorD() noexcept;
    [[maybe_unused]] VectorD(double x, double y, double z) noexcept;
    [[maybe_unused]] VectorD(const VectorD&) noexcept;

    [[maybe_unused]] [[nodiscard]] bool isNull() const noexcept;

    [[maybe_unused]] VectorD& setX(double) noexcept;
    [[maybe_unused]] VectorD& setY(double) noexcept;
    [[maybe_unused]] VectorD& setZ(double) noexcept;

    [[maybe_unused]] [[nodiscard]] double getX() const noexcept;
    [[maybe_unused]] [[nodiscard]] double getY() const noexcept;
    [[maybe_unused]] [[nodiscard]] double getZ() const noexcept;

    [[maybe_unused]] [[nodiscard]] std::string toString() const noexcept;
    [[maybe_unused]] explicit operator std::string () const;

    friend VectorD operator+ (const VectorD&, const VectorD&) noexcept;
    friend VectorD operator- (const VectorD&, const VectorD&) noexcept;
    friend VectorD operator* (const VectorD&, double) noexcept;
    friend VectorD operator* (const VectorD&, int) noexcept;
    friend VectorD operator/ (const VectorD&, double) noexcept(false);
    friend VectorD operator/ (const VectorD&, int) noexcept(false);
    friend VectorD operator^ (const VectorD&, double) noexcept;
    friend VectorD operator^ (const VectorD&, int) noexcept;

    VectorD& operator= (const VectorD&) noexcept;
    VectorD& operator+= (const VectorD&) noexcept;
    VectorD& operator-= (const VectorD&) noexcept;
    VectorD& operator*= (double) noexcept;
    VectorD& operator*= (int) noexcept;
    VectorD& operator/= (double) noexcept(false);
    VectorD& operator/= (int) noexcept(false);
    VectorD& operator^= (double) noexcept;
    VectorD& operator^= (int) noexcept;

    friend bool operator == (const VectorD&, const VectorD&) noexcept;
    friend bool operator != (const VectorD&, const VectorD&) noexcept;
};

[[maybe_unused]] typedef VectorF Vector;

#endif //ENG1_VECTOR_H
