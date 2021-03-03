#pragma clang diagnostic push
#pragma ide diagnostic ignored "NotImplementedFunctions"
//
// Created by vladl on 05/07/2020.
//


#pragma once

#ifndef ENG1_VECTOR4_H
#define ENG1_VECTOR4_H

#include <string>
#include <cmath>
#include <exception>

namespace engine { class Vector4F; class Vector4D; }

engine::Vector4F (operator+)(const engine::Vector4F &, const engine::Vector4F &) noexcept;
engine::Vector4F operator-(const engine::Vector4F &, const engine::Vector4F &) noexcept;
engine::Vector4F operator*(const engine::Vector4F &, float) noexcept;
engine::Vector4F operator*(const engine::Vector4F &, int) noexcept;
engine::Vector4F operator/(const engine::Vector4F &, float) noexcept(false);
engine::Vector4F operator/(const engine::Vector4F &, int) noexcept(false);
engine::Vector4F operator^(const engine::Vector4F &, float) noexcept;
engine::Vector4F operator^(const engine::Vector4F &, int) noexcept;

engine::Vector4D operator+(const engine::Vector4D &, const engine::Vector4D &) noexcept;
engine::Vector4D operator-(const engine::Vector4D &, const engine::Vector4D &) noexcept;
engine::Vector4D operator*(const engine::Vector4D &, double) noexcept;
engine::Vector4D operator*(const engine::Vector4D &, int) noexcept;
engine::Vector4D operator/(const engine::Vector4D &, double) noexcept(false);
engine::Vector4D operator/(const engine::Vector4D &, int) noexcept(false);
engine::Vector4D operator^(const engine::Vector4D &, double) noexcept;
engine::Vector4D operator^(const engine::Vector4D &, int) noexcept;

bool operator==(const engine::Vector4D &, const engine::Vector4D &) noexcept;
bool operator!=(const engine::Vector4D &, const engine::Vector4D &) noexcept;

bool operator==(const engine::Vector4F &, const engine::Vector4F &) noexcept;
bool operator!=(const engine::Vector4F &, const engine::Vector4F &) noexcept;

namespace engine {

    class [[maybe_unused]] EngineVector4DivByZero : public std::exception {
        [[nodiscard]] const char *what() const noexcept override {
            return "Tried dividing by zero!";
        }
    };

    class Vector4D;

    class [[maybe_unused]] Vector4F {
    private:
        float _x{0.0f};
        float _y{0.0f};
        float _z{0.0f};
        float _t{0.0f};

    public:
        [[maybe_unused]] [[maybe_unused]] static Vector4F nullVector;

        [[maybe_unused]] Vector4F() noexcept;

        [[maybe_unused]] Vector4F(float x, float y, float z, float t) noexcept:
                _x(x), _y(y), _z(z), _t(t) {

        }

        [[maybe_unused]] Vector4F(const Vector4F &) noexcept = default;
        [[maybe_unused]] explicit Vector4F(const Vector4D &) noexcept;

        [[maybe_unused]] [[nodiscard]] bool isNull() const noexcept;

        [[maybe_unused]] Vector4F &setX(float x) noexcept {
            this->_x = x;
            return *this;
        }

        [[maybe_unused]] Vector4F &setY(float y) noexcept {
            this->_y = y;
            return *this;
        }

        [[maybe_unused]] Vector4F &setZ(float z) noexcept {
            this->_z = z;
            return *this;
        }

        [[maybe_unused]] Vector4F &setT(float t) noexcept {
            this->_t = t;
            return *this;
        }

        [[maybe_unused]] [[nodiscard]] float getX() const noexcept {
            return this->_x;
        }

        [[maybe_unused]] [[nodiscard]] float getY() const noexcept {
            return this->_y;
        }

        [[maybe_unused]] [[nodiscard]] float getZ() const noexcept {
            return this->_z;
        }

        [[maybe_unused]] [[nodiscard]] float getT() const noexcept {
            return this->_t;
        }

        [[maybe_unused]] [[nodiscard]] std::string toString() const noexcept;
        [[maybe_unused]] explicit operator std::string() const;
        [[maybe_unused]] explicit operator Vector4D() const;

        friend Vector4F (::operator+)(const Vector4F &, const Vector4F &) noexcept;
        friend Vector4F (::operator-)(const Vector4F &, const Vector4F &) noexcept;
        friend Vector4F (::operator*)(const Vector4F &, float) noexcept;
        friend Vector4F (::operator*)(const Vector4F &, int) noexcept;
        friend Vector4F (::operator/)(const Vector4F &, float) noexcept(false);
        friend Vector4F (::operator/)(const Vector4F &, int) noexcept(false);
        friend Vector4F (::operator^)(const Vector4F &, float) noexcept;
        friend Vector4F (::operator^)(const Vector4F &, int) noexcept;

        Vector4F &operator=(const Vector4F &) noexcept;
        Vector4F &operator=(const Vector4D &) noexcept;
        Vector4F &operator+=(const Vector4F &) noexcept;
        Vector4F &operator-=(const Vector4F &) noexcept;
        Vector4F &operator*=(float) noexcept;
        Vector4F &operator*=(int) noexcept;
        Vector4F &operator/=(float) noexcept(false);
        Vector4F &operator/=(int) noexcept(false);
        Vector4F &operator^=(float) noexcept;
        Vector4F &operator^=(int) noexcept;

        friend bool (::operator==)(const Vector4F &, const Vector4F &) noexcept;
        friend bool (::operator!=)(const Vector4F &, const Vector4F &) noexcept;
    };

    class [[maybe_unused]] Vector4D {
    private:
        double _x{0.0f};
        double _y{0.0f};
        double _z{0.0f};
        double _t{0.0f};

    public:
        [[maybe_unused]] static Vector4D nullVector;

        [[maybe_unused]] Vector4D() noexcept;
        [[maybe_unused]] Vector4D(double x, double y, double z, double t) noexcept;
        [[maybe_unused]] Vector4D(const Vector4D &) noexcept;
        [[maybe_unused]] explicit Vector4D(const Vector4F &) noexcept;

        [[maybe_unused]] [[nodiscard]] bool isNull() const noexcept;

        [[maybe_unused]] Vector4D &setX(double) noexcept;
        [[maybe_unused]] Vector4D &setY(double) noexcept;
        [[maybe_unused]] Vector4D &setZ(double) noexcept;
        [[maybe_unused]] Vector4D &setT(double) noexcept;

        [[maybe_unused]] [[nodiscard]] double getX() const noexcept;
        [[maybe_unused]] [[nodiscard]] double getY() const noexcept;
        [[maybe_unused]] [[nodiscard]] double getZ() const noexcept;
        [[maybe_unused]] [[nodiscard]] double getT() const noexcept;

        [[maybe_unused]] [[nodiscard]] std::string toString() const noexcept;
        [[maybe_unused]] explicit operator std::string() const;
        [[maybe_unused]] explicit operator Vector4F() const;

        friend Vector4D (::operator+)(const Vector4D &, const Vector4D &) noexcept;
        friend Vector4D (::operator-)(const Vector4D &, const Vector4D &) noexcept;
        friend Vector4D (::operator*)(const Vector4D &, double) noexcept;
        friend Vector4D (::operator*)(const Vector4D &, int) noexcept;
        friend Vector4D (::operator/)(const Vector4D &, double) noexcept(false);
        friend Vector4D (::operator/)(const Vector4D &, int) noexcept(false);
        friend Vector4D (::operator^)(const Vector4D &, double) noexcept;
        friend Vector4D (::operator^)(const Vector4D &, int) noexcept;

        Vector4D &operator=(const Vector4D &) noexcept;
        Vector4D &operator=(const Vector4F &) noexcept;
        Vector4D &operator+=(const Vector4D &) noexcept;
        Vector4D &operator-=(const Vector4D &) noexcept;
        Vector4D &operator*=(double) noexcept;
        Vector4D &operator*=(int) noexcept;
        Vector4D &operator/=(double) noexcept(false);
        Vector4D &operator/=(int) noexcept(false);
        Vector4D &operator^=(double) noexcept;
        Vector4D &operator^=(int) noexcept;

        friend bool (::operator==)(const Vector4D &, const Vector4D &) noexcept;
        friend bool (::operator!=)(const Vector4D &, const Vector4D &) noexcept;
    };

    [[maybe_unused]] typedef Vector4F Vector4;
}

#ifndef nullvec
#define nullvec engine::Vector4F::nullVector
#endif

#pragma clang diagnostic pop
#endif //ENG1_VECTOR4_H
